/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:12 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:13 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that finalizes the redirection setup, restoring 
   standard input and output file descriptors as needed.

   - If a pipe is being prepared (prep_pipe), restores the output 
     to the pipe's write end; otherwise, restores the original stdout.
   - If a pipe operation is active (do_pipe) and it's not a heredoc,
     restores the input to the temporary read file descriptor; 
     otherwise, restores the original stdin.
   - This ensures the command's input/output is correctly redirected 
     for both piped and non-piped commands.
*/
void	done_redir(t_mini *mini, int heredoc)
{
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	if (mini->pipes.do_pipe && !heredoc)
		dup2(mini->pipes.temp_read_fd, STDIN_FILENO);
	else
		dup2(mini->pipes.saved_stdin, STDIN_FILENO);
}

/*
   Heres the function that handles output redirection for commands, either
   by overwriting (OUT) or appending (APPEND) to the specified 'file'.

   - Determines the appropriate flags based on the 'type':
     - OUT: Creates or truncates the file and opens it for writing.
     - APPEND: Creates or opens the file for appending.
   - Attempts to open the 'file' with the determined flags:
     - If the file cannot be opened, closes any open file descriptor and 
       returns -1 to indicate failure.
   - Redirects the opened file descriptor to standard output (STDOUT_FILENO).
   - Returns 0 on success, indicating the redirection was successful.
*/
int	redir_out(t_mini *mini, char *file, int type)
{
	int		flags;

	if (type == OUT)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	if (type == APPEND)
		flags = O_CREAT | O_APPEND | O_WRONLY;
	mini->fd_out = ms_open(mini, file, flags, 0644);
	if (mini->fd_out == -1)
	{
		close (mini->fd_out);
		return (-1);
	}
	handle_io(mini->fd_out, STDOUT_FILENO);
	return (0);
}

/*
   Heres the function that handles input redirection for commands, managing 
   regular input files and heredoc.

   - Sets 'mini->pipes.is_redir_in' to indicate input redirection is active.
   - If 'type' is IN:
     - Opens the specified 'file' in read-only mode.
     - If the file cannot be opened, returns -1.
     - Redirects the opened file descriptor to standard input (STDIN_FILENO).
   - If 'type' is HEREDOC:
     - Prepares for heredoc by forking a process and running 'heredoc()'.
     - Waits for the heredoc process to finish.
     - Checks the exit status to handle possible errors (e.g., SIGINT).
     - Redirects the heredoc output to standard input (STDIN_FILENO).
   - Returns 0 on success, or -1 if an error occurred during redirection.
*/
int	redir_in(t_mini *mini, t_cmdblock *cmdblock, char *file, int type)
{
	mini->pipes.is_redir_in = 1;
	if (type == IN)
	{
		mini->fd_in = ms_open(mini, file, O_RDONLY, 0644);
		if (mini->fd_in == -1)
			return (-1);
		handle_io(mini->fd_in, STDIN_FILENO);
	}
	if (type == HEREDOC)
	{
		done_redir(mini, 1);
		pipe(mini->pipes.h_pipe);
		cmdblock->h_pid = fork();
		if (cmdblock->h_pid == 0)
			heredoc(mini, cmdblock);
		waitpid(cmdblock->h_pid, &mini->pipes.hd_estatus, 0);
		close(mini->pipes.h_pipe[WRITE]);
		if (WEXITSTATUS(mini->pipes.hd_estatus) == SIGINT)
		{
			close(mini->pipes.h_pipe[READ]);
			return (-1);
		}
		dup2(mini->pipes.h_pipe[READ], STDIN_FILENO);
	}
	return (0);
}

/*
   Heres the function that selects and executes the appropriate redirection 
   based on the command argument provided.

   - Compares 'cmd_argv' with predefined redirection strings like S_OUT, 
     S_APPEND, S_IN, and S_HEREDOC.
   - If a match is found:
     - Calls the corresponding redirection function (redir_out or redir_in) 
       with the appropriate parameters.
     - Returns the result of the redirection function.
   - If no match is found, returns 0 indicating no action was taken.
*/
static int	select_and_exec(t_mini *mini, t_cmdblock *cmdblock, char *cmd_argv)
{
	if (ft_strcmp(cmd_argv, S_OUT) == 0)
		return (redir_out(mini, cmdblock->outfile, OUT));
	if (ft_strcmp(cmd_argv, S_APPEND) == 0)
		return (redir_out(mini, cmdblock->outfile, APPEND));
	if (ft_strcmp(cmd_argv, S_IN) == 0)
		return (redir_in(mini, cmdblock, cmdblock->infile, IN));
	if (ft_strcmp(cmd_argv, S_HEREDOC) == 0)
		return (redir_in(mini, cmdblock, cmdblock->infile, HEREDOC));
	return (0);
}

/*
   Heres the function that handles the execution of redirection operations 
   within a command block.

   - Initializes variables: 'i' for looping through command arguments, and 
   'option' to track if the first argument is a redirection.
   - Sets up initial states for infile, outfile, and is_redir_in to null or 0.
   - If the first argument of cmd_argv is a redirection, 'option' is set to 1.
   - Iterates through command arguments:
     - Based on 'option', either processes the current argument or skips one 
       argument forward when calling get_iofile.
     - Executes the command or redirection using select_and_exec.
   - Returns SUCCESS if all redirections and executions are processed correctly.
*/
int	exec_redir(t_mini *mini, t_cmdblock *cmdblock)
{
	int		i;
	int		option;

	i = 0;
	option = 0;
	cmdblock->infile = NULL;
	cmdblock->outfile = NULL;
	mini->pipes.is_redir_in = 0;
	if (check_for_redir(mini, cmdblock->cmd_argv[0]) == SUCCESS)
		option = 1;
	while (cmdblock->cmd_argv[i] != NULL)
	{
		if (option == 1)
			get_iofile(mini, cmdblock, i);
		else
			get_iofile(mini, cmdblock, i + 1);
		if (select_and_exec(mini, cmdblock, cmdblock->cmd_argv[i]) == -1)
			return (-1);
		i++;
	}
	return (SUCCESS);
}

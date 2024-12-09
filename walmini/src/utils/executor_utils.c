/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:32 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:33 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Here's the function that executes a program directly by setting up 
   process forking, signal handling, and permission checking.

   - How It Works:
     - Checks if the program has execution permissions using 
       `get_program_permission`.
     - If permission check fails, returns the corresponding error number.
     - Checks if command arguments are valid; if not, returns 0.
     - Sets `exec_path` to the program path from `cmdblock`.
     - If no executable path is set, returns 127.
     - Forks a new process; in the child process, calls `execute` to 
       run the program.
     - In the parent process, sets up signal handlers and waits for the 
       child process.
     - If the child process was terminated by a signal, returns the signal 
       number plus 128.
     - Otherwise, returns the exit status of the command.

   - Data Types:
     - Input: `t_mini *mini` (pointer to shell structure), 
       `t_cmdblock *cmdblock` (structure containing command arguments).
     - Output: Returns the exit status or signal number of the executed 
       program.
*/
int	exec_program(t_mini *mini, t_cmdblock *cmdblock)
{
	int		errnum;

	errnum = get_program_permission(mini, cmdblock);
	if (errnum != 0)
		return (errnum);
	if (cmdblock->cmd_argv == NULL || cmdblock->cmd_argv[0] == NULL)
		return (0);
	mini->exec_path = cmdblock->cmd_argv[0];
	if (!mini->exec_path)
		return (127);
	cmdblock->need_wait = 1;
	cmdblock->pid = fork();
	if (cmdblock->pid == 0)
		execute(mini, cmdblock);
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, signal_handler_exec);
	if (mini->pipes.prep_pipe == 0)
		waitpid(cmdblock->pid, &(cmdblock->estatus), 0);
	if (WIFSIGNALED(cmdblock->estatus))
		return (WTERMSIG(cmdblock->estatus) + 128);
	return (WEXITSTATUS(cmdblock->estatus));
}

/*
   Here's the function that handles the execution of commands by forking 
   processes, setting up signal handlers, and managing redirections.

   - How It Works:
     - Checks if the command arguments are valid; if not, returns 0.
     - Retrieves the executable path for the command using `get_exec_path`.
     - If the path is not found, returns 127.
     - Sets `need_wait` to 1 and forks a new process.
     - In the child process, calls the `execute` function to run the command.
     - In the parent process, sets up signal handlers and waits for the 
       child process to complete.
     - Manages redirection using `done_redir`.
     - If the child process was terminated by a signal, returns the signal 
       number plus 128.
     - Otherwise, returns the exit status of the command.

   - Data Types:
     - Input: `t_mini *mini` (pointer to shell structure), 
       `t_cmdblock *cmdblock` (structure containing command arguments).
     - Output: Returns the exit status or signal number of the executed command.
*/
int	exec_commands(t_mini *mini, t_cmdblock *cmdblock)
{
	if (cmdblock->cmd_argv == NULL || cmdblock->cmd_argv[0] == NULL)
		return (0);
	mini->exec_path = get_exec_path(mini, cmdblock->cmd_argv);
	if (!mini->exec_path)
		return (127);
	cmdblock->need_wait = 1;
	cmdblock->pid = fork();
	if (cmdblock->pid == 0)
		execute(mini, cmdblock);
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, signal_handler_exec);
	free (mini->exec_path);
	done_redir(mini, 0);
	if (mini->pipes.prep_pipe == 0)
		waitpid(cmdblock->pid, &(cmdblock->estatus), 0);
	if (WIFSIGNALED(cmdblock->estatus))
		return (WTERMSIG(cmdblock->estatus) + 128);
	return (WEXITSTATUS(cmdblock->estatus));
}

/*
   Here's the function that handles the execution of a command by 
   setting up the necessary signal handlers, preparing the environment, 
   and executing the command with `execve`.

   - How It Works:
     - Sets the signal handlers for SIGINT and SIGQUIT to default 
       behavior.
     - Converts the linked list of environment variables into a 2D array 
       for `execve` using `ft_llto2darr`.
     - Closes the read end of the pipe if `prep_pipe` is true.
     - Calls `do_pipe` if `do_pipe` is true to handle piping.
     - Attempts to execute the command with `execve`. If it fails, 
       reports an error using `cmd_error` and exits with status 127.
     - If execution succeeds, exits with status 0.

   - Data Types:
     - Input: `t_mini *mini` (pointer to shell structure), 
       `t_cmdblock *cmdblock` (structure containing command arguments).
     - Output: Calls `exit()` with the status code of the command execution.
*/
int	execute(t_mini *mini, t_cmdblock *cmdblock)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	mini->env = ft_llto2darr(mini->envp, env_to_str);
	if (mini->pipes.prep_pipe)
		close(mini->pipes.pipe[READ]);
	if (mini->pipes.do_pipe)
		do_pipe(mini);
	if (execve(mini->exec_path, cmdblock->cmd_argv, mini->env) == -1)
	{
		cmd_error(mini, cmdblock->cmd_argv, CMD_NF);
		exit(127);
	}
	exit(0);
}

/*
   Here's the function that manages the execution of commands in 
   the shell, including built-ins and external programs.

   - How It Works:
     - Ignores the SIGINT signal to prevent interruptions.
     - Returns 0 if `cmdblock->cmd_argv` is NULL or empty.
     - Calls `redir_error` to handle redirection errors; returns 258 
       if an error occurs.
     - If redirection is needed, executes it with `exec_redir` and 
       prepares execution arguments.
     - Executes built-ins using `exec_builtins` if the command is a 
       built-in.
     - If the command contains a '/', executes it with `exec_program`.
     - If `PATH` is NULL, reports an error and returns 127.
     - Otherwise, tries to execute the command using `exec_commands`.

   - Data Types:
     - Input: `t_mini *mini` (pointer to shell structure), 
       `t_cmdblock *cmdblock` (structure containing command arguments).
     - Output: Returns an integer indicating the command's exit status.
*/
int	executor(t_mini *mini, t_cmdblock *cmdblock)
{
	signal(SIGINT, SIG_IGN);
	if (cmdblock->cmd_argv == NULL || cmdblock->cmd_argv[0] == NULL)
		return (0);
	if (redir_error(mini, cmdblock) == ERROR)
		return (258);
	if (check_redir_type(mini, cmdblock) != 0)
	{
		if (exec_redir(mini, cmdblock) == -1)
			return (0);
		get_exec_argv(mini, cmdblock);
	}
	if (check_builtins(mini, cmdblock->cmd_argv[0]) == 1)
		return (exec_builtins(mini, cmdblock));
	else if (ft_strchr(cmdblock->cmd_argv[0], '/') != NULL)
		return (exec_program(mini, cmdblock));
	else if (get_env(mini, "PATH") == NULL)
	{
		cmd_error(mini, cmdblock->cmd_argv, NSFD);
		return (127);
	}
	else
		return (exec_commands(mini, cmdblock));
	return (0);
}

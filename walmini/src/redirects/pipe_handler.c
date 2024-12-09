/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:09 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:10 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that initializes, prepares, and manages the piping 
   operations in the shell.

   init_pipe:
   - Initializes the pipe-related flags and file descriptors.
   - Sets do_pipe and prep_pipe to 0, indicating no active pipe operations.
   - Duplicates and saves the original standard input/output file descriptors 
   for later restoration.
   - Sets temp_read_fd to -1, meaning no temporary read file descriptor is 
   active initially.
   - Sets is_redir_in to 0, indicating no input redirection is currently active.

   prepare_pipe:
   - Creates a pipe using the pipe system call.
   - Redirects the standard output (STDOUT_FILENO) to the write end of the 
   pipe to send output to the next command.

   do_pipe:
   - Closes the write end of the pipe to stop writing.
   - If there is a temporary read file descriptor and no input redirection is 
   active, it redirects standard input (STDIN_FILENO) to this temporary file 
   descriptor, allowing input from the previous command in the pipeline.
*/
void	init_pipe(t_mini *mini)
{
	mini->pipes.do_pipe = 0;
	mini->pipes.prep_pipe = 0;
	mini->pipes.saved_stdin = dup(STDIN_FILENO);
	mini->pipes.saved_stdout = dup(STDOUT_FILENO);
	mini->pipes.temp_read_fd = -1;
	mini->pipes.is_redir_in = 0;
}

void	prepare_pipe(t_mini *mini)
{
	pipe(mini->pipes.pipe);
	dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
}

void	do_pipe(t_mini *mini)
{
	close(mini->pipes.pipe[WRITE]);
	if (mini->pipes.temp_read_fd != -1 && !mini->pipes.is_redir_in)
		dup2(mini->pipes.temp_read_fd, STDIN_FILENO);
}

/*
   Heres the function that finalizes the pipe setup and restores the standard 
   input/output.

   finish_pipe:
   - Closes the write end of the pipe if it was prepared.
   - Closes the temporary read file descriptor if it was used.
   - Resets the pipe flags (do_pipe and prep_pipe) to 0, indicating no active 
   pipe operation.
   - Updates temp_read_fd to store the current read end of the pipe for later 
   use.
   - Restores the original standard output and input file descriptors to what 
   they were before piping.
*/
void	finish_pipe(t_mini *mini)
{
	if (mini->pipes.prep_pipe)
		close(mini->pipes.pipe[WRITE]);
	if (mini->pipes.temp_read_fd != -1)
		close(mini->pipes.temp_read_fd);
	mini->pipes.do_pipe = 0;
	mini->pipes.prep_pipe = 0;
	mini->pipes.temp_read_fd = mini->pipes.pipe[READ];
	dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	dup2(mini->pipes.saved_stdin, STDIN_FILENO);
}

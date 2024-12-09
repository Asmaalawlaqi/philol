/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:03 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:04 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that handles the signal during "heredoc" mode.

   - Ignore the signal number:
     We are not using the signal number here, so just ignore it.

   - Clear the current line:
     Replace the current line in the readline buffer with an empty string.

   - Move to a new line:
     Adjust the cursor to a new line and redisplay the prompt.

   - Print a newline:
     Output a newline character to the terminal to ensure proper formatting.

   - Exit with SIGINT:
     Terminate the process with the SIGINT exit status.
*/
void	heredoc_signal_handler(int signo)
{
	(void)signo;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_putchar_fd('\n', STDOUT_FILENO);
	exit(SIGINT);
}

/*
   Heres the function that handles the "heredoc" behavior in the shell.

   - Set up signals:
     Adjust signal handling to ignore SIGQUIT and handle SIGINT 
     with a custom handler.

   - Reset standard output:
     Reset the standard output to the original saved state.

   - Read input:
     Prompt the user with `> ` and read the input using `readline`.

   - Expand input:
     Expand variables and wildcards in the input using `expand_input`.

   - Loop until delimiter is found:
     Keep reading input lines and writing them to the heredoc pipe 
     until the input matches the specified delimiter.

   - Clean up:
     Free the memory used by the input string, and if in pipe mode, 
     restore the standard output to the pipe.

   - Close pipe and exit:
     Close the write end of the heredoc pipe and exit the process.
*/
void	heredoc(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*rl;
	char	*delimiter;

	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	rl = readline("> ");
	expand_input(mini, &rl);
	delimiter = cmdblock->infile;
	while (rl && ft_strncmp(rl, delimiter, ft_strlen(delimiter) + 1))
	{
		write(mini->pipes.h_pipe[WRITE], rl, ft_strlen(rl));
		write(mini->pipes.h_pipe[WRITE], "\n", 1);
		free(rl);
		rl = readline("> ");
		expand_input(mini, &rl);
	}
	free(rl);
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	close(mini->pipes.h_pipe[WRITE]);
	exit(0);
}

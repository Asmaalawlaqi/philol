/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:13:14 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:13:15 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_errno;
/*
	 Heres the function that prints command error 
	 messages to stderr. Here’s 
	 the breakdown:

	 - `dup2(STDERR_FILENO, STDOUT_FILENO)`: Redirects stdout to stderr 
		 so the error message is sent to the error stream.
	 - `user = get_env(mini, "USER")`: Fetches the username from 
		 environment variables, defaulting to "user" if not found.
	 - If `cmds` is not NULL, it prints the user, command, and the 
		 error message. Otherwise, it just prints the user and the 
		 error message.
	 - After printing, it restores stdout. If a pipe is being 
		 prepared, stdout is redirected to the pipe; otherwise, it 
		 goes back to the saved stdout.

	 This function ensures that command-related errors are properly 
	 displayed, with stdout reset to its previous state afterward.
*/

void	cmd_error(t_mini *mini, char **cmds, char *msg)
{
	char	*user;

	dup2(STDERR_FILENO, STDOUT_FILENO);
	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	if (cmds != NULL)
		printf(YELLOW"%s: \033[0m%s: %s", user, cmds[0], msg);
	else
		printf(YELLOW"%s: \033[0m: %s", user, msg);
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
}

/*
	 Heres the function that handles printing 
	 syntax error messages when the shell encounters a problem 
	 with the command syntax. Heres what 
	 it does:

	 - `dup2(STDERR_FILENO, STDOUT_FILENO)`: Redirects stdout to stderr 
		 so the error message gets sent to the error stream.
	 - `user = get_env(mini, "USER")`: Retrieves the username from 
		 environment variables, defaults to "user" if not found.
	 - If `token` is not NULL, it prints the error message including 
		 the problematic token, then frees the token. Otherwise, it 
		 just prints the error message.
	 - After printing, stdout is restored. If a pipe was being 
		 prepared, stdout is redirected to the pipe; otherwise, it 
		 goes back to the saved stdout.
	 - `g_errno = 258`: Sets a specific error code for syntax errors.
	 - Returns 0, indicating the error was handled.

	 This makes sure syntax errors are clearly communicated, and 
	 stdout is restored correctly afterward.
*/
int	syntax_error(t_mini *mini, char *err_msg, char *token)
{
	char	*user;

	dup2(STDERR_FILENO, STDOUT_FILENO);
	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	if (token != NULL)
	{
		printf(YELLOW"%s:\033[0m %s `%s'\n", user, err_msg, token);
		free(token);
	}
	else
		printf(YELLOW"%s:\033[0m %s\n", user, err_msg);
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
	g_errno = 258;
	return (0);
}

/*
	 Heres the function that handles printing out an 
	 error related to command 
	 arguments (like when theres an issue with the command or its 
	 arguments). Heres how it works:

	 - `dup2(STDERR_FILENO, STDOUT_FILENO)`: Redirects stdout to stderr 
		 so the error message is sent to the error stream.
	 - `user = get_env(mini, "USER")`: Retrieves the username from the 
		 environment variables. Defaults to "user" if not found.
	 - `printf(YELLOW"%s: \033[0m%s: %s: %s", user, cmds[0], cmds[1], 
		 msg)`: Prints the error message, showing the user, the command 
		 that caused the error, the problematic argument, and the error 
		 message.
	 - After printing, it restores stdout. If a pipe was being prepared, 
		 it redirects stdout to the pipe; otherwise, it redirects it back 
		 to the saved stdout.

	 This setup ensures that command argument errors are clearly 
	 displayed and that stdout is properly restored afterwards.
*/
void	cmd_arg_error(t_mini *mini, char **cmds, char *msg)
{
	char	*user;

	dup2(STDERR_FILENO, STDOUT_FILENO);
	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	printf(YELLOW"%s: \033[0m%s: %s: %s", user, cmds[0], cmds[1], msg);
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
}

/*
	 Heres the function that handles printing out an error
	 related to an identifier 
	 (like when theres an invalid variable name or similar issue). Heres 
	 the breakdown:

	 - `dup2(STDERR_FILENO, STDOUT_FILENO)`: Redirects stdout to stderr 
		 so the error message is printed to the error stream.
	 - `user = get_env(mini, "USER")`: Gets the username from the 
		 environment variables. If it cant find it, defaults to "user".
	 - `printf(YELLOW"%s: \033[0m%s: `%s': %s", user, cmds[0], cmds[i], 
		 msg)`: Prints out the error message in a formatted way, showing 
		 the user, the command that caused the error, and the specific 
		 identifier issue.
	 - Finally, it restores the stdout back to its original file 
		 descriptor. If a pipe was being prepared, it redirects stdout to 
		 the pipe; otherwise, it redirects it back to the saved stdout.

	 This setup ensures that error messages are shown correctly and that 
	 stdout is properly restored afterwards.
*/
void	identifier_error(t_mini *mini, char **cmds, int i, char *msg)
{
	char	*user;

	dup2(STDERR_FILENO, STDOUT_FILENO);
	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	printf(YELLOW"%s: \033[0m%s: `%s': %s", user, cmds[0], cmds[i], msg);
	if (mini->pipes.prep_pipe)
		dup2(mini->pipes.pipe[WRITE], STDOUT_FILENO);
	else
		dup2(mini->pipes.saved_stdout, STDOUT_FILENO);
}

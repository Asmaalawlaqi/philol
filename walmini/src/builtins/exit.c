/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:12:33 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:12:34 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that calculates the exit number for the shell.

   get_exit_num:
   - Initializes the exit number to 0.
   - Checks if a numeric argument is provided in cmd_argv[1].
   - If the argument is non-numeric, it reports an error and returns 255.
   - If valid, converts the argument to an integer (exit_num).
   - Returns the exit number.
*/
static int	get_exit_num(t_mini *mini, t_cmdblock *cmdblock)
{
	int	exit_num;

	exit_num = 0;
	if (cmdblock && cmdblock->cmd_argv && cmdblock->cmd_argv[1])
	{
		if (ft_isnumber(cmdblock->cmd_argv[1]) == 0)
		{
			cmd_arg_error(mini, cmdblock->cmd_argv, NONNUMERICARG);
			return (255);
		}
		exit_num = ft_atoi(cmdblock->cmd_argv[1]);
	}
	return (exit_num);
}

/*
   Heres the function that handles the 'exit' command for the shell.

   ms_exit:
   - Prints "exit" unless its running in a pipeline.
   - Checks if too many arguments are passed; if so, it reports an error.
   - Clears the command history before exiting.
   - Retrieves the exit number, normalizes it to a valid range, 
     and assigns it to g_errno.
   - If part of a pipeline, it returns the exit code; otherwise, exits the shell.
*/
int	ms_exit(t_mini *mini, t_cmdblock *cmdblock)
{
	int	exit_num;

	if (!mini->pipes.do_pipe && !mini->pipes.prep_pipe)
		printf("exit\n");
	if (cmdblock && ft_2darrlen((void **)cmdblock->cmd_argv) > 2)
	{
		cmd_error(mini, cmdblock->cmd_argv, TOOMANYARGS);
		return (ERROR);
	}
	clear_history();
	exit_num = get_exit_num(mini, cmdblock);
	g_errno = ((exit_num % 256) + 256) % 256;
	if (mini->pipes.do_pipe == 1 || mini->pipes.prep_pipe == 1)
		return (((exit_num % 256) + 256) % 256);
	exit(exit_num);
}

/*
   Heres the function that determines the type of command separator.

   get_spliter_type:
   - Takes a string input and checks for specific command separators.
   - If the input matches "&&", it returns the AND type.
   - If the input matches "||", it returns the OR type.
   - If the input matches "|", it returns the PIPE type.
   - If the input matches ";", it returns the SEMI_COLON type.
   - If none of these match, it returns INVALID.
*/
int	get_spliter_type(char *input)
{
	if (ft_strncmp(input, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(input, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(input, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(input, ";", 1) == 0)
		return (SEMI_COLON);
	return (INVALID);
}

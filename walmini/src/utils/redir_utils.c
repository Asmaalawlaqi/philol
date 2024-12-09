/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:42 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:43 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Here's the function that converts a redirection token
   to a human-readable format.

   - How It Works:
     - Iterates through each character of the `orig` string.
     - Increments each character by 59 to convert it to a human-readable 
       format.

   - Data Types:
     - Input: `char *orig` (the original redirection token to convert).
     - Output: None (modifies the `orig` string in place).
*/
static void	convert_redir_token(char *orig)
{
	int		i;

	i = -1;
	while (orig[++i] != 0)
		orig[i] += 59;
}

/*
   Here's the function that prints redirection errors and handles them.

   - How It Works:
     - Checks if the current token is a valid redirection operator using 
       `check_is_redir`.
     - If it's not valid, it duplicates the token, converts it to a human-
       readable format, and reports a syntax error with `syntax_error`.
     - Checks if the next token is also a redirection operator; if so, it 
       performs similar error handling.
     - If the next token is `NULL`, indicating a missing argument, it 
       reports a syntax error for a missing token.
     - If no errors are found, it returns `SUCCESS`.

   - Data Types:
     - Input: `t_mini *mini` (mini shell context), `t_cmdblock *cmdblock` 
       (command block), `int i` (index in `cmd_argv`).
     - Output: `int` (returns `ERROR` or `SUCCESS`).
*/
static int	print_redir_error(t_mini *mini, t_cmdblock *cmdblock, int i)
{
	char	*err_token;

	if (!check_is_redir(cmdblock->cmd_argv[i]))
	{
		err_token = ft_strndup(cmdblock->cmd_argv[i], 1);
		convert_redir_token(err_token);
		syntax_error(mini, UNEXPECTED_TOKEN, err_token);
		return (ERROR);
	}
	if (cmdblock->cmd_argv[i + 1]
		&& check_is_redir(cmdblock->cmd_argv[i + 1]))
	{
		err_token = ft_strndup(cmdblock->cmd_argv[i + 1],
				ft_strlen(cmdblock->cmd_argv[i + 1]));
		convert_redir_token(err_token);
		syntax_error(mini, UNEXPECTED_TOKEN, err_token);
		return (ERROR);
	}
	if (cmdblock->cmd_argv[i + 1] == NULL)
	{
		err_token = ft_strdup("newline");
		syntax_error(mini, UNEXPECTED_TOKEN, err_token);
		return (ERROR);
	}
	return (SUCCESS);
}

/*
   Here's the function that checks for redirection errors in the command 
   block.

   - How It Works:
     - Iterates through the `cmd_argv` array.
     - Checks for specific error-indicating characters (`\3` and `\1`).
     - If an error character is found, it calls `print_redir_error` to 
       handle the error.
     - If `print_redir_error` returns an error, it propagates this by 
       returning `ERROR`.
     - If no errors are found, it returns `SUCCESS`.

   - Data Types:
     - Input: `t_mini *mini` (mini shell context), `t_cmdblock *cmdblock` 
       (command block).
     - Output: `int` (returns `ERROR` or `SUCCESS`).
*/
int	redir_error(t_mini *mini, t_cmdblock *cmdblock)
{
	int		i;

	i = 0;
	while (cmdblock->cmd_argv[i])
	{
		if (cmdblock->cmd_argv[i][0] == '\3'
			|| cmdblock->cmd_argv[i][0] == '\1')
		{
			if (print_redir_error(mini, cmdblock, i) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

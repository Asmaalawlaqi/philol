/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:47 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:48 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Here's the function that checks the type of redirection in a 
   command block by comparing its arguments with known redirection 
   operators.

   - How It Works:
     - Iterates through the command arguments (`cmdblock->cmd_argv`).
     - For each argument, compares it with known redirection operators 
       in `mini->redir`.
     - Returns the index of the matching redirection type + 1.
     - Returns 0 if no redirection operator matches.

   - Data Types:
     - Input: `t_mini *mini` (structure containing redirection operators),
       `t_cmdblock *cmdblock` (command block with arguments).
     - Output: `int` (index of the redirection type + 1, or 0 if no match).
*/
int	check_redir_type(t_mini *mini, t_cmdblock *cmdblock)
{
	char	**redir;
	char	**args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = cmdblock->cmd_argv;
	redir = mini->redir;
	if (args == NULL)
		return (0);
	while (args[j] != NULL)
	{
		i = 0;
		while (redir[i] != 0)
		{
			if (ft_strcmp(redir[i], args[j]) == 0)
				return (i + 1);
			i++;
		}
		j++;
	}
	return (0);
}

/*
   Here's the function that checks if a string is a redirection 
   operator based on a list of redirection operators.

   - How It Works:
     - Trims whitespace from `str` using `ft_strtrim`.
     - Iterates through the list of known redirection operators in 
       `mini->redir`.
     - Compares the trimmed string with each operator using `ft_strcmp`.
     - Returns SUCCESS if a match is found, otherwise ERROR.

   - Data Types:
     - Input: `t_mini *mini` (structure containing redirection operators),
       `char *str` (the string to check).
     - Output: `int` (SUCCESS if `str` matches a redirection operator, 
       otherwise ERROR).
*/
int	check_for_redir(t_mini *mini, char *str)
{
	int		i;
	char	*trimmed_str;

	trimmed_str = ft_strtrim(str, " \t");
	if (trimmed_str == NULL)
		return (ERROR);
	i = 0;
	while (mini->redir[i])
	{
		if (ft_strcmp(trimmed_str, mini->redir[i]) == 0)
		{
			free(trimmed_str);
			return (SUCCESS);
		}
		i++;
	}
	free(trimmed_str);
	return (ERROR);
}

/*
   Here's the function that checks if a string is a redirection operator.

   - How It Works:
     - Compares the input string `str` with known redirection tokens 
       using `ft_strcmp`.
     - Returns 1 if `str` matches any of the redirection tokens, else 
       returns 0.

   - Data Types:
     - Input: `char *str` (the string to check).
     - Output: `int` (1 if `str` is a redirection operator, otherwise 0).
*/
int	check_is_redir(char *str)
{
	if (ft_strcmp("\1", str) == 0)
		return (1);
	if (ft_strcmp("\1\1", str) == 0)
		return (1);
	if (ft_strcmp("\3", str) == 0)
		return (1);
	if (ft_strcmp("\3\3", str) == 0)
		return (1);
	else
		return (0);
}

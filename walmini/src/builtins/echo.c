/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:12:27 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:12:28 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that checks if an input is a valid option.

   is_option:
   - Begins by checking if the input starts with a '-' character.
   - If it does, it checks if the following characters are 'n'.
   - Continues to increment the index as long as 'n' is found.
   - Returns the length of the option if valid (all 'n's).
   - Returns 0 if the input isn't a valid option or contains other chars.
*/
static int	is_option(char *input)
{
	int		i;

	i = 1;
	if (input[0] != '-')
		return (0);
	while (input[i] == 'n')
		i++;
	if (input[i] == '\0')
		return (i);
	return (0);
}

/*
   Heres the function that mimics the echo command behavior.

   ms_echo:
   - Starts by checking for any options (-n) in the input
     which prevents a newline at the end.
   - Iterates through the input arguments and prints them.
   - Handles redirection if found, skipping further prints.
   - If no -n option is found, it adds a newline after printing.
   - Returns 0 to indicate successful execution.
*/
int	ms_echo(t_mini *mini, char **input)
{
	int		i;
	int		option;

	i = 1;
	option = 0;
	if (input[i] == NULL)
		return (printf("\n"));
	while (input[i] != NULL && is_option(input[i]) > 1)
	{
		option = 1;
		i++;
	}
	while (input[i] != NULL)
	{
		if (check_for_redir(mini, input[i]) == 0)
			break ;
		write (1, input[i], ft_strlen(input[i]));
		if (input[i] != NULL)
			write (1, " ", 1);
		i++;
	}
	if (option == 0)
		write(1, "\n", 1);
	return (0);
}

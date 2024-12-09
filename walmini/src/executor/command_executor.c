/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:13:27 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:13:28 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that handles redirection arguments in 
   `cmdblock->cmd_argv`.

   - Initial check:
     It starts by checking if the first argument in `cmd_argv` 
     is a redirection symbol using `check_is_redir`.

   - Skipping redirections:
     If the first argument is a redirection, it skips over the 
     redirection symbols and their associated filenames by 
     incrementing `i` by 2 for each pair.

   - Allocating new array:
     Allocates a new `res` array to hold the remaining arguments 
     after the redirections.

   - Copying remaining args:
     Copies the non-redirection arguments from `cmd_argv` to `res`.

   - Final steps:
     Frees the old `cmd_argv` array and assigns the new `res` 
     array back to `cmd_argv`, effectively removing the redirection 
     parts from `cmd_argv`.
*/
static void	get_redir_argv(t_cmdblock *cmdblock)
{
	char	**res;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (check_is_redir(cmdblock->cmd_argv[0]) == 1)
	{
		while (cmdblock->cmd_argv[i] != NULL
			&& check_is_redir(cmdblock->cmd_argv[i]))
			i += 2;
		res = (char **)malloc(sizeof(char *)
				* (ft_2darrlen((void **)cmdblock->cmd_argv) - i + 1));
		while (cmdblock->cmd_argv[i])
		{
			res[k++] = ft_strdup(cmdblock->cmd_argv[i]);
			i++;
		}
		res[k] = NULL;
		ft_free2darr((void **)cmdblock->cmd_argv);
		cmdblock->cmd_argv = res;
	}
}

/*
   Heres the function that calculates the size of the `cmd_argv` 
   array in `cmdblock` before encountering a redirection symbol.

   - The outer loop:
     Iterates over each element in `cmd_argv` to find any 
     redirection symbols.

   - The inner loop:
     Compares each argument in `cmd_argv` with the known redirection 
     symbols stored in `mini->redir`.

   - `ft_strcmp(cmdblock->cmd_argv[i], mini->redir[j]) == 0`:
     Checks if the current `cmd_argv` argument matches a redirection 
     symbol.

   - Returns the index `i` where a redirection symbol is found, or 0 
     if none are found.
*/
static int	get_exec_argv_sz(t_mini *mini, t_cmdblock *cmdblock)
{
	int		i;
	int		j;

	i = 0;
	while (cmdblock->cmd_argv[i])
	{
		j = 0;
		while (mini->redir[j])
		{
			if (ft_strcmp(cmdblock->cmd_argv[i], mini->redir[j]) == 0)
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

/*
   Heres the function that refines the `cmd_argv` array in the 
   `cmdblock` after handling initial redirections.

   - `get_exec_argv_sz(mini, cmdblock)`:
     Calculates the size for the new `cmd_argv` array, considering 
     redirection adjustments.

   - `res = (char **)malloc(sizeof(char *) * (i + 1))`:
     Allocates memory for the refined `cmd_argv` array.

   - The loop:
     Iterates over `cmd_argv`, copying each argument to the newly 
     allocated array `res`, ensuring accurate processing.

   - `ft_free2darr((void **)cmdblock->cmd_argv)`:
     Frees the original `cmd_argv` array to prevent memory leaks.

   - `cmdblock->cmd_argv = res`:
     Replaces the old `cmd_argv` with the new array for execution.
*/
static void	get_redir2_argv(t_mini *mini, t_cmdblock *cmdblock)
{
	int		i;
	int		j;
	int		k;
	char	**res;

	k = 0;
	i = get_exec_argv_sz(mini, cmdblock);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	while (i--)
	{
		j = 0;
		res[k] = malloc(sizeof(char) * (ft_strlen(cmdblock->cmd_argv[k]) + 1));
		while (cmdblock->cmd_argv[k][j])
		{
			res[k][j] = cmdblock->cmd_argv[k][j];
			j++;
		}
		res[k][j] = '\0';
		k++;
	}
	res[k] = NULL;
	ft_free2darr((void **)cmdblock->cmd_argv);
	cmdblock->cmd_argv = res;
}

/*
   Heres the function that refines the argument list `cmd_argv` 
   in the `cmdblock` after the initial redirection processing.

   - `get_exec_argv_sz(mini, cmdblock)`:
     Determines the size needed for the new argument array by 
     evaluating the command block with respect to redirections.

   - `res = (char **)malloc(sizeof(char *) * (i + 1))`:
     Allocates memory for the new array `res`, which will store 
     the final arguments after processing. 

   - The loop:
     Iterates over the original `cmd_argv`, copying each argument 
     to the newly allocated space in `res`. 

   - `ft_free2darr((void **)cmdblock->cmd_argv)`:
     Frees the memory used by the original argument array to avoid 
     memory leaks. 

   - `cmdblock->cmd_argv = res`:
     Replaces the original `cmd_argv` with the newly processed array.
*/
void	get_exec_argv(t_mini *mini, t_cmdblock *cmdblock)
{
	get_redir_argv(cmdblock);
	if (check_redir_type(mini, cmdblock) != 0)
		get_redir2_argv(mini, cmdblock);
}

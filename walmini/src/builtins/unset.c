/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:13:08 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:13:09 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that removes an environment variable from the linked list.

   rm_env_var:
   - First, it checks if the shell is in a pipe state and returns if true.
   - Then, it starts from the head of the environment list `mini->envp`.
   - If the environment variable to be removed is at the head, it updates
     the head pointer and deletes the node.
   - If the environment variable is found in any other position, it links
     the previous node to the node after the one being removed and deletes it.
   - It uses `ft_lstdelone` to delete the node and free associated memory.
*/
static void	rm_env_var(t_mini *mini, t_env *env)
{
	t_list	*curr;
	t_list	*tmp;

	if (mini->pipes.do_pipe || mini->pipes.prep_pipe)
		return ;
	curr = mini->envp;
	if (curr->content == env)
	{
		mini->envp = curr->next;
		ft_lstdelone(curr, clear_env_var);
		return ;
	}
	while (curr->next != NULL)
	{
		if (curr->next->content == env)
		{
			tmp = curr->next;
			curr->next = curr->next->next;
			ft_lstdelone(tmp, clear_env_var);
			return ;
		}
		curr = curr->next;
	}
}

/*
   Heres the function that unsets or removes environment variables.

   ms_unset:
   - Loops through `cmd_argv` starting from index 1 to process each argument.
   - For each argument, it checks if it's valid using `valid_input`.
   - If valid and not equal to "_", it searches for the environment variable
     using `check_env_var`.
   - If found, it removes the environment variable using `rm_env_var`.
   - If the input is invalid, it triggers an error using `identifier_error`.
*/
void	ms_unset(t_mini *mini, char **cmd_argv)
{
	t_env	*envp;
	int		i;

	i = 0;
	if (cmd_argv[1] == NULL)
		return ;
	while (cmd_argv[++i] != NULL)
	{
		envp = check_env_var(mini->envp, cmd_argv[i]);
		if (ft_strcmp(cmd_argv[i], "_") == 0)
			continue ;
		if (valid_input(cmd_argv[i]))
		{
			envp = check_env_var(mini->envp, cmd_argv[i]);
			if (envp != NULL)
				rm_env_var(mini, envp);
		}
		else
			identifier_error(mini, cmd_argv, i, INVALID_IDENTIFIER);
	}
}

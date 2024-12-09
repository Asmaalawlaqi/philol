/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:12:30 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:12:31 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that prints the current environment variables.

   ms_env:
   - Starts by getting the list of environment variables (env_list).
   - Iterates through each node in the linked list.
   - For each node, it checks if the value is not NULL.
   - If the value exists, it prints the key-value pair in the format 'key=value'.
   - Continues until all environment variables are printed.
   - Returns 0 after finishing the iteration.
*/
int	ms_env(t_mini *mini)
{
	t_list	*env_list;
	t_env	*env_node;

	env_list = mini->envp;
	while (env_list != NULL)
	{
		env_node = (t_env *)env_list->content;
		if (env_node->value != NULL)
			printf ("%s=%s\n", env_node->key, env_node->value);
		env_list = env_list->next;
	}
	return (0);
}

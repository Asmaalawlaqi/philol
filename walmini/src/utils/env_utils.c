/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:08:47 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:08:48 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Here's the function that retrieves the value of an environment 
   variable based on the provided key.

   - How It Works:
     - Iterates through the linked list `mini->envp`.
     - Compares each `key` in the `t_env` structure with the provided 
       `key` using `ft_strcmp`.
     - If a match is found, returns the corresponding `value`.
     - If the end of the list is reached without finding the key, returns `NULL`.

   - Data Types:
     - Input: `t_mini *mini` (pointer to the mini shell structure), 
       `char *key` (key to search for).
     - Output: `char *` (value associated with the key, or `NULL` if not found).
*/
char	*get_env(t_mini *mini, char *key)
{
	t_list	*envp;
	t_env	*env_var;

	envp = mini->envp;
	while (envp != NULL)
	{
		env_var = envp->content;
		if (ft_strcmp(key, env_var->key) == 0)
			return (env_var->value);
		envp = envp->next;
	}
	return (NULL);
}

/*
   Here's the function that adds a new environment variable to the list.

   - How It Works:
     - Allocates memory for a new `t_env` structure.
     - Sets the `key` and `value` fields of the structure.
     - Adds the new `t_env` structure to the end of the environment list 
       using `ft_lstadd_back` and `ft_lstnew`.

   - Data Types:
     - Input: `t_mini *mini` (pointer to the mini shell structure), 
       `char *key` (environment variable key), `char *value` (environment 
       variable value).
     - Output: None (modifies the environment list in `mini`).
*/
void	add_env_var(t_mini *mini, char *key, char *value)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (env_var == NULL)
		return ;
	env_var->key = key;
	env_var->value = value;
	ft_lstadd_back(&mini->envp, ft_lstnew(env_var));
}

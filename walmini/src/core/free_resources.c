/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:09:03 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:09:04 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	 Heres the function that clears out memory for an environment 
	 variable. Lets break it down:

	 - `env = (t_env *)content`: Casts the content to a t_env pointer so 
		 we can access the key and value.
	 - First, it checks if `env` is NULL. If it is, we just return since 
		 theres nothing to free.
	 - `free(env->key)`: If the key isnt NULL, we free the memory 
		 allocated for it.
	 - `free(env->value)`: If the value isnt NULL, we free the memory 
		 allocated for it.
	 - `free(env)`: Finally, we free the memory allocated for the env 
		 structure itself.

	 This makes sure each environment variable is properly cleaned up 
	 and no memory is left hanging around.
*/
void	clear_env_var(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	if (env == NULL)
		return ;
	if (env->key != NULL)
		free(env->key);
	if (env->value != NULL)
		free(env->value);
	free(env);
}

/*
	 Heres the function that frees up memory for a single command 
	 block. Heres whats happening:

	 - First, it checks if the argument is NULL. If it is, we dont need 
		 to free anything.
	 - `cmdblock = (t_cmdblock *)arg`: Casts the argument to a 
		 t_cmdblock pointer so we can work with it.
	 - `free(cmdblock->input)`: Frees the memory allocated for the 
		 command block's input string.
	 - `free(cmdblock)`: Frees the memory allocated for the command 
		 block structure itself.

	 This makes sure each command block is properly cleaned up and we 
	 dont leave any memory hanging around.
*/
void	free_cmdblock(void *arg)
{
	t_cmdblock	*cmdblock;

	if (arg == NULL)
		return ;
	cmdblock = (t_cmdblock *)arg;
	free(cmdblock->input);
	free(cmdblock);
}

/*
	 Heres the function that cleans up memory used by the mini shell 
	 structure to prevent memory leaks. Heres whats happening:

	 - `free(mini->input)`: Frees the memory allocated for the user's 
		 input string.
	 - `free(mini->prompt)`: Frees the memory allocated for the shell 
		 prompt.
	 - `ft_lstclear(&mini->cmdblock_list, free_cmdblock)`: Clears the 
		 command block list and frees memory for each command block using 
		 the `free_cmdblock` function.

	 This makes sure we free up all the resources our shell has used 
	 before moving on or exiting.
*/
void	ms_free(t_mini *mini)
{
	free(mini->input);
	ft_lstclear(&mini->cmdblock_list, free_cmdblock);
}

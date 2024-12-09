/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:12:39 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:12:40 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that displays environment variables in the export format.

   show_export:
   - Loops through the environment list, printing each variable in the format
     `declare -x key="value"`.
   - Starts with the smallest key and iterates to the biggest one.
   - For each key, it checks if the value is NULL:
     - If NULL, prints just the key with "declare -x".
     - Otherwise, prints the key and value in the format 
	  `declare -x key="value"`.
   - Updates the `smallest` pointer to the next smallest key after printing.
   - Continues this process until all environment variables are printed.
*/
static void	show_export(t_env *smallest, t_env *biggest, t_list *envp)
{
	t_env	*temp_content;
	t_list	*temp;
	int		i;

	i = ft_lstsize(envp);
	temp_content = smallest;
	while (--i >= 0)
	{
		temp = envp;
		printf("declare -x %s", temp_content->key);
		if (temp_content->value == NULL)
			printf("\n");
		else
			printf("=\"%s\"\n", temp_content->value);
		temp_content = biggest;
		while (temp != NULL)
		{
			if (ft_strcmp(((t_env *)temp->content)->key, temp_content->key) < 0
				&& ft_strcmp(((t_env *)temp->content)->key, smallest->key) > 0)
				temp_content = (t_env *)temp->content;
			temp = temp->next;
		}
		smallest = temp_content;
	}
}

/*
   Heres the function that edits or adds an environment variable.

   edit_env_var:
   - Takes a key-value pair and updates the environment list.
   - First, checks if the key is "_" (a special case), and if so,
     frees the key and value without making changes.
   - Searches the environment list for an existing variable with the
     given key.
   - If the key is not found:
     - Adds a new environment variable with the provided key and value.
   - If the key is found:
     - Frees the old value and updates it with the new one if value is
       not null.
     - Frees the key after updating or adding the environment variable.
*/
void	edit_env_var(t_mini *mini, char *key, char *value)
{
	t_env	*envp;

	if (ft_strcmp(key, "_") == 0)
	{
		free (key);
		if (value)
			free (value);
		return ;
	}
	envp = check_env_var(mini->envp, key);
	if (envp == NULL)
		add_env_var(mini, key, value);
	else
	{
		if (value != NULL)
		{
			free(envp->value);
			envp->value = value;
		}
		free (key);
	}
}

/*
   Heres the function that extracts key-value pairs from a string.

   get_key_value:
   - Takes an argument (arg) and splits it into key and value.
   - Searches for '=' to determine where the key ends and value begins.
   - If '=' is not found, the entire argument is treated as the key.
   - If '=' is found:
     - Extracts the key by duplicating the part before '='.
     - Checks if the value starts with a quote (single or double).
     - If quoted, duplicates the value without the surrounding quotes.
     - If not quoted, duplicates the value as it is.
*/
static void	get_key_value(char *arg, char **key, char **value)
{
	*value = ft_strchr(arg, '=');
	if (*value == NULL)
	{
		*key = ft_strdup(arg);
		return ;
	}
	*key = ft_strndup(arg, ft_strlen(arg) - ft_strlen(*value));
	if ((*value + 1)[0] == '"' || (*value + 1)[0] == '\'')
		*value = ft_strndup(*value + 2, ft_strlen(*value + 2) - 1);
	else
		*value = ft_strdup(*value + 1);
}

/*
   Heres the function that prints all environment variables 
   in sorted order by their keys.

   print_export:
   - Initializes pointers for smallest and biggest environment 
     variables, pointing to the first element in the envp list.
   - Loops through the environment list:
     - Updates smallest_content if a smaller key is found.
     - Updates biggest_content if a bigger key is found.
   - Calls show_export() to display the variables in order from 
     smallest to biggest.
   - Returns 0 to indicate success.
*/
int	print_export(t_mini *mini)
{
	t_list	*temp;
	t_env	*smallest_content;
	t_env	*biggest_content;

	temp = mini->envp;
	smallest_content = ((t_env *)temp->content);
	biggest_content = ((t_env *)temp->content);
	while (temp != NULL)
	{
		if (ft_strcmp(((t_env *)temp->content)->key, smallest_content->key) < 0)
			smallest_content = (t_env *)temp->content;
		if (ft_strcmp(((t_env *)temp->content)->key, biggest_content->key) > 0)
			biggest_content = (t_env *)temp->content;
		temp = temp->next;
	}
	show_export(smallest_content, biggest_content, mini->envp);
	return (0);
}

/*
   Heres the function that handles the export command for the shell.

   ms_export:
   - Starts by initializing key, value, and error number (errnum).
   - If no arguments or a redirection is present, calls print_export().
   - Loops through cmd_argv, checking if the shell is in a pipe, 
     if not, it processes each key-value pair.
   - Checks if the key is valid; if so, it edits the environment variable.
   - If the key is invalid, it reports an error and sets errnum to 1.
   - Frees allocated memory for key and value after processing.
   - Returns the error number indicating success or failure.
*/
int	ms_export(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*key;
	char	*value;
	int		i;
	int		errnum;

	i = 0;
	errnum = 0;
	if (cmdblock->cmd_argv[1] == NULL || check_redir_type(mini, cmdblock) != 0)
		return (print_export(mini));
	while (cmdblock->cmd_argv[++i] != NULL)
	{
		if (mini->pipes.do_pipe || mini->pipes.prep_pipe)
			continue ;
		get_key_value(cmdblock->cmd_argv[i], &key, &value);
		if (valid_input(key))
			edit_env_var(mini, key, value);
		else
		{
			identifier_error(mini, cmdblock->cmd_argv, i, INVALID_IDENTIFIER);
			errnum = 1;
			free (key);
			free (value);
		}
	}
	return (errnum);
}

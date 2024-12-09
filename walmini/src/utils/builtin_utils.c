/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:09:12 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:09:13 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Here's the function that checks if a key is a valid environment 
   variable name.

   - How It Works:
     - Checks if the first character of `key` is an alphabetic character 
       or an underscore `_`.
     - Iterates through the remaining characters in `key`.
     - Ensures each character is either alphanumeric or an underscore.
     - Returns `1` if all characters are valid; otherwise, returns `0`.

   - Data Types:
     - Input: `char *key` (the key to be validated).
     - Output: `int` (returns `1` if the key is valid, `0` otherwise).
*/
int	valid_input(char *key)
{
	if (ft_isalpha(*key) == 0 && *key != '_')
		return (0);
	while (*(++key) != '\0')
	{
		if (ft_isalnum(*key) == 0 && *key != '_')
			return (0);
	}
	return (1);
}

/*
   Here's the function that checks if a given command is in the list 
   of built-in commands.

   - How It Works:
     - Iterates through the array of built-in commands (`builtins`).
     - Compares each built-in command with the provided `cmds` using 
       `ft_strcmp`.
     - Returns `1` if a match is found, indicating the command is a 
       built-in command.
     - Returns `0` if no match is found after checking all built-ins.

   - Data Types:
     - Input:
       - `t_mini *mini`: Pointer to the structure containing the 
         array of built-in commands.
       - `char *cmds`: The command string to check against the list 
         of built-ins.
     - Output:
       - `int`: `1` if the command is a built-in, `0` otherwise.
*/
int	check_builtins(t_mini *mini, char *cmds)
{
	char	**builtins;

	builtins = mini->builtins;
	if (cmds == NULL)
		return (0);
	while (*builtins != NULL)
	{
		if (ft_strcmp(*builtins, cmds) == 0)
			return (1);
		builtins++;
	}
	return (0);
}

/*
   Here's the function that chooses and executes a built-in command 
   based on the command specified in `cmdblock`.

   - How It Works:
     - Compares the first argument of `cmdblock` with known built-in 
       commands (`exit`, `env`, `pwd`, `unset`, `export`, `cd`, `echo`).
     - Calls the corresponding function for the command found.
     - Sets `errnum` based on the return value of the executed function.

   - Data Types:
     - Input:
       - `t_mini *mini`: Pointer to the structure containing the 
         environment and other state information.
       - `t_cmdblock *cmdblock`: Pointer to the command block 
         containing the command and arguments.
     - Output:
       - `int`: Error number from the executed command function, or 
         `0` if no command matches.
*/
static int	choose_and_exec(t_mini *mini, t_cmdblock *cmdblock)
{
	int	errnum;

	errnum = 0;
	if (ft_strncmp(cmdblock->cmd_argv[0], "exit", 5) == 0)
		errnum = ms_exit(mini, cmdblock);
	else if (ft_strncmp(cmdblock->cmd_argv[0], "env", 4) == 0)
		ms_env(mini);
	else if (ft_strncmp(cmdblock->cmd_argv[0], "pwd", 4) == 0)
		ms_pwd();
	else if (ft_strncmp(cmdblock->cmd_argv[0], "unset", 6) == 0)
		ms_unset(mini, cmdblock->cmd_argv);
	else if (ft_strncmp(cmdblock->cmd_argv[0], "export", 7) == 0)
		errnum = ms_export(mini, cmdblock);
	else if (ft_strncmp(cmdblock->cmd_argv[0], "cd", 3) == 0)
		errnum = ms_cd(mini, cmdblock);
	else if (ft_strncmp(cmdblock->cmd_argv[0], "echo", 5) == 0)
		errnum = ms_echo(mini, cmdblock->cmd_argv);
	return (errnum);
}

/*
   Here's the function that executes built-in commands within 
   the `t_mini` structure. It is used for running built-in 
   commands like `cd`, `exit`, `echo`, etc.

   - How It Works:
     - Calls `choose_and_exec` to select and execute the built-in 
       command specified in `cmdblock`.
     - After execution, it calls `done_redir` to restore file 
       descriptors and clean up any redirections.
     - Returns the error number obtained from `choose_and_exec`.

   - Data Types:
     - Input:
       - `t_mini *mini`: Pointer to the structure containing 
         the environment and other state information.
       - `t_cmdblock *cmdblock`: Pointer to the command block 
         containing the command and arguments.
     - Output:
       - `int`: Error number from `choose_and_exec`.
*/
int	exec_builtins(t_mini *mini, t_cmdblock *cmdblock)
{
	int	errnum;

	errnum = choose_and_exec(mini, cmdblock);
	done_redir(mini, 0);
	return (errnum);
}

/*
   Here's the function that checks for an environment variable 
   in a linked list of `t_env` structures. It is used in functions 
   such as `edit_env_var` and `rm_env_var`.

   - How It Works:
     - Iterates through the linked list `env`, which contains 
       `t_env` structures representing environment variables.
     - Compares the `key` with the `key` field of each `t_env` 
       structure using `ft_strcmp`.
     - If a match is found, it returns the address of the matching 
       `t_env` structure.
     - If the end of the list is reached without finding a match, 
       it returns `NULL`.

   - Data Types:
     - Input: 
       - `t_list *env`: Pointer to the start of the environment 
         list.
       - `char *key`: Key to search for.
     - Output:
       - `t_env *`: Pointer to the found environment variable or 
         `NULL` if not found.
*/
t_env	*check_env_var(t_list *env, char *key)
{
	t_env	*temp_env;

	while (env != NULL)
	{
		temp_env = env->content;
		if (ft_strcmp(key, temp_env->key) == 0)
			return (temp_env);
		env = env->next;
	}
	return (NULL);
}

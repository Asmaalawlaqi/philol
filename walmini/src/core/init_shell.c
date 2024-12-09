/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:08:52 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:08:53 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that initializes the built-in
   commands that our shell will recognize and 
   handle directly, without forking a new process.
   Heres whats going on:

   - `mini->builtins[0] = "pwd"`: Sets the built-in command for 
     printing the current directory.
   - `mini->builtins[1] = "env"`: Adds the command to print 
     environment variables.
   - `mini->builtins[2] = "echo"`: Adds the command to print text 
     to the terminal.
   - `mini->builtins[3] = "cd"`: Sets up the command to change 
     directories.
   - `mini->builtins[4] = "unset"`: Adds the command to remove 
     environment variables.
   - `mini->builtins[5] = "export"`: Sets the command to add or 
     modify environment variables.
   - `mini->builtins[6] = "exit"`: Adds the command to exit the shell.
   - `mini->builtins[7] = NULL`: Marks the end of the list of 
     built-in commands.

   This is basically a list of all the commands that our shell can 
   handle internally, making it faster and more efficient.
*/
static void	init_builtins(t_mini *mini)
{
	mini->builtins[0] = "pwd";
	mini->builtins[1] = "env";
	mini->builtins[2] = "echo";
	mini->builtins[3] = "cd";
	mini->builtins[4] = "unset";
	mini->builtins[5] = "export";
	mini->builtins[6] = "exit";
	mini->builtins[7] = NULL;
}

/*
   Heres the function that sets up the redirection characters
   for the shell.
   Heres whats going on:

   - `mini->redir[0] = "\1"`: Sets the basic redirection, probably 
     for standard output (`>`).
   - `mini->redir[1] = "\1\1"`: Handles double redirection, like 
     appending (`>>`).
   - `mini->redir[2] = "\3"`: Sets up redirection for standard 
     input (`<`).
   - `mini->redir[3] = "\3\3"`: Deals with here-doc redirection 
     (`<<`).
   - `mini->redir[4] = NULL`: Marks the end of the redirection list.

   This function is getting all the redirection types ready for 
   when we parse and handle commands.
*/
static void	init_redir(t_mini *mini)
{
	mini->redir[0] = "\1";
	mini->redir[1] = "\1\1";
	mini->redir[2] = "\3";
	mini->redir[3] = "\3\3";
	mini->redir[4] = NULL;
}

/*
   Heres the function that preps everything for
   each loop in the shell. 
   Heres the breakdown:

   - `init_signal`: Sets up signal handling, making sure we can 
     properly catch and handle signals like Ctrl+C.
   - `init_prompt`: Initializes the command prompt with the 
     current user and directory info, and preps it to display.
   - `init_pipe`: Prepares the pipe settings, so we can handle 
     command chaining and redirections later on.

   All this gets our shell ready for the user's next command.
*/
void	ms_loop_init(t_mini *mini)
{
	init_signal();
	init_prompt(mini);
	init_pipe(mini);
}

/*
   Heres the function that sets up the environment variables 
   for our shell. Heres what it does:

   - It goes through each string in the `envp` array, which 
     contains the environment variables.
   - For each environment variable, it splits the string into 
     `key` and `value` parts at the '=' character.
   - The `key` is duplicated up to the '=' sign, and the 
     `value` is duplicated from right after the '='.
   - Then, it adds the `key` and `value` pair to our shell's 
     environment list using `add_env_var`.
   - This process repeats until all environment variables 
     are stored in `mini->envp`.

   Functions used:
   - `ft_strchr`: Finds the '=' character in the environment 
     string.
   - `ft_strndup`: Duplicates the `key` part of the environment 
     variable.
   - `ft_strdup`: Duplicates the `value` part of the environment 
     variable.
   - `add_env_var`: Adds the `key` and `value` to the shell's 
     environment list.
*/
static void	init_env(t_mini *mini, char **envp)
{
	char	*key;
	char	*value;

	while (*envp != NULL)
	{
		value = ft_strchr(*envp, '=');
		key = ft_strndup(*envp, (ft_strlen(*envp) - ft_strlen(value)));
		value = ft_strdup(value + 1);
		add_env_var(mini, key, value);
		envp++;
	}
}

/*
   Heres the function that is all about setting up
   the initial state for our shell. Lets break it down:

   - We start by setting `g_errno` to 0, just to clear any 
     previous error codes.
   - Then, we initialize `mini->envp` and `mini->cmdblock_list`
     to NULL, making sure we have a clean slate.
   - We call `init_env` to load up the environment variables 
     from `envp` and store them in `mini->envp`.
   - After that, we call `init_builtins` to set up the built-in 
     commands our shell can execute.
   - Finally, `init_redir` is called to set up any redirection 
     handling needed by the shell.

   Functions used:
   - `init_env`: Loads and stores the environment variables.
   - `init_builtins`: Sets up built-in shell commands.
   - `init_redir`: Prepares redirection functionalities.
*/
void	ms_init(t_mini *mini, char **envp)
{
	g_errno = 0;
	mini->envp = NULL;
	mini->cmdblock_list = NULL;
	init_env(mini, envp);
	init_builtins(mini);
	init_redir(mini);
}

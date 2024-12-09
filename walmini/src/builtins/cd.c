/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:12:24 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:12:25 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that updates an environment variable's 
   value or adds it if not found.

   update_dir:
   - This function loops through the linked list envp in mini 
	 to find the environment variable with the key that 
	 matches the provided key.
   - If a match is found, it frees the old value and updates it with 
	 the new value.
   - If no matching key is found in the list, it adds the key-value 
	 pair to the environment list using add_env_var.
   - It ensures the environment variable is either updated or 
	 added, maintaining the state.
*/
static void	update_dir(t_mini *mini, char *key, char *value)
{
	t_list	*envp;
	t_env	*temp;

	envp = mini->envp;
	while (envp != NULL)
	{
		temp = (t_env *)envp->content;
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (temp->value != NULL)
				free(temp->value);
			temp->value = value;
			break ;
		}
		envp = envp->next;
	}
	if (envp == NULL)
		add_env_var(mini, key, value);
}

/*
   Heres the function that changes the current working directory
	 to the specified path.

   ms_chdir:
   - The function first checks if the path exists using access. 
     If it doesn't, it returns -1 to indicate failure.
   - If a pipe is in use (prep_pipe or do_pipe), it bypasses changing 
     the directory and returns 0 immediately.
   - It saves the current directory in oldpwd before attempting to change 
     the directory with chdir.
   - If the directory change fails, it frees oldpwd and returns -1.
   - On success, it updates the "PWD" and "OLDPWD" environment variables 
     with the new and old paths, respectively, using update_dir.
   - Returns 0 on success or -1 if an error occurs.
*/
static int	ms_chdir(t_mini *mini, char *path)
{
	char	*oldpwd;

	if (access(path, F_OK) != 0)
		return (-1);
	if (mini->pipes.prep_pipe || mini->pipes.do_pipe)
		return (0);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		free(oldpwd);
		return (-1);
	}
	update_dir(mini, "PWD", getcwd(NULL, 0));
	update_dir(mini, "OLDPWD", oldpwd);
	return (0);
}

/*
   Heres the function that manages the `cd` command when no path is given,
   attempting to change to the user's home directory.

   ms_cd_home:
   - The function retrieves the `HOME` environment variable using get_env.
   - If `HOME` is not set, it calls cmd_error to indicate that there is 
     no home directory set and returns 1.
   - If `HOME` is set, it tries to change the directory to the home path 
     using ms_chdir.
   - If successful, it returns 0. 
   - If the directory exists but is not accessible, it triggers cmd_arg_error 
     with a message indicating the issue.
   - Returns 1 if there was an error changing to the home directory.
*/
static int	ms_cd_home(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*home;

	home = get_env(mini, "HOME");
	if (home == NULL)
	{
		cmd_error(mini, cmdblock->cmd_argv, NOHOME);
		return (1);
	}
	if (ms_chdir(mini, home) == 0)
		return (0);
	if (access(home, F_OK) == 0)
		cmd_arg_error(mini, cmdblock->cmd_argv, NOTDIR);
	else
		cmd_arg_error(mini, cmdblock->cmd_argv, NSFD);
	return (1);
}

/*
   Heres the function that handles the logic for changing directories 
   when the `cd` command is used with a specific path.

   ms_cd_dir:
   - This function first checks if the command is trying to change to 
     the previous directory using `cd -`. If so, it switches to the 
     `OLDPWD` directory and prints the new path.
   - It also checks if the command is `cd ~` or `cd ~/something` to 
     expand the `~` to the user's home directory.
   - The function then attempts to change to the specified directory 
     using ms_chdir.
   - If the directory does not exist, it calls cmd_arg_error to handle 
     the error.
   - Returns 0 on success or 1 if there was an error in changing the 
     directory.
*/
static int	ms_cd_dir(t_mini *mini, t_cmdblock *cmdblock)
{
	char	*home;
	char	*oldpwd;

	home = getenv("HOME");
	oldpwd = get_env(mini, "OLDPWD");
	if (oldpwd && ft_strcmp(cmdblock->cmd_argv[1], "-") == 0)
	{
		ms_chdir(mini, oldpwd);
		ms_pwd();
		return (0);
	}
	if (ft_strcmp(cmdblock->cmd_argv[1], "~") == 0)
		ft_strexpand(&(cmdblock->cmd_argv[1]), home, 0, 1);
	if (ft_strncmp(cmdblock->cmd_argv[1], "~/", 2) == 0)
		ft_strexpand(&(cmdblock->cmd_argv[1]), home, 0, 1);
	if (ms_chdir(mini, cmdblock->cmd_argv[1]) != 0)
	{
		if (access(cmdblock->cmd_argv[1], F_OK) == 0)
			cmd_arg_error(mini, cmdblock->cmd_argv, NOTDIR);
		else
			cmd_arg_error(mini, cmdblock->cmd_argv, NSFD);
		return (1);
	}
	return (0);
}

/*
   Heres the function that manages the `cd` command in the shell.

   ms_cd:
   - This function checks if the `cd` command has been provided with 
     any arguments.
   - If no arguments are provided, it calls ms_cd_home to change the 
     directory to the user's home directory.
   - If arguments are provided, it calls ms_cd_dir to change to the 
     specified directory.
   - Returns 0 on success or 1 if there was an error changing the 
     directory.
*/
int	ms_cd(t_mini *mini, t_cmdblock *cmdblock)
{
	if (ft_2darrlen((void **)cmdblock->cmd_argv) == 1)
		return (ms_cd_home(mini, cmdblock));
	return (ms_cd_dir(mini, cmdblock) != 0);
}

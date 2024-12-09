/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:13:39 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:13:40 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that converts an environment variable 
   (stored in `t_env`) into a single string in the format "key=value".

   - Cast the argument:
     First, cast the generic `arg` pointer to a `t_env` pointer 
     (`env_t`) to access its members.

   - Create "key=value":
     Use `ft_strjoin` to concatenate the key and value with an 
     equals sign `=` between them.

   - Clean up temporary string:
     After creating the full `output`, free the temporary string 
     `temp` used for holding the "key=" part.

   - Return:
     Returns the full string in "key=value" format.
*/
char	*env_to_str(void *arg)
{
	t_env	*env_t;
	char	*temp;
	char	*output;

	env_t = (t_env *)arg;
	temp = ft_strjoin(env_t->key, "=");
	output = ft_strjoin(temp, env_t->value);
	free(temp);
	return (output);
}

/*
   Heres the function that figures out the executable path for a 
   command by searching through directories listed in the PATH 
   environment variable.

   - Fetch PATH environment:
     Get the PATH environment variable from `mini` and split it 
     into individual directory paths.

   - Attempt path creation:
     Loop through each path directory, trying to build a valid 
     executable path using `try_cmd_path`.

   - Check for success:
     If a valid `cmd_path` is found, it stops the loop and returns 
     this path.

   - Cleanup and errors:
     After looping, it frees the memory used for the split paths.
     If no valid `cmd_path` was found, it reports an error with `cmd_error`.

   - Return:
     Returns the valid `cmd_path` if found, otherwise returns `NULL`.
*/
char	*get_exec_path(t_mini *mini, char **cmds)
{
	char	*plist;
	char	**paths;
	char	*cmd_path;
	int		i;

	i = 0;
	plist = get_env(mini, "PATH");
	paths = ft_split(plist, ':');
	cmd_path = NULL;
	while (paths[i] != NULL)
	{
		cmd_path = try_cmd_path(paths[i], cmds[0]);
		if (cmd_path != NULL)
			break ;
		i++;
	}
	ft_free2darr((void *)paths);
	if (cmd_path == NULL)
		cmd_error(mini, cmds, CMD_NF);
	return (cmd_path);
}

/*
   Heres the function that attempts to build a valid command path 
   by combining the given `path` with `cmd` and checking if it’s 
   executable.

   - Build the command path:
     First, it joins the `path` with a "/" to create a directory path 
     and then appends the `cmd` to this path using `ft_strjoin_free`.

   - Check execution access:
     It checks if the resulting `cmd_path` is executable using `access`.
     If it’s executable, it returns `cmd_path`.

   - Handle failure:
     If the `cmd_path` isn’t executable, it frees the memory allocated 
     for `cmd_path` and returns `NULL`.
*/
char	*try_cmd_path(char *path, char *cmd)
{
	char	*cmd_path;
	char	*temp;

	temp = ft_strjoin(path, "/");
	cmd_path = ft_strjoin_free(temp, cmd);
	if (access(cmd_path, X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

/*
   Heres the function that checks if the program in `cmdblock` 
   has the right permissions to execute.

   - File existence:
     First, it checks if the file exists using `stat`. If the file 
     doesn’t exist, it triggers a `cmd_error` with a "not found" 
     message and returns 127.

   - Directory check:
     Then it checks if the path is a directory using `S_ISDIR`. 
     If it’s a directory, it triggers a `cmd_error` with an 
     "is a directory" message and returns 126.

   - Execution permission:
     Lastly, it checks if the file has execution permissions with 
     `access`. If not, it triggers a `cmd_error` with a "permission 
     denied" message and returns 126.

   - Success:
     If all checks pass, it returns 0, meaning the program is ready 
     to be executed.
*/
int	get_program_permission(t_mini *mini, t_cmdblock *cmdblock)
{
	struct stat	file_stat;

	if (stat(cmdblock->cmd_argv[0], &file_stat) != 0)
	{
		cmd_error(mini, cmdblock->cmd_argv, NSFD);
		return (127);
	}
	if (S_ISDIR(file_stat.st_mode) != 0)
	{
		cmd_error(mini, cmdblock->cmd_argv, ISDIR);
		return (126);
	}
	else if (access(cmdblock->cmd_argv[0], X_OK) != 0)
	{
		cmd_error(mini, cmdblock->cmd_argv, PERMISSION_DENIED);
		return (126);
	}
	return (0);
}

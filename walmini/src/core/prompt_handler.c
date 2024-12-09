/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:13:23 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:13:24 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	 Heres the function that converts an absolute path into a relative path 
	 based on the user's home directory. Here’s how it works:

	 - `path = ft_strnstr(pwd, home, ft_strlen(home)) + ft_strlen(home)`: 
		 Finds the home directory within the current working directory 
		 (`pwd`) and then skips ahead to the part of the path after 
		 the home directory.

	 - `path = ft_strjoin("~", path)`: Prepends a `~` to the remaining 
		 part of the path to create a relative path.

	 - `free(pwd)`: Frees the original `pwd` memory since it's no longer 
		 needed.

	 - Finally, the function returns the newly constructed relative path, 
		 with the home directory replaced by `~`.
*/
static char	*get_relative_path(char *home, char *pwd)
{
	char	*path;

	path = ft_strnstr(pwd, home, ft_strlen(home)) + ft_strlen(home);
	path = ft_strjoin("~", path);
	free(pwd);
	return (path);
}

/*
	 Heres the function that sets up the shell prompt with user and directory 
	 info. Here’s how it works:

	 - `user = get_env(mini, "USER")`: Fetches the username from 
		 environment variables. Defaults to "user" if not found.
	 - `pwd = getcwd(NULL, 0)`: Retrieves the current working directory.
	 - `home = get_env(mini, "HOME")`: Fetches the home directory from 
		 environment variables.
	 - If the current directory (`pwd`) is within the home directory 
		 (`home`), it converts the path to a relative one, replacing the 
		 home directory with `~`.

	 This function preps the necessary info for the shell prompt, 
	 making sure it shows the user and directory context correctly.
*/
void	init_prompt(t_mini *mini)
{
	char	*user;
	char	*pwd;
	char	*home;

	user = get_env(mini, "USER");
	if (user == NULL)
		user = "user";
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	home = get_env(mini, "HOME");
	if (ft_strnstr(pwd, home, ft_strlen(home)))
		pwd = get_relative_path(home, pwd);
	free(pwd);
}

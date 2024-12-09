/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:12:57 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:12:58 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that prints the current working directory.

   ms_pwd:
   - Gets the current working directory using getcwd, storing it in `cwd`.
   - Prints the directory to the standard output using ft_putendl_fd.
   - Frees the allocated memory for `cwd` after printing.
*/
void	ms_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
}

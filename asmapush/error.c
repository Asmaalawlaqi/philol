/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:23:59 by asmalawl          #+#    #+#             */
/*   Updated: 2024/05/26 14:24:01 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_2d(char **x)
{
	int	j;

	j = 0;
	while (x[j] != NULL)
	{
		free(x[j]);
		j++;
	}
	free(x);
}

void	exit_any(t_list **stackA, char *s, char **x)
{
	free_2d(x);
	ft_lstclear(stackA, free);
	error_exit(s);
}

void	error_exit(char *arg_str)
{
	free(arg_str);
	write(2, "Error\n", 6);
	exit(1);
}

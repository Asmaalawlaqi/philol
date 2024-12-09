/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:25:07 by asmalawl          #+#    #+#             */
/*   Updated: 2024/05/26 14:25:08 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_3d(char **x)
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

void	error_exit1(t_list **stack_a, char *s, char **x)
{
	ft_lstclear(stack_a, free);
	free_3d(x);
	free(s);
	write(2, "Error\n", 6);
	exit(1);
}

int	ft_atoi(const char *str, t_list **stack_a, char *s, char **x)
{
	int				i;
	int				k;
	unsigned long	value;

	i = 0;
	k = 1;
	value = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			k = k * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + (str[i] - 48);
		if (value > 2147483647 && k == 1)
			error_exit1(stack_a, s, x);
		if (value > 2147483648 && k == -1)
			error_exit1(stack_a, s, x);
		i++;
	}
	return (value * k);
}

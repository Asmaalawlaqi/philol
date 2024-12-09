/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:50:08 by asmalawl          #+#    #+#             */
/*   Updated: 2024/08/23 17:50:16 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	chk_digit(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (arg[i] < 48 || arg[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int	handel_error(char **av)
{
	if (ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0
		|| chk_digit(av[1]) == 1)
		return (write(2, "Invalid philo number\n", 22), 1);
	if (ft_atoi(av[2]) < 60 || chk_digit(av[2]) == 1)
		return (write(2, "time to die invalid\n", 21), 1);
	if (ft_atoi(av[3]) < 60 || chk_digit(av[3]) == 1)
		return (write(2, "time to eat invalid\n", 21), 1);
	if (ft_atoi(av[4]) < 60 || chk_digit(av[4]) == 1)
		return (write(2, "time to sleep invalid\n", 22), 1);
	if (av[5] && (ft_atoi(av[5]) <= 0 || chk_digit(av[5]) == 1))
		return (write(2, "invalid num of time each philo should eat\n", 42), 1);
	return (0);
}

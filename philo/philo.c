/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:02:19 by asmalawl          #+#    #+#             */
/*   Updated: 2024/08/23 18:02:20 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (ac < 5 || ac > 6)
		return (write(2, "4 || 5 args expected\n", 21), 1);
	if (handel_error(av) == 1)
		return (1);
	set_data(&data, philos);
	set_forks(forks, ft_atoi(av[1]));
	set_philos(philos, &data, forks, av);
	thread_create(&data, forks);
	destroying(NULL, &data, forks);
	return (0);
}

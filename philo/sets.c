/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:02:04 by asmalawl          #+#    #+#             */
/*   Updated: 2024/08/23 18:02:05 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	set_input(t_philo *philo, char **av)
{
	philo->philos_n = ft_atoi(av[1]);
	philo->die_time = ft_atoi(av[2]);
	philo->eat_time = ft_atoi(av[3]);
	philo->sleep_time = ft_atoi(av[4]);
	if (av[5])
		philo->num_times_to_eat = ft_atoi(av[5]);
	else
		philo->num_times_to_eat = -1;
}

void	set_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks,
		char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		set_input(&philos[i], av);
		philos[i].start_time = get_current();
		philos[i].last_meal = get_current();
		philos[i].write_lock = &data->write_lock;
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].dead = &data->dead_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].philos_n - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	set_forks(pthread_mutex_t *forks, int philos_n)
{
	int	i;

	i = 0;
	while (i < philos_n)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	set_data(t_data *data, t_philo *philos)
{
	data->dead_flag = 0;
	data->philos = philos;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

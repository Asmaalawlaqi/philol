/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:02:12 by asmalawl          #+#    #+#             */
/*   Updated: 2024/08/23 18:02:13 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

static void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 1)
		ft_usleep(50);
	while (!dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (p);
}

int	thread_create(t_data *data, pthread_mutex_t *forks)
{

	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, data->philos) != 0)
		destroying("error thread creation", data, forks);
	i = 0;
	while (i < data->philos[0].philos_n)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]) != 0)
			destroying("error thread creation", data, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destroying("error in joining threads", data, forks);
	while (i < data->philos[0].philos_n)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destroying("error in joining threads", data, forks);
		i++;
	}
	return (0);
}

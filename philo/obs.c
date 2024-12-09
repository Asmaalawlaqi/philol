/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:02:24 by asmalawl          #+#    #+#             */
/*   Updated: 2024/08/23 18:02:25 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	print_action(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current() - philo->start_time;
	if (!dead(philo))
		printf("%zu philosopher %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	philosopher_dead(t_philo *philo, size_t die_time)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current() - philo->last_meal >= die_time && philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->philos_n)
	{
		if (philosopher_dead(&philos[i], philos[i].die_time))
		{
			print_action("died 💀", &philos[i], philos[i].id);
			pthread_mutex_lock(philos->dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	all_eats(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos->num_times_to_eat == -1)
		return (0);
	while (i < philos->philos_n)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten <= philos->num_times_to_eat)
		{
			pthread_mutex_unlock(philos[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	pthread_mutex_lock(philos->dead_lock);
	*philos->dead = 1;
	pthread_mutex_unlock(philos->dead_lock);
	return (1);
}


void	*monitor(void *p)
{
	t_philo	*d;

	d = (t_philo *)p;
	while (1)
		if (check_if_dead(d) == 1 || all_eats(d) == 1)
			break ;
	return (p);
}

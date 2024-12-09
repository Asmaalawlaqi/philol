/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:02:31 by asmalawl          #+#    #+#             */
/*   Updated: 2024/08/23 18:02:37 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	thinking(t_philo *philo)
{
	print_action("is thinking 🤔", philo, philo->id);
}

void	sleeping(t_philo *philo)
{
	print_action("is sleeping 😴", philo, philo->id);
	ft_usleep(philo->sleep_time);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_action("has taken a fork 🍴", philo, philo->id);
	if (philo->philos_n == 1)
	{
		ft_usleep(philo->die_time);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print_action("has taken a fork 🍴", philo, philo->id);
	philo->eating = 1;
	print_action("is eating 🍽️ 😋", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

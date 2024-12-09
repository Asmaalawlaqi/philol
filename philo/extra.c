/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:02:51 by asmalawl          #+#    #+#             */
/*   Updated: 2024/08/23 18:02:52 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char *s)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s++ == '-')
			sign = sign * -1;
	}
	while (*s >= '0' && *s <= '9')
	{
		if ((res > LONG_MAX / 10) || (res == LONG_MAX / 10 && (*s
					- 48) > LONG_MAX % 10))
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		res = res * 10 + (*s++ - 48);
	}
	return (res * sign);
}

void	destroying(char *s, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (s)
	{
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->philos[0].philos_n)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

size_t	get_current(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 21);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_current();
	while ((get_current() - start) < ms)
		usleep(500);
	return (0);
}

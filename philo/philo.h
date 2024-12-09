/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:01:57 by asmalawl          #+#    #+#             */
/*   Updated: 2024/08/23 18:01:58 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			die_time;
	size_t			start_time;
	int				philos_n;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_data
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_data;

int					chk_digit(char *arg);
int					handel_error(char **av);
void				set_data(t_data *data, t_philo *philos);
void				set_forks(pthread_mutex_t *forks, int philos_n);
void				set_philos(t_philo *philos, t_data *data,
						pthread_mutex_t *forks, char **av);
void				set_input(t_philo *philo, char **av);
int					dead(t_philo *philo);
int					thread_create(t_data *data, pthread_mutex_t *forks);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
void				print_action(char *str, t_philo *philo, int id);
int					philosopher_dead(t_philo *philo, size_t die_time);
int					check_if_dead(t_philo *p);
void				*monitor(void *p);
int					ft_strlen(char *s);
int					ft_atoi(const char *s);
void				destroying(char *s, t_data *data, pthread_mutex_t *forks);
size_t				get_current(void);
int					ft_usleep(size_t ms);
#endif

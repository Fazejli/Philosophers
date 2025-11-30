/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:08:06 by fadzejli          #+#    #+#             */
/*   Updated: 2025/11/16 17:56:09 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				num;
	int				nb_meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				nbr;
	long			start;
	int				stop;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				nbr_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write_lock;
	t_philo			*philo;
}	t_table;

// Init functions
int		check_args(char **av);
int		init_args(char **av, t_table *table);
int		init_philo(t_table *table);
int		init_forks(t_table *table);

// Routine functions
void	*routine(void *arg);
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);

// Monitor functions
void	*monitor_routine(void *arg);
int		check_death(t_table *table, t_philo *philo);
int		check_all_ate(t_table *table);

// Utils functions
int		free_all(t_table *table);
void	mess_error(char *str);
void	ft_putstr_error(char *str);
long	get_time(void);
void	locked_printf(t_philo *philo, char *msg);
int		get_stop(t_table *table);
void	set_stop(t_table *table);
long	get_last_meal(t_philo *philo);
void	set_last_meal(t_philo *philo, long time);
int		get_nb_meals(t_philo *philo);
void	increment_meals(t_philo *philo);
void	ft_usleep(long time_in_ms);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:41:34 by fadzejli          #+#    #+#             */
/*   Updated: 2025/11/16 18:00:17 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		locked_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		locked_printf(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		locked_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		locked_printf(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	locked_printf(philo, "is eating");
	set_last_meal(philo, get_time());
	ft_usleep(philo->table->time_eat);
	increment_meals(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	locked_printf(philo, "is sleeping");
	ft_usleep(philo->table->time_sleep);
}

static void	think(t_philo *philo)
{
	long	time_to_think;

	locked_printf(philo, "is thinking");
	if (philo->table->nbr % 2 == 0)
		return ;
	time_to_think = (philo->table->time_die
			- (get_time() - get_last_meal(philo))
			- philo->table->time_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	ft_usleep(time_to_think);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->nbr == 1)
	{
		locked_printf(philo, "has taken a fork");
		ft_usleep(philo->table->time_die);
		return (NULL);
	}
	if (philo->num % 2 == 0)
		ft_usleep(philo->table->time_eat / 2);
	while (!get_stop(philo->table))
	{
		eat(philo);
		if (philo->table->nbr_must_eat > 0
			&& get_nb_meals(philo) >= philo->table->nbr_must_eat)
			break ;
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

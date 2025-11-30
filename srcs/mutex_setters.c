/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 18:00:00 by fadzejli          #+#    #+#             */
/*   Updated: 2025/11/16 18:01:28 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_stop(t_table *table)
{
	int	value;

	pthread_mutex_lock(&table->lock);
	value = table->stop;
	pthread_mutex_unlock(&table->lock);
	return (value);
}

void	set_stop(t_table *table)
{
	pthread_mutex_lock(&table->lock);
	table->stop = 1;
	pthread_mutex_unlock(&table->lock);
}

long	get_last_meal(t_philo *philo)
{
	long	value;

	pthread_mutex_lock(&philo->meal_lock);
	value = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	return (value);
}

void	set_last_meal(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->meal_lock);
}

int	get_nb_meals(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&philo->meal_lock);
	value = philo->nb_meals;
	pthread_mutex_unlock(&philo->meal_lock);
	return (value);
}

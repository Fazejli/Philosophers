/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 18:01:46 by fadzejli          #+#    #+#             */
/*   Updated: 2025/11/16 18:02:14 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	increment_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->meal_lock);
}

int	free_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philo[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&table->lock);
	pthread_mutex_destroy(&table->write_lock);
	free(table->forks);
	free(table->philo);
	return (0);
}

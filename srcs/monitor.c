/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:59:29 by fadzejli          #+#    #+#             */
/*   Updated: 2025/11/16 17:58:34 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death(t_table *table, t_philo *philo)
{
	long	time_since_meal;

	time_since_meal = get_time() - get_last_meal(philo);
	if (time_since_meal > table->time_die)
	{
		pthread_mutex_lock(&table->write_lock);
		if (!table->stop)
		{
			printf("%ld %d died\n", get_time() - table->start, philo->num);
			set_stop(table);
		}
		pthread_mutex_unlock(&table->write_lock);
		return (1);
	}
	return (0);
}

int	check_all_ate(t_table *table)
{
	int	i;
	int	finished;

	if (table->nbr_must_eat <= 0)
		return (0);
	i = 0;
	finished = 0;
	while (i < table->nbr)
	{
		if (get_nb_meals(&table->philo[i]) >= table->nbr_must_eat)
			finished++;
		i++;
	}
	if (finished == table->nbr)
	{
		set_stop(table);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!get_stop(table))
	{
		i = 0;
		while (i < table->nbr)
		{
			if (check_death(table, &table->philo[i]))
				return (NULL);
			i++;
		}
		if (check_all_ate(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

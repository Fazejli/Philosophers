/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:28:26 by fadzejli          #+#    #+#             */
/*   Updated: 2025/11/16 17:59:36 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][0] == '-')
			return (1);
		if (av[i][0] == '+')
			j++;
		if (!av[i][j])
			return (1);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init_args(char **av, t_table *table)
{
	if (table->nbr <= 0 || table->nbr > 200)
		return (1);
	table->time_die = atoi(av[2]);
	table->time_eat = atoi(av[3]);
	table->time_sleep = atoi(av[4]);
	if (table->time_die < 60 || table->time_eat < 60 || table->time_sleep < 60)
		return (1);
	table->start = get_time();
	table->stop = 0;
	table->nbr_must_eat = -1;
	if (av[5])
	{
		table->nbr_must_eat = atoi(av[5]);
		if (table->nbr_must_eat == 0)
			return (1);
	}
	return (0);
}

int	init_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->nbr);
	if (!table->philo)
		return (1);
	while (i < table->nbr)
	{
		table->philo[i].num = i + 1;
		table->philo[i].nb_meals = 0;
		table->philo[i].last_meal = table->start;
		table->philo[i].table = table;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->nbr];
		if (pthread_mutex_init(&table->philo[i].meal_lock, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&table->lock, NULL))
		return (1);
	if (pthread_mutex_init(&table->write_lock, NULL))
		return (1);
	return (0);
}

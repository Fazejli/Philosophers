/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:08:06 by fadzejli          #+#    #+#             */
/*   Updated: 2025/11/16 17:59:39 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	creat_join(t_table *table)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < table->nbr)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				routine, &table->philo[i]))
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, table))
		return (1);
	i = 0;
	while (i < table->nbr)
	{
		if (pthread_join(table->philo[i].thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(monitor, NULL))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_table		table;

	if ((ac != 6 && ac != 5) || (check_args(av)) == 1)
		mess_error("Check your args.");
	table.nbr = atoi(av[1]);
	if (init_args(av, &table))
		mess_error("Args error.");
	if (init_forks(&table))
		mess_error("Forks init fail");
	if (init_philo(&table))
	{
		free_all(&table);
		mess_error("Philo init fail");
	}
	if (creat_join(&table))
	{
		free_all(&table);
		mess_error("Thread join fail.");
	}
	free_all(&table);
	return (0);
}

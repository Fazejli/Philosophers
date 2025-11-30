/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:45:40 by fadzejli          #+#    #+#             */
/*   Updated: 2025/11/16 18:02:08 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

void	ft_usleep(long time_in_ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(500);
}

void	locked_printf(t_philo *philo, char *msg)
{
	long	timestamp;

	if (!philo || !philo->table)
		return ;
	pthread_mutex_lock(&philo->table->write_lock);
	if (!get_stop(philo->table))
	{
		timestamp = get_time() - philo->table->start;
		printf("%ld %d %s\n", timestamp, philo->num, msg);
	}
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	ft_putstr_error(char *str)
{
	int	i;

	if (!str)
	{
		ft_putstr_error("ERROR");
		return ;
	}
	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
}

void	mess_error(char *str)
{
	ft_putstr_error(str);
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:31:45 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/13 17:33:25 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	store_value(t_data *data, char **av)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	if (!av[5])
		data->number_of_times_each_philosopher_must_eat = -1;
}

size_t	count_time(void)
{
	size_t			tm;
	struct timeval	time;

	gettimeofday(&time, NULL);
	tm = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (tm);
}

void	sleeping(size_t i, int j)
{
	size_t	l;

	l = 0;
	while (1)
	{
		if (count_time() >= i + j)
			break ;
		usleep(100);
	}
}

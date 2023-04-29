/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:31:45 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/29 19:37:14 by abenmous         ###   ########.fr       */
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

void	sleeping(t_philo *philo, size_t i, int j)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->r1);
		if (count_time() >= i + j || philo->data->br == 0)
		{
			pthread_mutex_unlock(&philo->data->r1);
			break ;
		}
		pthread_mutex_unlock(&philo->data->r1);
		usleep(100);
	}
}

void	printing(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->r1);
	if (philo->data->br == 1)
	{
		pthread_mutex_unlock(&philo->data->r1);
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n", count_time()
			- philo->data->first_time, philo->id + 1, s);
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_lock(&philo->data->r1);
	}
	pthread_mutex_unlock(&philo->data->r1);
}

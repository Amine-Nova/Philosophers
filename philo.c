/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:37:05 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/28 20:57:49 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	creat_mutex(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = data->number_of_philosophers;
	data->forks = malloc(sizeof(pthread_mutex_t) * i);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->races, NULL);
	pthread_mutex_init(&data->r1, NULL);
	while (j < i)
	{
		pthread_mutex_init(&data->forks[j], NULL);
		j++;
	}
}

void	*thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_philosophers != 1)
	{	
		pthread_mutex_lock(&philo->data->races);
		philo->number_time_philo_eat = 0;
		pthread_mutex_unlock(&philo->data->races);
	}
	pthread_mutex_lock(&philo->data->r1);
	while (philo->data->br)
	{
		pthread_mutex_unlock(&philo->data->r1);
		routine(philo);
		pthread_mutex_lock(&philo->data->r1);
	}
	pthread_mutex_unlock(&philo->data->r1);
	return (EXIT_SUCCESS);
}

void	creat_thread(t_data *data)
{
	int	i;
	int	j;

	if (data->number_of_philosophers % 2 == 0)
		data->prime = 1;
	if (data->number_of_philosophers % 2 == 1)
		data->prime = 2;
	i = data->number_of_philosophers;
	j = 0;
	data->philos = malloc(sizeof(t_philo) * i);
	data->first_time = count_time();
	data->br = 1;
	while (j < i)
	{
		data->philos[j].last_time_eat = count_time();
		data->philos[j].id = j;
		data->philos[j].data = data;
		pthread_create(&data->philos[j].th, NULL, thread, &data->philos[j]);
		usleep(50);
		j++;
	}
}

int	is_death(t_data *data)
{
	int	j;
	int	d;

	d = 1;
	j = -1;
	while (++j < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->races);
		if (data->philos[j].number_time_philo_eat
			!= data->number_of_times_each_philosopher_must_eat)
			d = 0;
		pthread_mutex_unlock(&data->races);
	}
	pthread_mutex_lock(&data->r1);
	if (d == 1)
	{
		data->br = 0;
		pthread_mutex_unlock(&data->r1);
		return (1);
	}
	pthread_mutex_unlock(&data->r1);
	j = is_death2(data);
	if (j == 1)
		return (1);
	return (0);
}

int	is_death2(t_data *data)
{
	int	j;

	j = -1;
	while (++j < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->races);
		if (count_time() - data->philos[j].last_time_eat >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->races);
			pthread_mutex_lock(&data->r1);
			data->br = 0;
			usleep (500);
			printf("%lu %d died\n", count_time()
				- data->first_time, data->philos[j].id + 1);
			pthread_mutex_unlock(&data->r1);
			if (data->number_of_philosophers == 1)
				pthread_mutex_unlock(&data->forks[0]);
			return (1);
		}
		pthread_mutex_unlock(&data->races);
		usleep (100);
	}
	return (0);
}

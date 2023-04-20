/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:37:05 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/20 02:32:00 by abenmous         ###   ########.fr       */
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
	pthread_mutex_init(&philo->data->print, NULL);
	pthread_mutex_init(&philo->data->races, NULL);
	while (1)
		routine(philo);
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
	while (j < i)
	{
		data->philos[j].last_time_eat = count_time();
		data->philos[j].time_start = count_time();
		data->philos[j].id = j;
		data->philos[j].data = data;
		pthread_create(&data->philos[j].th, NULL, thread, &data->philos[j]);
		usleep(50);
		j++;
	}
}

int	is_death(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->races);
	if (data->number_of_times_each_philosopher_must_eat
		== data->philos[data->number_of_philosophers
			- data->prime].number_time_philo_eat
		&& data->number_of_times_each_philosopher_must_eat != -1)
	{
		pthread_mutex_unlock(&data->races);
		pthread_mutex_lock(&data->print);
		return (1);
	}
	i = is_death2(data);
	if (i == 1)
		return (1);
	pthread_mutex_unlock(&data->races);
	return (0);
}

int	is_death2(t_data *data)
{
	int	j;

	j = -1;
	while (++j < data->number_of_philosophers)
	{
		if (count_time() - data->philos[j].last_time_eat >= data->time_to_die)
		{
			pthread_mutex_lock(&data->print);
			pthread_mutex_unlock(&data->races);
			printf("%lu %d died\n", count_time()
				- data->first_time, data->philos->id + 1);
			return (1);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:37:05 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/18 22:03:58 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void creat_mutex(t_data *data)
{
	int i;
	int j;

	j = 0;
	i = data->number_of_philosophers;
	data->forks = malloc(sizeof(pthread_mutex_t) * i);
	while (j < i)
	{
		pthread_mutex_init(&data->forks[j], NULL);
		j++;
	}
}

void *thread(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->number_time_philo_eat = 0;
	pthread_mutex_init(&philo->data->print, NULL);
	pthread_mutex_init(&philo->data->races, NULL);
	while (1)
		routine(philo);
	return (EXIT_SUCCESS);
}

void routine(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
		usleep(500);
	is_thinking(philo);
	taken_fork(philo);
	philo->number_time_philo_eat++;
	is_sleeping(philo);
}

void	creat_thread(t_data *data)
{
	int i;
	int j;

	i = data->number_of_philosophers;
	j = 0;
	data->philos = malloc(sizeof(t_philo) * i);
	data->first_time = count_time();
	while (j < i)
	{
		data->philos[j].time_start = count_time();
		data->philos[j].id = j;
		data->philos[j].data = data;
		pthread_create(&data->philos[j].th, NULL, thread, &data->philos[j]);
		usleep(50);
		j++;
	}
	j = 0;
	while (j < i)
		pthread_mutex_destroy(&data->forks[j++]);
	while(j < i)
		pthread_detach(data->philos[j++].th);
}

int is_death(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_lock(&data->races);
	if (data->number_of_times_each_philosopher_must_eat
			== data->philos[data->number_of_philosophers - 1].number_time_philo_eat)
	{
		pthread_mutex_unlock(&data->races);
		pthread_mutex_lock(&data->print);
		return (1);
	}
	if (count_time() - data->philos->last_time_eat >= data->time_to_die)
	{
		if (count_time() - data->philos->last_time_eat >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->races);
			pthread_mutex_lock(&data->print);
			printf("%lu %d died\n", count_time() - data->first_time, data->philos->id + 1);
			return (1);
		}
	}
	pthread_mutex_unlock(&data->races);
	return (0);
}

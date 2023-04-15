/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:37:05 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/15 21:39:04 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	creat_mutex(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = data->number_of_philosophers;
	data->forks = malloc(sizeof(pthread_mutex_t) * i);
	while (j <= i)
	{
		pthread_mutex_init(&data->forks[j], NULL);
		j++;
	}
}

void	*thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->number_time_philo_eat = 0;
	pthread_mutex_init(&philo->data->print, NULL);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
		routine(philo);
	return (EXIT_SUCCESS);
}

void	routine(t_philo	*philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d is thinking\n", count_time()
		- philo->data->first_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d has taken a fork\n", count_time()
		- philo->data->first_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->forks[(philo->id + 1)
		% philo->data->number_of_philosophers]);
	routine2(philo);
}

void routine2(t_philo *philo)
{
	philo->last_time_eat = count_time();
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d is eating\n", count_time()
		- philo->data->first_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	sleeping(count_time(), philo->data->time_to_eat);
	philo->number_time_philo_eat++;
	// printf("%ld %d %d\n", count_time()
	// 	- philo->data->first_time, philo->number_time_philo_eat, philo->id);
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	pthread_mutex_unlock(&philo->data->forks[(philo->id + 1)
		% philo->data->number_of_philosophers]);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d is sleeping\n", count_time()
		- philo->data->first_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	sleeping(count_time(), philo->data->time_to_sleep);
}

void	creat_thread(t_data *data)
{
	int	i;
	int	j;

	i = data->number_of_philosophers;
	j = 0;
	data->philos = malloc(sizeof(t_philo) * i);
	data->first_time = count_time();
	while (j < i)
	{
		data->philos[j].time_start = count_time();
		data->philos[j].id = j + 1;
		data->philos[j].data = data;
		pthread_create(&data->philos[j].th, NULL, thread, &data->philos[j]);
		usleep(50);
		j++;
	}
	j = 0;
	while (j < i)
		pthread_mutex_destroy(&data->forks[j++]);
}

int is_death(t_data *data)
{
	int j;

	j = 0;
	if(count_time() - data->philos->last_time_eat >= (size_t)data->time_to_die)
	{
		pthread_mutex_lock(&data->print);
		printf("%lu %d is dead\n", count_time() - data->first_time, data->philos->id);
		return (1);
	}
	return (0);
}

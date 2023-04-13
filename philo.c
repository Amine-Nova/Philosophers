/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:37:05 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/13 17:33:50 by abenmous         ###   ########.fr       */
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
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
		routine(philo);
	return (EXIT_SUCCESS);
}

void	routine(t_philo	*philo)
{
	printf("%ld %d is thinking\n", count_time()
		- philo->data->first_time, philo->id);
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	printf("%ld %d has taken a fork\n", count_time()
		- philo->data->first_time, philo->id);
	pthread_mutex_lock(&philo->data->forks[(philo->id + 1)
		% philo->data->number_of_philosophers]);
	printf("%ld %d has taken a fork\n", count_time()
		- philo->data->first_time, philo->id);
	printf("%ld %d is eating\n", count_time()
		- philo->data->first_time, philo->id);
	philo->number_time_philo_eat++;
	printf("%ld %d %d\n", count_time()
		- philo->data->first_time, philo->number_time_philo_eat, philo->id);
	sleeping(count_time(), philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	pthread_mutex_unlock(&philo->data->forks[(philo->id + 1)
		% philo->data->number_of_philosophers]);
	printf("%ld %d is sleeping\n", count_time()
		- philo->data->first_time, philo->id);
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
		data->philos[j].id = j + 1;
		data->philos[j].data = data;
		pthread_create(&data->philos[j].th, NULL, thread, &data->philos[j]);
		usleep(50);
		j++;
	}
	j = 0;
	while (j < i)
		pthread_join(data->philos[j++].th, NULL);
	j = 0;
	while (j < i)
		pthread_mutex_destroy(&data->forks[j++]);
}

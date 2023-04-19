/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:37:13 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/19 21:18:45 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d is eating\n", count_time()
		- philo->data->first_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print);
}

void	is_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d is thinking\n", count_time()
		- philo->data->first_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print);
}

void	taken_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d has taken a fork\n", count_time()
		- philo->data->first_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->forks[(philo->id + 1)
		% philo->data->number_of_philosophers]);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d has taken a fork\n", count_time()
		- philo->data->first_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->races);
	philo->last_time_eat = count_time();
	time_to_eat(philo);
	pthread_mutex_unlock(&philo->data->races);
	sleeping(count_time(), philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	pthread_mutex_unlock(&philo->data->forks[(philo->id + 1)
		% philo->data->number_of_philosophers]);
}

void	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d is sleeping\n", count_time()
		- philo->data->first_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print);
	sleeping(count_time(), philo->data->time_to_sleep);
}

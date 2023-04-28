/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:37:13 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/28 20:21:01 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
		usleep(500);
	is_thinking(philo);
	taken_fork(&philo);
	pthread_mutex_lock(&philo->data->races);
	philo->number_time_philo_eat++;
	pthread_mutex_unlock(&philo->data->races);
	is_sleeping(philo);
}

void	time_to_eat(t_philo *philo)
{
	printing(philo, "is eating");
}

void	is_thinking(t_philo *philo)
{
	printing(philo, "is thinking");
}

void	taken_fork(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->data->forks[(*philo)->id]);
	printing((*philo), "has taken a fork");
	pthread_mutex_lock(&(*philo)->data->forks[((*philo)->id + 1)
		% (*philo)->data->number_of_philosophers]);
	printing((*philo), "has taken a fork");
	pthread_mutex_lock(&(*philo)->data->races);
	(*philo)->last_time_eat = count_time();
	time_to_eat((*philo));
	pthread_mutex_unlock(&(*philo)->data->races);
	sleeping(count_time(), (*philo)->data->time_to_eat);
	pthread_mutex_unlock(&(*philo)->data->forks[(*philo)->id]);
	pthread_mutex_unlock(&(*philo)->data->forks[((*philo)->id + 1)
		% (*philo)->data->number_of_philosophers]);
}

void	is_sleeping(t_philo *philo)
{
	printing(philo, "is sleeping");
	sleeping(count_time(), philo->data->time_to_sleep);
}

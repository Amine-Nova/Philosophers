/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:37:05 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/11 22:37:05 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (ac < 5 || ac > 6)
		exit_error();
	check_error(av);
	store_value(data, av);
	creat_mutex(data);
	creat_thread(data);
}

void	store_value(t_data *data, char **av)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
}
void	creat_mutex(t_data *data)
{
	int i;
	int j;

	j = 0;
	i = data->number_of_philosophers;
	data->forks = malloc(sizeof(pthread_mutex_t) * i);
	while(j <= i)
	{
		pthread_mutex_init(&data->forks[j], NULL);
		j++;
	}
}

size_t count_time()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return(time.tv_usec);
}

size_t count_time2()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return(time.tv_sec);
}

void	*thread(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while(1)
	{
		printf("%ld %d\tis thinking\n", count_time() / 1000, philo->id);
		pthread_mutex_lock(&philo->data->forks[philo->id]);
		pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->number_of_philosophers]);
		printf("%ld %d\thas taken a fork\n", count_time() / 1000,philo->id);
		printf("%ld %d\tis eating\n", count_time() / 1000,philo->id);
		philo->number_time_philo_eat++;
		usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
		pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % philo->data->number_of_philosophers]);
		printf("%ld %d\tis sleeping\n", count_time() / 1000, philo->id);
	}
	return (EXIT_SUCCESS);
}

void	creat_thread(t_data *data)
{
	int	i;
	int j;
	
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

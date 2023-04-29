/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:31:19 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/29 23:04:01 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	store_all(t_data *data, char **av)
{
	int	d;

	store_value(data, av);
	creat_mutex(data);
	if (creat_thread(data) == 1)
		return (1);
	d = 1;
	while (1)
	{
		if (is_death(data, d) == 1)
			break ;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ac < 5 || ac > 6)
	{
		free(data);
		printf("error\n");
		return (1);
	}
	if (check_error(av) == 1)
	{
		free(data);
		return (1);
	}
	if (store_all(data, av))
		return (1);
	if (data->number_of_philosophers == 1)
		pthread_mutex_unlock(&data->forks[0]);
	free_stuff(data);
	return (0);
}

void	free_stuff(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_join(data->philos[i].th, NULL);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->r1);
	pthread_mutex_destroy(&data->races);
	free(data->philos);
	free(data->forks);
	free(data);
	return ;
}

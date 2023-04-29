/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:31:19 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/29 13:50:25 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	store_all(t_data *data, char **av)
{
	store_value(data, av);
	creat_mutex(data);
	creat_thread(data);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int			d;

	data = malloc(sizeof(t_data));
	data->i = 0;
	if (ac < 5 || ac > 6)
	{
		free(data);
		printf("error\n");
		return (1);
	}
	data->i = check_error(av);
	if (data->i == 1)
	{
		free(data);
		return (1);
	}
	store_all(data, av);
	d = 1;
	while (1)
	{
		if (is_death(data, d) == 1)
			break ;
	}
	free_stuff(data);
	return (0);
}

void	free_stuff(t_data *data)
{
	int	i;

	i = -1;
	if (data->number_of_philosophers == 1)
		pthread_mutex_unlock(&data->forks[0]);
	while (++i < data->number_of_philosophers)
	{
		pthread_join(data->philos[i].th, NULL);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->r1);
	pthread_mutex_destroy(&data->races);
	free(data->philos);
	free(data->forks);
	free(data);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:31:19 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/26 21:40:27 by abenmous         ###   ########.fr       */
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
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (ac < 5 || ac > 6)
	{
		free(data);
		printf("error\n");
		return (1);
	}
	i = check_error(av);
	if (i == 1)
	{
		free(data);
		return (1);
	}
	store_all(data, av);
	while (1)
	{
		i = is_death(data);
		if (i == 1)
			break ;
	}
	return (0);
}

void	free_stuff(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_detach(data->philos[i].th);
	}
	free(data->philos);
	free(data->forks);
	free(data);
	return ;
}

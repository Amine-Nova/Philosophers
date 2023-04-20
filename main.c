/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:31:19 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/20 02:52:28 by abenmous         ###   ########.fr       */
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
		exit_error();
	i = check_error(av);
	if (i == 1)
		return (0);
	store_all(data, av);
	while (1)
	{
		i = is_death(data);
		if (i == 1)
			break ;
	}
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_detach(data->philos[i].th);
	}
	free(data->forks);
	free(data->philos);
}

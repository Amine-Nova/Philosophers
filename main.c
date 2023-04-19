/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:31:19 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/19 18:30:57 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;
	int		j;

	i = 0;
	j = 1;
	data = malloc(sizeof(t_data));
	if (ac < 5 || ac > 6)
		exit_error();
	j = check_error(av);
	if (j == 0)
		return (0);
	store_value(data, av);
	creat_mutex(data);
	creat_thread(data);
	while (1)
	{
		i = is_death(data);
		if (i == 1)
			break ;
	}
}

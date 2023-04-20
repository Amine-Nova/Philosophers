/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:37:02 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/20 02:20:22 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	check_error(char **av)
{
	int	i;
	int	j;
	int	q;

	i = 0;
	q = 1;
	while (av[++i])
	{
		if (fun_strlen(av[i]) > 11 || ft_atoi(av[i]) > INT_MAX
			|| ft_atoi(av[i]) <= 0)
			q = exit_error();
		if (q == 0)
			return (0);
		j = -1;
		while (av[i][++j])
			if (av[i][j] == '-' || (av[i][j] == '+' &&
			(av[i][j + 1] < '0' || av[i][j + 1] > '9'))
			|| ((av[i][j] < '0' || av[i][j] > '9') &&
			av[i][j] != '+' && av[i][j] != ' '))
				q = exit_error();
		if (q == 0)
			return (1);
	}
	return (0);
}

int	exit_error(void)
{
	printf("error\n");
	return (0);
}

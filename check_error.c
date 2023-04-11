/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:37:02 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/04 19:30:57 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	check_error(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		if (fun_strlen(av[i]) > 11 || ft_atoi(av[i]) > INT_MAX
			|| ft_atoi(av[i]) <= 0)
			exit_error();
		j = -1;
		while (av[i][++j])
			if (av[i][j] == '-' || (av[i][j] == '+' &&
			(av[i][j + 1] < '0' || av[i][j + 1] > '9'))
			|| ((av[i][j] < '0' || av[i][j] > '9') &&
			av[i][j] != '+' && av[i][j] != ' '))
				exit_error();
	}
}

void	exit_error(void)
{
	printf("error\n");
	exit(1);
}

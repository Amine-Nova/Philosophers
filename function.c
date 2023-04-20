/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:37:07 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/20 02:49:19 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

size_t	fun_strlen(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i] && str[i] != ' ')
	{
		i++;
		j++;
	}
	while (str[i] == ' ')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
		exit_error();
	return (j);
}

size_t	ft_atoi(const char *str)
{
	size_t	a;
	size_t	b;
	size_t	c;

	a = 0;
	b = 1;
	c = 0;
	while (str[a] == 32 || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == '+' || str[a] == '-')
	{
		if (str[a] == '-')
			b = -1;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		c = c * 10 + str[a] - 48;
		a++;
	}
	return (c * b);
}

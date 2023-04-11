/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:37:10 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/11 22:28:04 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<limits.h>
# include<stdio.h>
# include<pthread.h>
# include<unistd.h>
# include<stdlib.h>
#include<sys/time.h>

struct s_data;

typedef	struct s_philo
{
	int				id;
	pthread_t		th;
	int			number_time_philo_eat;
	struct s_data	*data;
}	t_philo;


typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	size_t				first_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_data;

void	exit_error(void);
void	check_error(char **av);
size_t	fun_strlen(char *str);
int		ft_atoi(const char *str);
void	store_value(t_data *data, char **av);
void	creat_thread(t_data *data);
void	creat_mutex(t_data *data);
size_t	count_time();
size_t count_time2();

#endif 
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:37:10 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/15 21:36:31 by abenmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<limits.h>
# include<stdio.h>
# include<pthread.h>
# include<unistd.h>
# include<stdlib.h>
# include<sys/time.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	pthread_t		th;
	size_t			time_start;
	int				number_time_philo_eat;
	size_t			last_time_eat;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	size_t			first_time;
	t_philo			*philos;
	pthread_mutex_t print;
	pthread_mutex_t	*forks;
}	t_data;

void	exit_error(void);
void	check_error(char **av);
size_t	fun_strlen(char *str);
int		ft_atoi(const char *str);
void	store_value(t_data *data, char **av);
void	creat_thread(t_data *data);
void	creat_mutex(t_data *data);
size_t	count_time(void);
void	sleeping(size_t i, int j);
void	routine(t_philo	*philo);
int		is_death(t_data *data);
void	routine2(t_philo *philo);
#endif 
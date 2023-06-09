/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenmous <abenmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:37:10 by abenmous          #+#    #+#             */
/*   Updated: 2023/04/29 22:50:28 by abenmous         ###   ########.fr       */
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
	int				number_time_philo_eat;
	size_t			last_time_eat;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				br;
	int				prime;
	int				number_of_times_each_philosopher_must_eat;
	size_t			first_time;
	t_philo			*philos;
	pthread_mutex_t	print;
	pthread_mutex_t	races;
	pthread_mutex_t	r1;
	pthread_mutex_t	*forks;
}	t_data;

int		exit_error(void);
int		store_all(t_data *data, char **av);
int		check_error(char **av);
size_t	fun_strlen(char *str);
size_t	ft_atoi(const char *str);
void	store_value(t_data *data, char **av);
int		creat_thread(t_data *data);
int		creat_mutex(t_data *data);
size_t	count_time(void);
void	sleeping(t_philo *philo, size_t i, int j);
void	routine(t_philo	*philo);
int		is_death(t_data *data, int d);
void	time_to_eat(t_philo *philo);
void	is_thinking(t_philo *philo);
void	taken_fork(t_philo *philo);
void	is_sleeping(t_philo *philo);
int		is_death2(t_data *data);
void	free_stuff(t_data *data);
void	printing(t_philo *philo, char *s);
int		check_last(t_data *data, int d);
int		ft_strcmp(char *s1, char *s2);
#endif 
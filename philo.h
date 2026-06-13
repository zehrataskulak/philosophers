/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaskula <ztaskula@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:20:16 by ztaskula          #+#    #+#             */
/*   Updated: 2026/06/13 20:31:15 by ztaskula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_must_eat;
	long long		start_time;
	int				dead_cntrl;
	pthread_mutex_t	mutex_dead_cntrl;
	pthread_mutex_t	mutex_printf;
}	t_args;

typedef struct s_philo
{
	int				philo_id;
	int				eat_times;
	int				right_fork_id;
	int				left_fork_id;
	pthread_t		thread;
	struct s_args	*args;
	pthread_mutex_t	*fork_mutex;
	long long		last_meal_time;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	mutex_eat_times;
}	t_philo;

long		z_atoi(const char *str);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
int			f_dead_cntrl(t_philo *philo);
int			print_action(char *action, t_philo *philo);
int			philo_eat(t_philo *philo);
int			philo_sleep(t_philo *philo);
int			philo_think(t_philo *philo);
int			check_meal_times(t_philo *philo);
int			check_meal_limit(t_philo *philo);
int			check_eat_status(t_philo *philo, int i, int must_eat);
void		read_args(int argc, char **argv, t_args *args);
void		init_mutexes(pthread_mutex_t **fork_mutex, int fork_num);
void		init_philos(t_philo **philo, t_args *args);
void		free_args(t_args *args);
void		free_philo(t_philo **philo);
void		*philos_function(void *arg);
void		set_dead_flag(t_philo *philo, int i);
long long	find_time(long long start_time);

#endif
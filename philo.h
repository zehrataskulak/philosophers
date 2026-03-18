/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 08:32:42 by zzehra            #+#    #+#             */
/*   Updated: 2026/03/16 12:34:09 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct s_args{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    int dead_cntrl;
} t_args;



typedef struct s_philo{
    int philo_id;
    long long last_meal;
    int eat_times;
    int right_fork_id;
    int left_fork_id;
    pthread_t thread;
    struct s_args *args;
    pthread_mutex_t *fork_mutex;
    long long start_time;
    int dead_control;
} t_philo;

long	z_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
void read_args(int argc, char **argv, t_args *args);
void init_mutexes(pthread_mutex_t **fork_mutex, int fork_num);
void    init_philos(t_philo **philo, t_args *args);
void free_philo(t_philo **philo);
void *philos_function(void *arg);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 08:32:42 by zzehra            #+#    #+#             */
/*   Updated: 2026/04/28 09:57:28 by zzehra           ###   ########.fr       */
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
    int number_of_times_must_eat;
    
    long long start_time;
    int dead_cntrl;
    pthread_mutex_t mutex_dead_cntrl;//

    //long long start_time;
} t_args;


typedef struct s_philo{
    int philo_id;   
    int eat_times;
    int right_fork_id;
    int left_fork_id;
    pthread_t thread;
    struct s_args *args;
    pthread_mutex_t *fork_mutex;
    
    long long last_meal_time;
    pthread_mutex_t mutex_last_meal;
} t_philo;

long	z_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
int f_dead_cntrl(t_philo *philo);
void read_args(int argc, char **argv, t_args *args);
void init_mutexes(pthread_mutex_t **fork_mutex, int fork_num);
void    init_philos(t_philo **philo, t_args *args);
void free_philo(t_philo **philo);
void *philos_function(void *arg);
long long find_time(long long start_time);


#endif
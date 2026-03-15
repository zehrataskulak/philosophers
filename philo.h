/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 08:32:42 by zzehra            #+#    #+#             */
/*   Updated: 2026/03/15 16:53:11 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct s_args{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
} t_args;

typedef struct s_philo{
    int philo_id;
    long long last_meal;
    int eat_times;
    int right_fork_id;
    int left_fork_id;
    pthread_t thread;
    struct s_args *args;
} t_philo;

long	z_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
int read_args(int argc, char **argv, t_args *args);
void    init_philo(t_philo **philo, t_args args);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 08:32:42 by zzehra            #+#    #+#             */
/*   Updated: 2025/12/24 09:41:43 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>


typedef struct s_args{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    // int number_of_times_each_philosopher_must_eat; ??
} t_args;

int	ft_atoi(const char *str);
int read_args(int argc, char **argv, t_args *args);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 09:12:20 by zzehra            #+#    #+#             */
/*   Updated: 2026/03/15 16:51:35 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void assign_args(int argc, char **argv, t_args *args)
{
    args->number_of_philosophers = z_atoi(argv[1]);
    args->time_to_die = z_atoi(argv[2]);
    args->time_to_eat = z_atoi(argv[3]);
    args->time_to_sleep = z_atoi(argv[4]);
    if(argc == 6)
        args->number_of_times_each_philosopher_must_eat = z_atoi(argv[5]);
}

int argument_error(int argc, char **argv)
{
    int i;
    
    i = 1;
    while(i < argc)
    {
        if(ft_strchr(argv[i], '.'))
        {
            write(1, "Argument error!\n", 17);
            return (-1);
        }
        i++;
    }
    i = 1;
    while(i < 5)
    {
        if(!z_atoi(argv[i]) || z_atoi(argv[i]) < 0)
        {
            write(1, "Argument error!\n", 17);
            return (-1);
        }
        i++;
    }
    return (0);
}

int read_args(int argc, char **argv, t_args *args)
{
    
    if(argc > 6 || argc < 5)
    {
        write(1, "Invalid number of arguments!\n", 30);
        return (-1);
    }
    
    if(argument_error(argc, argv) == -1)
        return (-1);
    
    if(argc == 6 && ((z_atoi(argv[5]) == 0 && argv[5][0] != '0') || (z_atoi(argv[5]) < 0)))
    {
        write(1, "Argument error!\n", 17);
        return (-1);
    }
    else if(argc == 6 && (z_atoi(argv[5]) == 0 && argv[5][1]))
    {
        write(1, "Argument error!\n", 17);
        return (-1);
    }
    
    assign_args(argc, argv, args);
    return (0);
}
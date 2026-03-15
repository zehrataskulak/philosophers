/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 09:13:08 by zzehra            #+#    #+#             */
/*   Updated: 2026/03/15 16:40:15 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_mutexes(pthread_mutex_t **fork_mutex, int fork_num)
{
    int i;

    i = 0;
    *fork_mutex = malloc(sizeof(pthread_mutex_t) * fork_num);
    if(!(*fork_mutex))
        return ;
    while(i < fork_num)
    {   
        if(pthread_mutex_init(&(*fork_mutex)[i], NULL))
        {
            while (--i >= 0)
                pthread_mutex_destroy(&(*fork_mutex)[i]);
            free(*fork_mutex);
            write(1, "Error: mutex init failed\n", 26);
            exit(1);
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    t_args args;
    pthread_mutex_t *fork_mutex;
    //t_philo *philo;
  
    if(read_args(argc, argv, &args) == -1)
        return (-1);
    start_mutexes(&fork_mutex, args.number_of_philosophers);
    
    
  
    /*printf("%d\n%d\n%d\n%d\n", args.number_of_philosophers, args.time_to_die, args.time_to_eat, args.time_to_sleep);
    if(argc == 6)
        printf("%d\n", args.number_of_times_each_philosopher_must_eat);*/
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_srcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 17:59:43 by zzehra            #+#    #+#             */
/*   Updated: 2026/04/28 09:58:00 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_mutexes(pthread_mutex_t **fork_mutex, int fork_num)
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

void init_philos(t_philo **philo, t_args *args)
{
    pthread_mutex_t *fork_mutex;
    int i;
    struct timeval	tv;
    
    *philo = malloc(sizeof(t_philo) * args->number_of_philosophers);
    if(!(*philo))
        return ;
    init_mutexes(&fork_mutex, args->number_of_philosophers);
    
    gettimeofday(&tv, NULL);
    i = 0;
    while(i < args->number_of_philosophers)
    {
        (*philo)[i].philo_id = i + 1;
        (*philo)[i].left_fork_id = (i + 1) % args->number_of_philosophers;
        (*philo)[i].right_fork_id = i;
        (*philo)[i].eat_times = 0;
        (*philo)[i].args = args;
        (*philo)[i].last_meal_time = 0;
        (*philo)[i].thread = 0;
        (*philo)[i].fork_mutex = fork_mutex;
        pthread_mutex_init(&(*philo)[i].mutex_last_meal, NULL);
        i++;
    }
}


void free_philo(t_philo **philo)
{
    int i;
    t_args *args;

    if (!philo || !*philo)
        return;

    args = (*philo)[0].args;
    // Her filozofun mutex'ini destroy et
    for (i = 0; i < args->number_of_philosophers; i++)
    {
        pthread_mutex_destroy(&(*philo)[i].mutex_last_meal);
    }

    // Çatal mutex dizisini destroy et
    if ((*philo)[0].fork_mutex)
    {
        for (i = 0; i < args->number_of_philosophers; i++)
            pthread_mutex_destroy(&(*philo)[0].fork_mutex[i]);
        free((*philo)[0].fork_mutex);
    }

    pthread_mutex_destroy(&args->mutex_dead_cntrl);

    // Filozof dizisini free et
    free(*philo);
    *philo = NULL;
}


/*void free_philo(t_philo **philo)
{
    int i;
    int philo_num;

    if (!philo || !*philo)
        return;

    philo_num = (*philo)[0].args->number_of_philosophers;

    i = 0;
    while(i < philo_num)
    {
        pthread_mutex_destroy(&(*philo)[0].fork_mutex[i]);
        i++;
    }

    free((*philo)[0].fork_mutex);
    //pthread_mutex_destroy(&(*philo)[0].args->mutex_dead_cntrl);

    free(*philo);
    *philo = NULL;
}*/



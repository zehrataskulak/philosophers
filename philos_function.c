/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 22:06:01 by zzehra            #+#    #+#             */
/*   Updated: 2026/03/16 12:42:48 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philos_function(void *arg)
{
    struct timeval	tv;
    t_philo *philo;
    long long start_time;  
    long long ms_time1;
    long long ms_time2;
    long long ms_time3;
    
    
    philo = (t_philo *)arg;
    if(philo->args->dead_cntrl)
        return ((void *)(-1));
    start_time = philo->start_time;
    
//    while(1)
//    {

        gettimeofday(&tv, NULL);
        ms_time1 = tv.tv_sec * 1000LL + tv.tv_usec / 1000 - start_time;

        if(philo->args->number_of_philosophers != 1)
        {
            if (philo->philo_id % 2 == 0)
            {
                pthread_mutex_lock(&philo->fork_mutex[philo->left_fork_id]);
                printf("time: %lld, %d took left fork\n", ms_time1, philo->philo_id);
                pthread_mutex_lock(&philo->fork_mutex[philo->right_fork_id]);
                printf("time: %lld, %d took right fork\n", ms_time1, philo->philo_id);
            }
            else
            {
                pthread_mutex_lock(&philo->fork_mutex[philo->right_fork_id]);
                printf("time: %lld, %d took right fork\n", ms_time1, philo->philo_id);
                pthread_mutex_lock(&philo->fork_mutex[philo->left_fork_id]);
                printf("time: %lld, %d took left fork\n", ms_time1, philo->philo_id);
            }

        }
        else
        {
            printf("time: %lld, %d philo died!\n", ms_time1 + philo->args->time_to_die, philo->philo_id);
            //pthread_exit((void *)(-1));
            philo->args->dead_cntrl = 1;
            return ((void *)(-1));
            
        }
        
        gettimeofday(&tv, NULL);
        ms_time2 = tv.tv_sec * 1000LL + tv.tv_usec / 1000 - start_time;
        
        if((ms_time2 - ms_time1) >= philo->args->time_to_die)
        {
            printf("time: %lld, %d philo died!\n", ms_time2, philo->philo_id);
            //pthread_exit((void *)(-1));
            philo->args->dead_cntrl = 1;
            return ((void *)(-1));
            
        }
        
        printf("time: %lld, %d philo eating\n", ms_time1, philo->philo_id);
        usleep(philo->args->time_to_eat * 1000);
        pthread_mutex_unlock(&philo->fork_mutex[philo->right_fork_id]);
        pthread_mutex_unlock(&philo->fork_mutex[philo->left_fork_id]);
        philo->last_meal = ms_time2;
        philo->eat_times++;
        
        gettimeofday(&tv, NULL);
        ms_time3 = tv.tv_sec * 1000LL + tv.tv_usec / 1000 - start_time;
        
        if(philo->args->time_to_sleep >= philo->args->time_to_die)
        {
            printf("time: %lld, %d philo died!\n", ms_time3 + philo->args->time_to_die, philo->philo_id);
            //pthread_exit((void *)(-1));
            philo->args->dead_cntrl = 1;
            return ((void *)(-1));
            
        }

        printf("time: %lld, %d philo sleeping\n", ms_time3, philo->philo_id);
        usleep(philo->args->time_to_sleep * 1000);
        //pthread_exit((void *)0);
        return ((void *)(0));
//    }
}
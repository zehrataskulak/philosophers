/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 22:06:01 by zzehra            #+#    #+#             */
/*   Updated: 2026/04/11 13:40:03 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int f_dead_cntrl(t_philo *philo)
{
    pthread_mutex_lock(&philo->mutex_dead_cntrl);
    if (philo->args->dead_cntrl == 1)
    {
        pthread_mutex_unlock(&philo->mutex_dead_cntrl);
        return (1);
        //return ((void *)(-1));
    }
    pthread_mutex_unlock(&philo->mutex_dead_cntrl);
    return (0);
}

void *philos_function(void *arg)
{
    struct timeval	tv;
    t_philo *philo;
    long long start_time;  
    long long ms_time1;
    long long ms_time2;
    
    philo = (t_philo *)arg;    
    start_time = philo->start_time;
    
    
    
    
    while(1)
    {      
        if(f_dead_cntrl(philo))
            break;
        if (philo->eat_times >= philo->args->number_of_times_each_philosopher_must_eat) {
            break;
        }

        gettimeofday(&tv, NULL);
        ms_time1 = tv.tv_sec * 1000LL + tv.tv_usec / 1000 - start_time;
        
        
        if(philo->args->number_of_philosophers == 1)
        {
            printf("time: %lld, %d took the fork\n", ms_time1, philo->philo_id);
            printf("time: %lld, %d philo died2!\n", ms_time1 + philo->args->time_to_die, philo->philo_id);
            break;
            //return ((void *)(-1));
        }

        
        //////////////////

        if(philo->philo_id % 2 == 0)
            usleep(1);
        
        pthread_mutex_lock(&philo->fork_mutex[philo->right_fork_id]);
        pthread_mutex_lock(&philo->fork_mutex[philo->left_fork_id]);
             
        gettimeofday(&tv, NULL);
        ms_time2 = tv.tv_sec * 1000LL + tv.tv_usec / 1000 - start_time;

        if(f_dead_cntrl(philo))
            break;

        
        
        if((ms_time2 - ms_time1) >= philo->args->time_to_die)
        {
            printf("time: %lld, %d philo died1!\n", ms_time1 + philo->args->time_to_die, philo->philo_id);
            pthread_mutex_lock(&philo->mutex_dead_cntrl);//
            philo->args->dead_cntrl = 1;
            pthread_mutex_unlock(&philo->mutex_dead_cntrl);//
            pthread_mutex_unlock(&philo->fork_mutex[philo->right_fork_id]);
            pthread_mutex_unlock(&philo->fork_mutex[philo->left_fork_id]);
            break;
            //return ((void *)(-1));            
        }
        
        printf("time: %lld, %d took left fork\n", ms_time2, philo->philo_id);
        printf("time: %lld, %d took right fork\n", ms_time2, philo->philo_id);
            
        if(f_dead_cntrl(philo))
            break;
            
        printf("time: %lld, %d philo eating\n", ms_time2, philo->philo_id);
        usleep(philo->args->time_to_eat * 1000);

        pthread_mutex_unlock(&philo->fork_mutex[philo->right_fork_id]);
        pthread_mutex_unlock(&philo->fork_mutex[philo->left_fork_id]);
        ms_time2 += philo->args->time_to_eat;
        philo->last_meal = ms_time2;
        philo->eat_times++;

        if(f_dead_cntrl(philo))
            break;

        printf("time: %lld, %d philo sleeping\n", ms_time2, philo->philo_id);
        
        if(philo->args->time_to_sleep >= philo->args->time_to_die)
        {
            printf("time: %lld, %d philo died3!\n", ms_time2 + philo->args->time_to_die, philo->philo_id);
            pthread_mutex_lock(&philo->mutex_dead_cntrl);//
            philo->args->dead_cntrl = 1;
            pthread_mutex_unlock(&philo->mutex_dead_cntrl);//
            break;
            //return ((void *)(-1));
            
        }

        usleep(philo->args->time_to_sleep * 1000);
    }
    return ((void *)(0));
}
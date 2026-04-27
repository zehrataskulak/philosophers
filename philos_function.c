/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:30:30 by zzehra            #+#    #+#             */
/*   Updated: 2026/04/27 20:31:58 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long find_time(long long start_time)
{
    struct timeval	tv;
    long long time;

    gettimeofday(&tv, NULL);
    if(start_time != -1)
        time = tv.tv_sec * 1000LL + tv.tv_usec / 1000 - start_time;
    else
        time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
    return (time);
}

int f_dead_cntrl(t_philo *philo)
{
    pthread_mutex_lock(&philo->args->mutex_dead_cntrl);
    if (philo->args->dead_cntrl == 1)
    {
        pthread_mutex_unlock(&philo->args->mutex_dead_cntrl);
        return (1);
    }
    pthread_mutex_unlock(&philo->args->mutex_dead_cntrl);
    return (0);
}

void	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork_mutex[philo->left_fork_id]);
		pthread_mutex_lock(&philo->fork_mutex[philo->right_fork_id]);
	}
	else
	{
		pthread_mutex_lock(&philo->fork_mutex[philo->right_fork_id]);
		pthread_mutex_lock(&philo->fork_mutex[philo->left_fork_id]);
	}
}

void    release_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->fork_mutex[philo->right_fork_id]);
    pthread_mutex_unlock(&philo->fork_mutex[philo->left_fork_id]);
}

int	philo_eat(t_philo *philo)
{
	long long	curr_time;

	take_forks(philo);
	if (f_dead_cntrl(philo))
	{
		release_forks(philo);
		return (1);
	}
	curr_time = find_time(philo->args->start_time);
	printf("time: %lld, %d took fork\n", curr_time, philo->philo_id);
	printf("time: %lld, %d took fork\n", curr_time, philo->philo_id);
	printf("time: %lld, %d philo eating\n", curr_time, philo->philo_id);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal_time = find_time(philo->args->start_time);
	pthread_mutex_unlock(&philo->mutex_last_meal);
	usleep(philo->args->time_to_eat * 1000);
	philo->eat_times++;
    release_forks(philo);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	long long	curr_time;

	if (f_dead_cntrl(philo))
		return (1);
	curr_time = find_time(philo->args->start_time);
	printf("time: %lld, %d philo sleeping\n", curr_time, philo->philo_id);
	usleep(philo->args->time_to_sleep * 1000);
	return (0);
}


void	*philos_function(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->args->number_of_philosophers == 1)
	{
		printf("time: %d, %d took the fork\n", 0, philo->philo_id);
		return (NULL);
	}
	while (1)
	{
		if (philo->args->number_of_times_must_eat != -1
			&& philo->args->number_of_times_must_eat == philo->eat_times)
			break ;
		if (philo_eat(philo))
			break ;
		if (philo_sleep(philo))
			break ;
	}
	return (NULL);
}

/*void *philos_function(void *arg)
{
    t_philo *philo;
    long long start_time;
    long long curr_time;

    philo = (t_philo *)arg;
    start_time = find_time(-1);
    if(philo->args->number_of_philosophers == 1)
    {
        printf("time: %d, %d took the fork\n", 0, philo->philo_id);
        return ((void *)(0));
    }
    while(1)
    {
        if(philo->args->number_of_times_must_eat != -1 
            && philo->args->number_of_times_must_eat == philo->eat_times)
            return ((void *)(0));

        if (philo->philo_id % 2 != 0)
        {
            pthread_mutex_lock(&philo->fork_mutex[philo->left_fork_id]);
            pthread_mutex_lock(&philo->fork_mutex[philo->right_fork_id]);
        }
        else
        {
            pthread_mutex_lock(&philo->fork_mutex[philo->right_fork_id]);
            pthread_mutex_lock(&philo->fork_mutex[philo->left_fork_id]);
        }

        if(f_dead_cntrl(philo))
            return (unlock_mutexes(philo));

        curr_time = find_time(start_time);
        printf("time: %lld, %d took fork\n", curr_time, philo->philo_id);
        printf("time: %lld, %d took fork\n", curr_time, philo->philo_id);

        if(f_dead_cntrl(philo))
            return (unlock_mutexes(philo));

        printf("time: %lld, %d philo eating\n", curr_time, philo->philo_id);
        usleep(philo->args->time_to_eat * 1000);
        philo->eat_times++;
        pthread_mutex_lock(&philo->mutex_last_meal);
        philo->last_meal_time = find_time(start_time);
        pthread_mutex_unlock(&philo->mutex_last_meal);
        pthread_mutex_unlock(&philo->fork_mutex[philo->right_fork_id]);
        pthread_mutex_unlock(&philo->fork_mutex[philo->left_fork_id]);

        if(philo->args->dead_cntrl)
            return ((void *)(0));
        
        printf("time: %lld, %d philo sleeping\n", curr_time + philo->args->time_to_sleep, philo->philo_id);
        usleep(philo->args->time_to_sleep * 1000);
    }
    return ((void *)(0));
}*/
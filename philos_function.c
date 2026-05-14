/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:30:30 by zzehra            #+#    #+#             */
/*   Updated: 2026/05/14 19:14:15 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	find_time(long long start_time)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	if (start_time != -1)
		time = tv.tv_sec * 1000LL + tv.tv_usec / 1000 - start_time;
	else
		time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (time);
}

int	f_dead_cntrl(t_philo *philo)
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

void	*philos_function(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->args->number_of_philosophers == 1)
	{
		printf("time: %d, %d took the fork\n", 0, philo->philo_id);
		printf("time: %d, 1 philo died!\n", philo->args->time_to_die);
		return (NULL);
	}
	while (1)
	{
		if (f_dead_cntrl(philo))
			break ;
		if (philo->args->number_of_times_must_eat != -1
			&& philo->args->number_of_times_must_eat == philo->eat_times)
			break ;
		if (philo_eat(philo))
			break ;
		if (philo_sleep(philo))
			break ;
		if (philo_think(philo))
			break ;
	}
	return (NULL);
}

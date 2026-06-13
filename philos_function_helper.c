/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_function_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaskula <ztaskula@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:20:24 by ztaskula          #+#    #+#             */
/*   Updated: 2026/06/13 20:40:20 by ztaskula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork_mutex[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->fork_mutex[philo->left_fork_id]);
}

int	philo_eat(t_philo *philo)
{
	if (f_dead_cntrl(philo))
		return (1);
	take_forks(philo);
	if (f_dead_cntrl(philo)
		|| print_action("fork", philo)
		|| print_action("fork", philo)
		|| print_action("eat", philo))
	{
		release_forks(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal_time = find_time(philo->args->start_time);
	pthread_mutex_unlock(&philo->mutex_last_meal);
	usleep(philo->args->time_to_eat * 1000);
	pthread_mutex_lock(&philo->mutex_eat_times);
	philo->eat_times++;
	pthread_mutex_unlock(&philo->mutex_eat_times);
	release_forks(philo);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (print_action("sleep", philo))
		return (1);
	usleep(philo->args->time_to_sleep * 1000);
	return (0);
}

int	philo_think(t_philo *philo)
{
	long long	time_diff;

	if (f_dead_cntrl(philo))
		return (1);
	if (print_action("think", philo))
		return (1);
	time_diff = philo->args->time_to_die
		- philo->args->time_to_eat
		- philo->args->time_to_sleep;
	if (time_diff > 0)
	{
		if (philo->args->number_of_philosophers % 2 == 0)
			usleep(time_diff / 4 * 1000);
		else
			usleep(time_diff / 2 * 1000);
	}
	return (0);
}

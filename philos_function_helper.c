/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_function_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaskula <ztaskula@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:08:51 by zzehra            #+#    #+#             */
/*   Updated: 2026/05/16 13:13:30 by ztaskula         ###   ########.fr       */
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
	long long	curr_time;

	take_forks(philo);
	curr_time = find_time(philo->args->start_time);
	if (f_dead_cntrl(philo))
	{
		release_forks(philo);
		return (1);
	}
	if (print_action("fork", curr_time, philo))
		return (1);
	if (print_action("fork", curr_time, philo))
		return (1);
	if (print_action("eat", curr_time, philo))
		return (1);
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

	curr_time = find_time(philo->args->start_time);
	if (print_action("sleep", curr_time, philo))
		return (1);
	usleep(philo->args->time_to_sleep * 1000);
	return (0);
}

int	philo_think(t_philo *philo)
{
	long long	curr_time;

	curr_time = find_time(philo->args->start_time);
	if (print_action("think", curr_time, philo))
		return (1);
	usleep(500);
	return (0);
}

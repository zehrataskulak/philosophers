/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaskula <ztaskula@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:20:38 by ztaskula          #+#    #+#             */
/*   Updated: 2026/06/13 20:45:44 by ztaskula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_action_helper(char *action, t_philo *philo)
{
	long long	curr_time;

	if (!ft_strcmp(action, "fork"))
	{
		if (f_dead_cntrl(philo))
			return (1);
		pthread_mutex_lock(&philo->args->mutex_printf);
		curr_time = find_time(philo->args->start_time);
		printf("%lld %d has taken a fork\n", curr_time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->mutex_printf);
	}
	else if (!ft_strcmp(action, "eat"))
	{
		if (f_dead_cntrl(philo))
			return (1);
		pthread_mutex_lock(&philo->args->mutex_printf);
		curr_time = find_time(philo->args->start_time);
		printf("%lld %d philo eating\n", curr_time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->mutex_printf);
	}
	return (0);
}

int	print_action(char *action, t_philo *philo)
{
	long long	curr_time;

	if (print_action_helper(action, philo))
		return (1);
	if (!ft_strcmp(action, "sleep"))
	{
		if (f_dead_cntrl(philo))
			return (1);
		pthread_mutex_lock(&philo->args->mutex_printf);
		curr_time = find_time(philo->args->start_time);
		printf("%lld %d philo sleeping\n", curr_time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->mutex_printf);
	}
	else if (!ft_strcmp(action, "think"))
	{
		if (f_dead_cntrl(philo))
			return (1);
		pthread_mutex_lock(&philo->args->mutex_printf);
		curr_time = find_time(philo->args->start_time);
		printf("%lld %d philo thinking\n", curr_time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->mutex_printf);
	}
	return (0);
}

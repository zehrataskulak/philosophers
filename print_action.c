/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaskula <ztaskula@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:06:38 by zzehra            #+#    #+#             */
/*   Updated: 2026/05/16 13:19:26 by ztaskula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

int	print_action_helper(char *action, long long curr_time, t_philo *philo)
{
	if (!ft_strcmp(action, "fork"))
	{
		if (f_dead_cntrl(philo))
			return (1);
		pthread_mutex_lock(&philo->args->mutex_printf);
		printf("time: %lld, %d took fork\n", curr_time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->mutex_printf);
	}
	else if (!ft_strcmp(action, "eat"))
	{
		if (f_dead_cntrl(philo))
			return (1);
		pthread_mutex_lock(&philo->args->mutex_printf);
		printf("time: %lld, %d philo eating\n", curr_time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->mutex_printf);
	}
	return (0);
}

int	print_action(char *action, long long curr_time, t_philo *philo)
{
	if (print_action_helper(action, curr_time, philo))
		return (1);
	else if (!ft_strcmp(action, "sleep"))
	{
		if (f_dead_cntrl(philo))
			return (1);
		pthread_mutex_lock(&philo->args->mutex_printf);
		printf("time: %lld, %d philo sleeping\n", curr_time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->mutex_printf);
	}
	else
	{
		if (f_dead_cntrl(philo))
			return (1);
		pthread_mutex_lock(&philo->args->mutex_printf);
		printf("time: %lld, %d philo thinking\n", curr_time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->mutex_printf);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:06:38 by zzehra            #+#    #+#             */
/*   Updated: 2026/05/23 11:21:31 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_action_helper(char *action, long long curr_time, t_philo *philo)
{
	if (!ft_strcmp(action, "fork"))
	{
		if (f_dead_cntrl(philo))
			return (1);
		pthread_mutex_lock(&philo->args->mutex_printf);
		printf("%lld %d has taken a fork\n", curr_time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->mutex_printf);
	}
	else if (!ft_strcmp(action, "eat"))
	{
		if (f_dead_cntrl(philo))
			return (1);
		pthread_mutex_lock(&philo->args->mutex_printf);
		printf("%lld %d philo eating\n", curr_time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->mutex_printf);
	}
	return (0);
}

int	print_action(char *action, long long curr_time, t_philo *philo)
{
	if (print_action_helper(action, curr_time, philo))
		return (1);
	if (!ft_strcmp(action, "sleep"))
	{
		if (f_dead_cntrl(philo))
			return (1);
		pthread_mutex_lock(&philo->args->mutex_printf);
		printf("%lld %d philo sleeping\n", curr_time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->mutex_printf);
	}
	else if (!ft_strcmp(action, "think"))
	{
		if (f_dead_cntrl(philo))
			return (1);
		pthread_mutex_lock(&philo->args->mutex_printf);
		printf("%lld %d philo thinking\n", curr_time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->mutex_printf);
	}
	return (0);
}

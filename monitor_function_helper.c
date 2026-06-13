/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaskula <ztaskula@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:26:18 by ztaskula          #+#    #+#             */
/*   Updated: 2026/06/13 20:37:51 by ztaskula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal_times(t_philo *philo)
{
	int	i;
	int	philo_num;
	int	must_eat_times;
	int	eat_count;

	philo_num = philo[0].args->number_of_philosophers;
	must_eat_times = philo[0].args->number_of_times_must_eat;
	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_lock(&philo[i].mutex_eat_times);
		eat_count = philo[i].eat_times;
		pthread_mutex_unlock(&philo[i].mutex_eat_times);
		if (eat_count != must_eat_times)
			return (0);
		i++;
	}
	return (1);
}

int	check_meal_limit(t_philo *philo)
{
	pthread_mutex_lock(&philo[0].args->mutex_dead_cntrl);
	philo[0].args->dead_cntrl = 1;
	pthread_mutex_unlock(&philo[0].args->mutex_dead_cntrl);
	return (1);
}

int	check_eat_status(t_philo *philo, int i, int must_eat)
{
	int	eat_count;

	pthread_mutex_lock(&philo[i].mutex_eat_times);
	eat_count = philo[i].eat_times;
	pthread_mutex_unlock(&philo[i].mutex_eat_times);
	if (!(must_eat != -1 && eat_count >= must_eat))
		return (1);
	return (0);
}

void	set_dead_flag(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo[i].args->mutex_dead_cntrl);
	philo[i].args->dead_cntrl = 1;
	pthread_mutex_unlock(&philo[i].args->mutex_dead_cntrl);
}

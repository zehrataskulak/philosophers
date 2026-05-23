/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 09:13:08 by zzehra            #+#    #+#             */
/*   Updated: 2026/05/23 11:53:31 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal_times(t_philo *philo)
{
	int	i;
	int	philo_num;
	int	must_eat_times;

	philo_num = philo[0].args->number_of_philosophers;
	must_eat_times = philo[0].args->number_of_times_must_eat;
	i = 0;
	while (i < philo_num)
	{
		if (philo[i].eat_times != must_eat_times)
			return (0);
		i++;
	}
	return (1);
}

int	check_philos(t_philo *philo, int i, long long curr_time)
{
	pthread_mutex_lock(&philo[i].mutex_last_meal);
	if (philo[0].args->number_of_times_must_eat != -1
		&& philo[i].eat_times >= philo[0].args->number_of_times_must_eat)
		pthread_mutex_unlock(&philo[i].mutex_last_meal);
	else if (curr_time - philo[i].last_meal_time
		>= philo[i].args->time_to_die)
	{
		printf("%lld %d philo died!\n", curr_time, philo[i].philo_id);
		pthread_mutex_unlock(&philo[i].mutex_last_meal);
		return (1);
	}
	else
		pthread_mutex_unlock(&philo[i].mutex_last_meal);
	if (philo[0].args->number_of_times_must_eat != -1
		&& check_meal_times(philo))
	{
		pthread_mutex_lock(&philo[i].args->mutex_dead_cntrl);
		philo[i].args->dead_cntrl = 1;
		pthread_mutex_unlock(&philo[i].args->mutex_dead_cntrl);
		return (1);
	}
	return (0);
}

void	*monitor_function(void *arg)
{
	t_philo		*philo;
	int			i;
	long long	curr_time;

	philo = (t_philo *)arg;
	i = 0;
	if (philo[0].args->number_of_philosophers == 1)
		return (NULL);
	while (1)
	{
		if (i == philo[0].args->number_of_philosophers)
			i = 0;
		curr_time = find_time(philo[0].args->start_time);
		if (check_philos(philo, i, curr_time))
			break ;
		i++;
		usleep(300);
	}
	pthread_mutex_lock(&philo[i].args->mutex_dead_cntrl);
	philo[i].args->dead_cntrl = 1;
	pthread_mutex_unlock(&philo[i].args->mutex_dead_cntrl);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_args		args;
	t_philo		*philo;
	pthread_t	monitor_thread;
	int			i;

	read_args(argc, argv, &args);
	init_philos(&philo, &args);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL,
				(void *)philos_function, &philo[i]) != 0)
			return (write(2, "Error: thread create failed\n", 29), 1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL,
			(void *)monitor_function, philo) != 0)
		return (write(2, "Error: thread create failed\n", 29), 1);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < args.number_of_philosophers)
		pthread_join(philo[i++].thread, NULL);
	free_args(philo[0].args);
	free_philo(&philo);
	return (0);
}

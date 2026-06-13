/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaskula <ztaskula@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:20:08 by ztaskula          #+#    #+#             */
/*   Updated: 2026/06/13 20:31:45 by ztaskula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_philo *philo, int i, long long curr_time)
{
	pthread_mutex_lock(&philo[i].mutex_last_meal);
	if (curr_time - philo[i].last_meal_time >= philo[i].args->time_to_die)
	{
		pthread_mutex_lock(&philo[i].args->mutex_dead_cntrl);
		philo[i].args->dead_cntrl = 1;
		pthread_mutex_unlock(&philo[i].args->mutex_dead_cntrl);
		pthread_mutex_lock(&philo[i].args->mutex_printf);
		printf("%lld %d philo died\n", curr_time, philo[i].philo_id);
		pthread_mutex_unlock(&philo[i].args->mutex_printf);
		pthread_mutex_unlock(&philo[i].mutex_last_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo[i].mutex_last_meal);
	return (0);
}

int	check_philos(t_philo *philo, int i, long long curr_time)
{
	int	must_eat;

	must_eat = philo[0].args->number_of_times_must_eat;
	if (check_eat_status(philo, i, must_eat))
	{
		if (check_philo_death(philo, i, curr_time))
			return (1);
	}
	if (must_eat != -1 && check_meal_times(philo))
		return (check_meal_limit(philo));
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
	set_dead_flag(philo, i);
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

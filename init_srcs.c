/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_srcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaskula <ztaskula@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:20:02 by ztaskula          #+#    #+#             */
/*   Updated: 2026/06/13 20:20:04 by ztaskula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(pthread_mutex_t **fork_mutex, int fork_num)
{
	int	i;

	i = 0;
	*fork_mutex = malloc(sizeof(pthread_mutex_t) * fork_num);
	if (!(*fork_mutex))
		return ;
	while (i < fork_num)
	{
		if (pthread_mutex_init(&(*fork_mutex)[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(*fork_mutex)[i]);
			free(*fork_mutex);
			write(1, "Error: mutex init failed\n", 26);
			exit(1);
		}
		i++;
	}
}

void	init_philos(t_philo **philo, t_args *args)
{
	pthread_mutex_t	*fork_mutex;
	int				i;
	struct timeval	tv;

	*philo = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!(*philo))
		return ;
	init_mutexes(&fork_mutex, args->number_of_philosophers);
	gettimeofday(&tv, NULL);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].left_fork_id = (i + 1) % args->number_of_philosophers;
		(*philo)[i].right_fork_id = i;
		(*philo)[i].eat_times = 0;
		(*philo)[i].args = args;
		(*philo)[i].last_meal_time = 0;
		(*philo)[i].thread = 0;
		(*philo)[i].fork_mutex = fork_mutex;
		pthread_mutex_init(&(*philo)[i].mutex_last_meal, NULL);
		pthread_mutex_init(&(*philo)[i].mutex_eat_times, NULL);
		i++;
	}
}

void	free_philo(t_philo **philo)
{
	int		i;
	t_args	*args;

	if (!philo || !*philo)
		return ;
	args = (*philo)[0].args;
	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_mutex_destroy(&(*philo)[i].mutex_last_meal);
		pthread_mutex_destroy(&(*philo)[i].mutex_eat_times);
		i++;
	}
	if ((*philo)[0].fork_mutex)
	{
		i = 0;
		while (i < args->number_of_philosophers)
		{
			pthread_mutex_destroy(&(*philo)[0].fork_mutex[i]);
			i++;
		}
		free((*philo)[0].fork_mutex);
	}
	free(*philo);
	*philo = NULL;
}

void	free_args(t_args *args)
{
	pthread_mutex_destroy(&args->mutex_dead_cntrl);
	pthread_mutex_destroy(&args->mutex_printf);
}

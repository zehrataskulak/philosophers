/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaskula <ztaskula@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:20:44 by ztaskula          #+#    #+#             */
/*   Updated: 2026/06/13 20:33:57 by ztaskula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_args(int argc, char **argv, t_args *args)
{
	args->number_of_philosophers = z_atoi(argv[1]);
	args->time_to_die = z_atoi(argv[2]);
	args->time_to_eat = z_atoi(argv[3]);
	args->time_to_sleep = z_atoi(argv[4]);
	args->dead_cntrl = 0;
	if (argc == 6)
		args->number_of_times_must_eat = z_atoi(argv[5]);
	else
		args->number_of_times_must_eat = -1;
	args->start_time = find_time(-1);
	pthread_mutex_init(&args->mutex_dead_cntrl, NULL);
	pthread_mutex_init(&args->mutex_printf, NULL);
}

void	arg_error_exit(void)
{
	write(1, "Argument error!\n", 17);
	exit(1);
}

void	argument_error(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strchr(argv[i], '.'))
			arg_error_exit();
		if (i == 1 && z_atoi(argv[i]) > 200)
			arg_error_exit();
		if (i < 5 && z_atoi(argv[i]) <= 0)
			arg_error_exit();
		i++;
	}
	if (argc == 6)
	{
		if (z_atoi(argv[5]) < 0)
			arg_error_exit();
		if (z_atoi(argv[5]) == 0)
		{
			if (argv[5][0] != '0' || argv[5][1])
				arg_error_exit();
			exit(0);
		}
	}
}

void	read_args(int argc, char **argv, t_args *args)
{
	if (argc > 6 || argc < 5)
	{
		write(1, "Invalid number of arguments!\n", 30);
		exit(1);
	}
	argument_error(argc, argv);
	assign_args(argc, argv, args);
}

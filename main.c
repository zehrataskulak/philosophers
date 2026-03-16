/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 09:13:08 by zzehra            #+#    #+#             */
/*   Updated: 2026/03/16 08:34:22 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_args args;
    t_philo *philo;
    int i;
    int res;
  
    read_args(argc, argv, &args);
    init_philos(&philo, &args);
    i = 0;
    while(i < args.number_of_philosophers)
    {
        if (pthread_create(&philo[i].thread, NULL, (void *)philos_function, &philo[i]) != 0)
        {
            write(2, "Error: thread create failed\n", 29);
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < args.number_of_philosophers)
    {
        pthread_join(philo[i].thread, &res);
        if(res == -1)
        {
            free_philo(&philo);
            return (0);
        }
        i++;
    }
    free_philo(&philo);
    return (0);
}
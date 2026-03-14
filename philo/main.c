/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 09:13:08 by zzehra            #+#    #+#             */
/*   Updated: 2026/03/12 18:00:28 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_args args;
    //t_philo *philo;
  
    if(read_args(argc, argv, &args) == -1)
        return (-1);
    
  
    printf("%d\n%d\n%d\n%d\n", args.number_of_philosophers, args.time_to_die, args.time_to_eat, args.time_to_sleep);
    if(argc == 6)
        printf("%d\n", args.number_of_times_each_philosopher_must_eat);
}
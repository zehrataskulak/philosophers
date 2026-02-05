/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 09:13:08 by zzehra            #+#    #+#             */
/*   Updated: 2025/12/24 09:42:55 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_args args;
    
    int chck = read_args(argc, argv, &args);
    if(chck == 0)
        printf("%d\n%d\n%d\n%d\n", args.number_of_philosophers, args.time_to_die, args.time_to_eat, args.time_to_sleep);
}
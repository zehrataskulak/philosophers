/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_usleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:52:18 by zzehra            #+#    #+#             */
/*   Updated: 2026/05/14 18:00:47 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	z_usleep(int microsecond)
{
	struct timeval	tv;
	long long		start_time;
	long long		end_time;

	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000000LL + tv.tv_usec;
	end_time = start_time;
	while (1)
	{
		gettimeofday(&tv, NULL);
		end_time = tv.tv_sec * 1000000LL + tv.tv_usec;
		if (end_time - start_time >= microsecond)
			break ;
	}
}

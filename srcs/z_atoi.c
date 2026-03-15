/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_atoi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzehra <zzehra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 09:21:56 by zzehra            #+#    #+#             */
/*   Updated: 2026/03/12 17:07:25 by zzehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


long	z_atoi(const char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (!str[i] || str[i] == 32 || str[i] == 9 || str[i] == 10)
		return (num * sign);
	else
		return (0);
}
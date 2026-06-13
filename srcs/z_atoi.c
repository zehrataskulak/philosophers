/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_atoi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaskula <ztaskula@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:19:54 by ztaskula          #+#    #+#             */
/*   Updated: 2026/06/13 20:19:56 by ztaskula         ###   ########.fr       */
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

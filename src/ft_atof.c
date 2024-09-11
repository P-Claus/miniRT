/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:11:34 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/11 22:19:06 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	atof_check_sign(const char *str, int *iter)
{
	int	sign;

	sign = 1;
	if (str[*iter] == '-' || str[*iter] == '+')
	{
		if (str[*iter] == '-')
		{
			sign = -1;
			(*iter)++;
		}
	}
	return (sign);
}

float	ft_atof(const char *str, int decimal_nb)
{
	float	result;
	int		sign;
	int		iter;
	float	fraction;
	int		count;

	result = 0.0;
	iter = 0;
	fraction = 0.1;
	count = 0;
	sign = atof_check_sign(str, &iter);
	while (str[iter] >= '0' && str[iter] <= '9')
		result = result * 10.0 + (str[iter++] - '0');
	if (str[iter] == '.')
	{
		iter++;
		while (str[iter] >= '0' && str[iter] <= '9' && count < decimal_nb)
		{
			result = result + (str[iter] - '0') * fraction;
			fraction /= 10.0;
			iter++;
			count++;
		}
	}
	return (result * sign);
}

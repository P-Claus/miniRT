/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 08:57:40 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/06 21:59:11 by pclaus           ###   ########.fr       */
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

double	ft_atof(const char *str, int decimal_nb)
{
	double	result;
	int		sign;
	int		iter;
	double	fraction;
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

int	count_items_in_split(char **split, int nb_needed)
{
	int	iter;

	iter = 0;
	while (split[iter])
		iter++;
	if (iter == nb_needed)
		return (0);
	else
		return (1);
}

int	check_digits_in_coordinates(char **split)
{
	int	iter;
	int	word_iter;

	iter = 0;
	word_iter = 0;
	while (split[iter])
	{
		while (split[iter][word_iter] && split[iter][word_iter] != '\0')
		{
			if (!ft_isdigit(split[iter][word_iter])
				&& !(split[iter][word_iter] == '.')
				&& !(split[iter][word_iter] == '-'))
			{
				return (1);
			}
			word_iter++;
		}
		iter++;
		word_iter = 0;
	}
	return (0);
}

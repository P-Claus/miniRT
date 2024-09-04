/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 08:57:40 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/04 20:37:38 by pclaus           ###   ########.fr       */
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

int	check_digits_in_coordinates(char **split, int decimal_nb)
{
	int	iter;
	int	word_iter;
	bool	passed_dot;
	int		dec_nb;

	iter = 0;
	dec_nb = 0;
	word_iter = 0;
	passed_dot = false;
	while (split[iter])
	{
		while (split[iter][word_iter] && split[iter][word_iter] != '\0')
		{
			if ((!ft_isdigit(split[iter][word_iter])
				&& !(split[iter][word_iter] == '.')
				&& !(split[iter][word_iter] == '-'))
				|| dec_nb > decimal_nb)
					return (1);
			if (passed_dot == true)
				dec_nb++;
			if (split[iter][word_iter] == '.')
				passed_dot = true;
			word_iter++;
		}
		iter++;
		passed_dot = false;
		dec_nb = 0;
		word_iter = 0;
	}
	return (0);
}

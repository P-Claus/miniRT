/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:24:12 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/06 22:01:16 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	check_digits_in_rgb(char **split)
{
	int	iter;
	int	word_iter;

	iter = 0;
	word_iter = 0;
	while (split[iter])
	{
		while (split[iter][word_iter] && split[iter][word_iter] != '\0')
		{
			if (!ft_isdigit(split[iter][word_iter]))
				return (1);
			word_iter++;
		}
		iter++;
		word_iter = 0;
	}
	return (0);
}

int	rgb_bit_shift(char **rgb_split, int rgb_values[], int *rgb_code)
{
	int	iter;

	iter = 0;
	while ((rgb_split)[iter])
	{
		rgb_values[iter] = ft_atoi(rgb_split[iter]);
		if (!(rgb_values[iter] >= 0 && rgb_values[iter] <= 255))
			return (1);
		iter++;
	}
	*rgb_code = (rgb_values[0] << 16) | (rgb_values[1] << 8) | rgb_values[2];
	return (0);
}

int	parse_rgb(int *rgb_int, char *string)
{
	char	**rgb_split;
	int		rgb_values[3];
	int		rgb_code;

	rgb_split = ft_split(string, ',');
	if (count_items_in_split(rgb_split, 3) == 1
		|| check_digits_in_rgb(rgb_split) == 1 || rgb_bit_shift(rgb_split,
			rgb_values, &rgb_code) == 1)
	{
		free_split(rgb_split);
		return (1);
	}
	*rgb_int = rgb_code;
	free_split(rgb_split);
	return (0);
}

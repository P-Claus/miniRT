/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:24:12 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/24 09:42:02 by pclaus           ###   ########.fr       */
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

static int	fill_rgb_struct(char **rgb_split, int rgb_values[], t_rgb *rgb)
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
	rgb->r = rgb_values[0] / 255.0;
	rgb->g = rgb_values[1] / 255.0;
	rgb->b = rgb_values[2] / 255.0;
	return (0);
}

int	parse_rgb(t_rgb *rgb, char *string)
{
	char	**rgb_split;
	int		rgb_values[3];
	
	rgb_split = ft_split(string, ',');
	if (count_items_in_split(rgb_split, 3) == 1
		|| check_digits_in_rgb(rgb_split) == 1 || fill_rgb_struct(rgb_split,
			rgb_values, rgb) == 1)
	{
		free_split(rgb_split);
		return (1);
	}
	free_split(rgb_split);
	return (0);
}

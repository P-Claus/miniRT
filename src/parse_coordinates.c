/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coordinates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:27:26 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/05 13:54:10 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	check_digits_in_coordinates(char **split)
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

int	parse_orientation_vector(t_scene_info *scene_info, char *string, int iter)
{
	char	**coordinates_split;
	double	coordinate_values[3];

	coordinates_split = ft_split(string, ',');
	if (count_items_in_split(coordinates_split, 3) == 1
		|| check_digits_in_coordinates(coordinates_split) == 1)
	{
		free_split(coordinates_split);
		return (1);
	}
	while (coordinates_split[++iter])
	{
		coordinate_values[iter] = ft_atof(coordinates_split[iter], 2);
		if (!(coordinate_values[iter] >= -1.00
				&& coordinate_values[iter] <= 1.00))
		{
			free_split(coordinates_split);
			return (1);
		}
	}
	scene_info->C_coordinates_o.x = coordinate_values[0];
	scene_info->C_coordinates_o.y = coordinate_values[1];
	scene_info->C_coordinates_o.z = coordinate_values[2];
	free_split(coordinates_split);
	return (0);
}

int	parse_coordinates_viewpoint(t_scene_info *scene_info, char *string)
{
	char	**coordinates_split;
	double	coordinate_values[3];
	int		iter;

	iter = -1;
	coordinates_split = ft_split(string, ',');
	if (count_items_in_split(coordinates_split, 3) == 1
		|| check_digits_in_coordinates(coordinates_split) == 1)
	{
		free_split(coordinates_split);
		return (1);
	}
	while (coordinates_split[++iter])
		coordinate_values[iter] = ft_atof(coordinates_split[iter], 2);
	scene_info->C_coordinates_vp.x = coordinate_values[0];
	scene_info->C_coordinates_vp.y = coordinate_values[1];
	scene_info->C_coordinates_vp.z = coordinate_values[2];
	free_split(coordinates_split);
	return (0);
}

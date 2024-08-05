/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:32:53 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/05 14:22:58 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	parse_field_of_view(t_scene_info *scene_info, char *string)
{
	int	converted_int;

	if (ft_strchr(string, '.'))
		return (1);
	converted_int = ft_atoi(string);
	if (converted_int >= 0 && converted_int <= 180)
	{
		scene_info->C_fov = converted_int;
		return (0);
	}
	return (1);
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

int	parse_camera(t_scene_info *scene_info, char *string)
{
	char	**split;

	split = ft_split(string, ' ');
	if (count_items_in_split(split, 4) == 1
		|| parse_coordinates(&scene_info->C_coordinates_vp, split[1]) == 1
		|| parse_orientation_vector(scene_info, split[2], -1) == 1
		|| parse_field_of_view(scene_info, split[3]) == 1)
	{
		free_split(split);
		return (1);
	}
	free_split(split);
	return (0);
}

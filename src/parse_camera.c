/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:32:53 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/27 00:16:36 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	handle_conversion(t_scene_info *scene_info, char *string)
{
	int	converted_int;

	converted_int = ft_atoi(string);
	if (converted_int >= 0 && converted_int <= 180)
	{
		scene_info->camera.fov = converted_int;
		return (0);
	}
	return (1);
}

static int	parse_field_of_view(t_scene_info *scene_info, char *string)
{
	int		iter;
	char	*trim;

	iter = 0;
	if (ft_strchr(string, '.'))
		return (1);
	trim = ft_strtrim(string, "\n");
	while (trim[iter] && trim[iter] != '\0')
	{
		if (!ft_isdigit(trim[iter]))
		{
			free(trim);
			return (1);
		}
		iter++;
	}
	if (handle_conversion(scene_info, string) == 0)
	{
		free(trim);
		return (0);
	}
	free(trim);
	return (1);
}

int	parse_camera(t_scene_info *scene_info, char *string)
{
	char	**split;

	split = ft_split(string, ' ');
	if (count_items_in_split(split, 4) == 1
		|| parse_coordinates(&scene_info->camera.coordinates, split[1]) == 1
		|| parse_orientation_vector(
			&scene_info->camera.vector, split[2], -1) == 1
		|| parse_field_of_view(scene_info, split[3]) == 1)
	{
		free_split(split);
		return (1);
	}
	free_split(split);
	scene_info->camera.yaw = 
		atan2(-scene_info->camera.vector.x, -scene_info->camera.vector.z);
	scene_info->camera.pitch = 
		atan2(vec3_norm((t_coordinates){-scene_info->camera.vector.z,
				-scene_info->camera.vector.x, 0}), scene_info->camera.vector.y)
		- M_PI_2;
	rotate_camera(&scene_info->camera, (t_pixel_coord){0, 0}, 0);
	return (0);
}

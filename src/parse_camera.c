/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:32:53 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/05 13:52:28 by pclaus           ###   ########.fr       */
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

int	parse_camera(t_scene_info *scene_info, char *string)
{
	char	**split;

	split = ft_split(string, ' ');
	if (count_items_in_split(split, 4) == 1
		|| parse_coordinates_viewpoint(scene_info, split[1]) == 1
		|| parse_orientation_vector(scene_info, split[2], -1) == 1
		|| parse_field_of_view(scene_info, split[3]) == 1)
	{
		free_split(split);
		return (1);
	}
	free_split(split);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:23:11 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/08 12:21:29 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	parse_diameter(t_scene_info *scene_info, char *string, int index)
{
	float	conversion;
	int		iter;

	iter = 0;
	while (string[iter] && string[iter] != '\0')
	{
		if (!ft_isdigit(string[iter]) && !(string[iter] == '.'))
			return (1);
		iter++;
	}
	conversion = ft_atof(string, 2);
	scene_info->cylinders[index].diameter = conversion;
	return (0);
}

static int	parse_height(t_scene_info *scene_info, char *string, int index)
{
	float	conversion;
	int		iter;

	iter = 0;
	while (string[iter] && string[iter] != '\0')
	{
		if (!ft_isdigit(string[iter]) && !(string[iter] == '.'))
			return (1);
		iter++;
	}
	conversion = ft_atof(string, 2);
	scene_info->cylinders[index].height = conversion;
	return (0);
}

int	parse_cylinder(t_scene_info *scene_info, char *string,
		t_identifier_count *id_count)
{
	char	**split;
	char	*trimmed_rgb;

	split = ft_split(string, ' ');
	id_count->cy_count--;
	if (count_items_in_split(split, 6) == 1
		|| parse_coordinates(&scene_info->cylinders[id_count->cy_count].coordinates,
			split[1]) == 1
		|| parse_orientation_vector(&scene_info->cylinders[id_count->cy_count].vector,
			split[2], -1) == 1 || parse_diameter(scene_info, split[3],
			id_count->cy_count) == 1 || parse_height(scene_info, split[4], id_count->cy_count) == 1)
	{
		free_split(split);
		return (1);
	}
	trimmed_rgb = ft_strtrim(split[5], "\n");
	if (parse_rgb(&scene_info->cylinders[id_count->cy_count].rgb_code,
					trimmed_rgb) == 1)
	{
		free_split_and_trimmed_rgb(split, trimmed_rgb);
		return (1);
	}
	free_split_and_trimmed_rgb(split, trimmed_rgb);
	return (0);
}

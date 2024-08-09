/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:18:01 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/09 10:31:44 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	parse_diameter(t_scene_info *scene_info, char *string,
		t_identifier_count *id_count)
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
	if (conversion > INT_MAX)
		return (1);
	scene_info->spheres[id_count->sp_count].diameter = conversion;
	return (0);
}

int	parse_sphere(t_scene_info *scene_info, char *string,
		t_identifier_count *id_count)
{
	char	**split;
	char	*trimmed_rgb;

	id_count->sp_count--;
	split = ft_split(string, ' ');
	if (count_items_in_split(split, 4) == 1
		|| parse_coordinates(
			&scene_info->spheres[id_count->sp_count].coordinates,
			split[1]) == 1 || parse_diameter(scene_info, split[2],
			id_count) == 1)
	{
		free_split(split);
		return (1);
	}
	trimmed_rgb = ft_strtrim(split[3], "\n");
	if (parse_rgb(&scene_info->spheres[id_count->sp_count].rgb_code,
			trimmed_rgb) == 1)
	{
		free_split_and_trimmed_rgb(split, trimmed_rgb);
		return (1);
	}
	free_split_and_trimmed_rgb(split, trimmed_rgb);
	return (0);
}

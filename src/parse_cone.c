/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:18:52 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/31 14:31:53 by pclaus           ###   ########.fr       */
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
	if (conversion > (float)INT_MAX)
		return (1);
	scene_info->cones[index].diameter = conversion;
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
	if (conversion > (float)INT_MAX)
		return (1);
	scene_info->cones[index].height = conversion;
	return (0);
}

static int	handle_rgb(t_scene_info *scene_info, char **split,
		t_identifier_count *id_count)
{
	char	*trimmed_rgb;

	trimmed_rgb = ft_strtrim(split[5], "\n");
	if (parse_rgb(&scene_info->cones[id_count->co_count].rgb,
			trimmed_rgb) == 1)
	{
		free_split_and_trimmed_rgb(split, trimmed_rgb);
		return (1);
	}
	free(trimmed_rgb);
	return (0);
}

int	parse_cone(t_scene_info *scene_info, char *string,
		t_identifier_count *id_count)
{
	char	**split;

	split = ft_split(string, ' ');
	id_count->co_count--;
	if (count_items_in_split(split, 6) == 1
		|| parse_coordinates(&scene_info->cones[id_count->co_count].apex,
			split[1]) == 1
		|| parse_orientation_vector(&scene_info->cones[id_count->co_count].vector,
			split[2], -1) == 1 || parse_diameter(scene_info, split[3],
			id_count->co_count) == 1 || parse_height(scene_info, split[4],
			id_count->co_count) == 1)
	{
		free_split((split));
		return (1);
	}
	if (handle_rgb(scene_info, split, id_count) == 1)
		return (1);
	free_split(split);
	return (0);
}

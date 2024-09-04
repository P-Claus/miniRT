/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:06:52 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/04 20:48:59 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	handle_conversion(t_scene_info *scene_info, char *string)
{
	double	conversion;

	conversion = ft_atof(string, 3);
	printf("The conversion is: %f\n", conversion);
	if (!(conversion >= 0.0 && conversion <= 1.0))
		return (1);
	scene_info->light.brightness = conversion;
	return (0);
}

int	parse_light(t_scene_info *scene_info, char *string)
{
	char	**split;
	char	*trimmed_rgb;

	split = ft_split(string, ' ');
	if (count_items_in_split(split, 4) == 1
		|| parse_coordinates(&scene_info->light.coordinates, split[1]) == 1
		|| ft_strlen(split[2]) > 5)
	{
		free_split(split);
		return (1);
	}
	if (handle_conversion(scene_info, split[2]) == 1)
	{
		free_split(split);
		return (1);
	}
	trimmed_rgb = ft_strtrim(split[3], "\n");
	if (parse_rgb(&scene_info->light.rgb, trimmed_rgb) == 1)
	{
		free_split_and_trimmed_rgb(split, trimmed_rgb);
		return (1);
	}
	free_split_and_trimmed_rgb(split, trimmed_rgb);
	return (0);
}

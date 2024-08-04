/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_lighting.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:18:26 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/04 18:18:04 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	ambient_lighting_error_check_lighting_ratio(double lighting_ratio)
{
	if (lighting_ratio >= 0.0 && lighting_ratio <= 1.0)
		return (0);
	else
		return (1);
}

int	parse_ambient_lighting(t_scene_info *scene_info, char *string)
{
	char	**split;
	char	*trimmed_rgb;
	double	conversion;

	split = ft_split(string, ' ');
	if (count_items_in_split(split, 3) == 1 || ft_strlen(split[1]) != 3)
	{
		free_split(split);
		return (1);
	}
	conversion = ft_atof(split[1], 1);
	scene_info->A_lighting = conversion;
	if (ambient_lighting_error_check_lighting_ratio(conversion) == 1)
	{
		free_split(split);
		return (1);
	}
	trimmed_rgb = ft_strtrim(split[2], "\n");
	if (parse_rgb(scene_info, trimmed_rgb) == 1)
	{
		free_split_and_trimmed_rgb(split, trimmed_rgb);
		return (1);
	}
	free_split_and_trimmed_rgb(split, trimmed_rgb);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:51:11 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/08 14:31:13 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	parse_plane(t_scene_info *scene_info, char *string,
		t_identifier_count *id_count)
{
	char	**split;
	char	*trimmed_rgb;

	split = ft_split(string, ' ');
	id_count->pl_count--;
	if (count_items_in_split(split, 4) == 1
		|| parse_coordinates(
			&scene_info->planes[id_count->pl_count].coordinates,
			split[1]) == 1
		|| parse_orientation_vector(
			&scene_info->planes[id_count->pl_count].vector,
			split[2], -1) == 1)
	{
		free_split(split);
		return (1);
	}
	trimmed_rgb = ft_strtrim(split[3], "\n");
	if (parse_rgb(&scene_info->planes[id_count->pl_count].rgb_code,
			trimmed_rgb) == 1)
	{
		free_split_and_trimmed_rgb(split, trimmed_rgb);
		return (1);
	}
	free_split_and_trimmed_rgb(split, trimmed_rgb);
	return (0);
}

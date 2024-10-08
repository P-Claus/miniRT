/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:18:44 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/08 17:59:13 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	free_split(char **split)
{
	int	iter;

	iter = 0;
	while (split[iter])
	{
		free(split[iter]);
		iter++;
	}
	free(split);
}

void	free_split_and_trimmed_rgb(char **split, char *trimmed_rgb)
{
	int	iter;

	iter = 0;
	while (split[iter])
	{
		free(split[iter]);
		iter++;
	}
	free(split);
	free(trimmed_rgb);
}

void	free_shape_arrays(t_scene_info *scene_info)
{
	free(scene_info->spheres);
	free(scene_info->planes);
	free(scene_info->cylinders);
}

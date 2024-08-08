/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:59:20 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/08 12:10:29 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"


static void	init_sphere(t_scene_info *scene_info, t_identifier_count *id_count)
{
	int	iter;

	iter = 0;
	while (iter < id_count->sp_count)
	{
		scene_info->spheres[iter].rgb_code = 0;
		scene_info->spheres[iter].diameter = 0;
		scene_info->spheres[iter].coordinates.x = 0;
		scene_info->spheres[iter].coordinates.y = 0;
		scene_info->spheres[iter].coordinates.z = 0;
		iter++;
	}
}

static void	init_plane(t_scene_info *scene_info, t_identifier_count *id_count)
{
	int	iter;

	iter = 0;
	while (iter < id_count->pl_count)
	{
		scene_info->planes[iter].rgb_code = 0;
		scene_info->planes[iter].coordinates.x = 0;
		scene_info->planes[iter].coordinates.y = 0;
		scene_info->planes[iter].coordinates.z = 0;
		scene_info->planes[iter].vector.x = 0;
		scene_info->planes[iter].vector.y = 0;
		scene_info->planes[iter].vector.z = 0;
		iter++;
	}
}

static void	init_cylinder(t_scene_info *scene_info, t_identifier_count *id_count)
{
	int	iter;

	iter = 0;
	while (iter < id_count->cy_count)
	{
		scene_info->cylinders[iter].rgb_code = 0;
		scene_info->cylinders[iter].height = 0;
		scene_info->cylinders[iter].diameter = 0;
		scene_info->cylinders[iter].coordinates.x = 0;
		scene_info->cylinders[iter].coordinates.x = 0;
		scene_info->cylinders[iter].coordinates.x = 0;
		scene_info->cylinders[iter].vector.x = 0;
		scene_info->cylinders[iter].vector.y = 0;
		scene_info->cylinders[iter].vector.z = 0;
		iter++;
	}
}

void	init_scene_info(t_scene_info *scene_info, t_identifier_count *id_count)
{
	scene_info->A_lighting = 0.0;
	scene_info->A_rgb_code = 0;
	scene_info->C_coordinates_vp.x = 0;
	scene_info->C_coordinates_vp.y = 0;
	scene_info->C_coordinates_vp.z = 0;
	scene_info->C_coordinates_o.x = 0;
	scene_info->C_coordinates_o.y = 0;
	scene_info->C_coordinates_o.z = 0;
	scene_info->L_cordinates_lp.x = 0;
	scene_info->L_cordinates_lp.y = 0;
	scene_info->L_cordinates_lp.z = 0;
	scene_info->L_brightness = 0;
	scene_info->L_rgb_code = 0;
	
	scene_info->spheres = malloc(id_count->sp_count * sizeof(t_sphere));
	scene_info->planes = malloc(id_count->pl_count * sizeof(t_plane));
	scene_info->cylinders = malloc(id_count->cy_count * sizeof(t_cylinder));

	if (!scene_info->spheres || !scene_info->planes || !scene_info->cylinders)
	{
		free(scene_info->spheres);
		free(scene_info->planes);
		free(scene_info->cylinders);
		return ;
	}
	init_sphere(scene_info, id_count);
	init_plane(scene_info, id_count);
	init_cylinder(scene_info, id_count);
}

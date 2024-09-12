/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:59:20 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/12 19:55:42 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	allocate_shape_arrays(t_scene_info *scene_info,
		t_identifier_count *id_count)
{
	scene_info->spheres = malloc(id_count->sp_count * sizeof(t_sphere));
	if (!scene_info->spheres)
		return (1);
	scene_info->planes = malloc(id_count->pl_count * sizeof(t_plane));
	if (!scene_info->planes)
	{
		free(scene_info->spheres);
		return (1);
	}
	scene_info->cylinders = malloc(id_count->cy_count * sizeof(t_cylinder));
	if (!scene_info->cylinders)
	{
		free(scene_info->spheres);
		free(scene_info->planes);
		return (1);
	}
	scene_info->cones = malloc(id_count->co_count * sizeof(t_cone));
	if (!scene_info->cones)
	{
		free(scene_info->spheres);
		free(scene_info->planes);
		free(scene_info->cylinders);
		return (1);
	}
	return (0);
}

void	init_ambient_lightning(t_scene_info *scene_info)
{
	scene_info->a_lighting.ambient_lighting = 0.0;
	scene_info->a_lighting.rgb.r = 0;
	scene_info->a_lighting.rgb.g = 0;
	scene_info->a_lighting.rgb.b = 0;
}

void	init_camera(t_scene_info *scene_info)
{
	scene_info->camera.coordinates.x = 0;
	scene_info->camera.coordinates.y = 0;
	scene_info->camera.coordinates.z = 0;
	scene_info->camera.vector.x = 0;
	scene_info->camera.vector.y = 0;
	scene_info->camera.vector.z = 0;
	scene_info->camera.fov = 0;
}

void	init_light(t_scene_info *scene_info)
{
	scene_info->light.coordinates.x = 0;
	scene_info->light.coordinates.y = 0;
	scene_info->light.coordinates.z = 0;
	scene_info->light.brightness = 0;
	scene_info->light.rgb.r = 0;
	scene_info->light.rgb.g = 0;
	scene_info->light.rgb.b = 0;
}

void	init_scene_info(t_scene_info *scene_info, t_identifier_count *id_count)
{
	init_ambient_lightning(scene_info);
	init_camera(scene_info);
	init_light(scene_info);
	scene_info->nb_of_spheres = id_count->sp_count;
	scene_info->nb_of_planes = id_count->pl_count;
	scene_info->nb_of_cylinders = id_count->cy_count;
	scene_info->nb_of_cones = id_count->co_count;
	if (allocate_shape_arrays(scene_info, id_count) == 1)
		return ;
	init_sphere(scene_info, id_count);
	init_plane(scene_info, id_count);
	init_cylinder(scene_info, id_count);
	init_cone(scene_info, id_count);
}

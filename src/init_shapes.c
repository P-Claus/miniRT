/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:13:07 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/12 19:13:55 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_sphere(t_scene_info *scene_info, t_identifier_count *id_count)
{
	int	iter;

	iter = 0;
	while (iter < id_count->sp_count)
	{
		scene_info->spheres[iter].rgb.r = 0;
		scene_info->spheres[iter].rgb.g = 0;
		scene_info->spheres[iter].rgb.b = 0;
		scene_info->spheres[iter].diameter = 0;
		scene_info->spheres[iter].coordinates.x = 0;
		scene_info->spheres[iter].coordinates.y = 0;
		scene_info->spheres[iter].coordinates.z = 0;
		iter++;
	}
}

void	init_plane(t_scene_info *scene_info, t_identifier_count *id_count)
{
	int	iter;

	iter = 0;
	while (iter < id_count->pl_count)
	{
		scene_info->planes[iter].rgb.r = 0;
		scene_info->planes[iter].rgb.g = 0;
		scene_info->planes[iter].rgb.b = 0;
		scene_info->planes[iter].coordinates.x = 0;
		scene_info->planes[iter].coordinates.y = 0;
		scene_info->planes[iter].coordinates.z = 0;
		scene_info->planes[iter].vector.x = 0;
		scene_info->planes[iter].vector.y = 0;
		scene_info->planes[iter].vector.z = 0;
		iter++;
	}
}

void	init_cylinder(t_scene_info *scene_info,	t_identifier_count *id_count)
{
	int	iter;

	iter = 0;
	while (iter < id_count->cy_count)
	{
		scene_info->cylinders[iter].rgb.r = 0;
		scene_info->cylinders[iter].rgb.g = 0;
		scene_info->cylinders[iter].rgb.b = 0;
		scene_info->cylinders[iter].height = 0;
		scene_info->cylinders[iter].diameter = 0;
		scene_info->cylinders[iter].coordinates.x = 0;
		scene_info->cylinders[iter].coordinates.y = 0;
		scene_info->cylinders[iter].coordinates.z = 0;
		scene_info->cylinders[iter].vector.x = 0;
		scene_info->cylinders[iter].vector.y = 0;
		scene_info->cylinders[iter].vector.z = 0;
		iter++;
	}
}

void	init_cone(t_scene_info *scene_info, t_identifier_count *id_count)
{
	int	iter;

	iter = 0;
	while (iter < id_count->co_count)
	{
		scene_info->cones[iter].rgb.r = 0;
		scene_info->cones[iter].rgb.g = 0;
		scene_info->cones[iter].rgb.b = 0;
		scene_info->cones[iter].height = 0;
		scene_info->cones[iter].diameter = 0;
		scene_info->cones[iter].apex.x = 0;
		scene_info->cones[iter].apex.y = 0;
		scene_info->cones[iter].apex.z = 0;
		scene_info->cones[iter].vector.x = 0;
		scene_info->cones[iter].vector.y = 0;
		scene_info->cones[iter].vector.z = 0;
		iter++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:59:20 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/06 14:03:03 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"


static void	init_sphere(t_scene_info *scene_info)
{
	scene_info->sphere.rgb_code = 0;
	scene_info->sphere.diameter = 0;
	scene_info->sphere.coordinates.x = 0;
	scene_info->sphere.coordinates.y = 0;
	scene_info->sphere.coordinates.z = 0;
}

static void	init_plane(t_scene_info *scene_info)
{
	scene_info->plane.coordinates.x = 0;
	scene_info->plane.coordinates.y = 0;
	scene_info->plane.coordinates.z = 0;
	scene_info->plane.vector.x = 0;
	scene_info->plane.vector.y = 0;
	scene_info->plane.vector.z = 0;
	scene_info->plane.rgb_code = 0;
}

static void	init_cylinder(t_scene_info *scene_info)
{
	scene_info->cylinder.rgb_code = 0;
	scene_info->cylinder.height = 0;
	scene_info->cylinder.diameter = 0;
	scene_info->cylinder.coordinates.x = 0;
	scene_info->cylinder.coordinates.y = 0;
	scene_info->cylinder.coordinates.z = 0;
	scene_info->cylinder.vector.x = 0;
	scene_info->cylinder.vector.y = 0;
	scene_info->cylinder.vector.z = 0;
}

void	init_scene_info(t_scene_info *scene_info)
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
	init_sphere(scene_info);
	init_plane(scene_info);
	init_cylinder(scene_info);
}

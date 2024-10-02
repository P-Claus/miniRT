/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light_camera_ambient.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:18:07 by pclaus            #+#    #+#             */
/*   Updated: 2024/10/02 22:18:20 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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

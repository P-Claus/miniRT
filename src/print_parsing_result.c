/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing_result.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:50:13 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/05 18:52:15 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	print_ambient_lighting(t_scene_info *scene_info)
{
	printf(" --------------------------------------------- \n");
	printf("|              Ambient lighting               |\n");
	printf("|                                             |\n");
	printf("|             Lighting ratio: %5.3f           |\n",
		scene_info->a_lighting.ambient_lighting);
	printf("|      RGB: %8f,%8f,%8f        |\n",
		scene_info->a_lighting.rgb.r,
		scene_info->a_lighting.rgb.g,
		scene_info->a_lighting.rgb.b);
	printf(" --------------------------------------------- \n");
}

static void	print_camera(t_scene_info *scene_info)
{
	printf(" --------------------------------------------- \n");
	printf("|                   Camera                    |\n");
	printf("|                                             |\n");
	printf("|            Viewpoint coordinates:           |\n");
	printf("|            %6.3f,%6.3f,%6.3f           |\n",
		scene_info->camera.coordinates.x,
		scene_info->camera.coordinates.y,
		scene_info->camera.coordinates.z);
	printf("|              Orientation vector:            |\n");
	printf("|             %6.3f,%6.3f,%6.3f            |\n",
		scene_info->camera.vector.x,
		scene_info->camera.vector.y,
		scene_info->camera.vector.z);
	printf("|                  FOV: %3d                   |\n",
		scene_info->camera.fov);
	printf(" --------------------------------------------- \n");
}

static void	print_light(t_scene_info *scene_info)
{
	printf(" --------------------------------------------- \n");
	printf("|                    Light                    |\n");
	printf("|                                             |\n");
	printf("|          Light point coordinates:           |\n");
	printf("|             %6.3f,%6.3f,%6.3f            |\n",
		scene_info->light.coordinates.x,
		scene_info->light.coordinates.y,
		scene_info->light.coordinates.z);
	printf("|        Light brightness ratio: %4.3f        |\n",
		scene_info->light.brightness);
	printf("|       RGB: %8f,%8f,%8f       |\n",
		scene_info->light.rgb.r,
		scene_info->light.rgb.g,
		scene_info->light.rgb.b);
	printf(" --------------------------------------------- \n");
}

void	print_parsing_result(t_scene_info *scene_info)
{
	print_ambient_lighting(scene_info);
	print_camera(scene_info);
	print_light(scene_info);
	print_spheres(scene_info);
	print_planes(scene_info);
	print_cylinders(scene_info, 0);
	print_cones(scene_info, 0);
}

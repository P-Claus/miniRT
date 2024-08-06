/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing_result.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:50:13 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/06 21:56:10 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	print_ambient_lighting(t_scene_info *scene_info)
{
	printf(" --------------------------------------------- \n");
	printf("|              Ambient lighting               |\n");
	printf("|              ~~~~~~~~~~~~~~~~               |\n");
	printf("|                                             |\n");
	printf("|             Lighting ratio: %4.2f            |\n",
			scene_info->A_lighting);
	printf("|              RGB: %3d,%3d,%3d               |\n",
			scene_info->A_rgb_code >> 16 & 0xFF,
			scene_info->A_rgb_code >> 8 & 0xFF,
			scene_info->A_rgb_code & 0xFF);
	printf(" --------------------------------------------- \n");
}

static void	print_camera(t_scene_info *scene_info)
{
	printf(" --------------------------------------------- \n");
	printf("|                   Camera                    |\n");
	printf("|                   ~~~~~~                    |\n");
	printf("|                                             |\n");
	printf("|   Viewpoint coordinates: %5.1f,%5.1f,%5.1f  |\n",
			scene_info->C_coordinates_vp.x,
			scene_info->C_coordinates_vp.y,
			scene_info->C_coordinates_vp.z);
	printf("|      Orientation vector: %4.1f,%4.1f,%4.1f     |\n",
			scene_info->C_coordinates_o.x,
			scene_info->C_coordinates_o.y,
			scene_info->C_coordinates_o.z);
	printf("|                  FOV: %3d                   |\n",
			scene_info->C_fov);
	printf(" --------------------------------------------- \n");
}

static void	print_light(t_scene_info *scene_info)
{
	printf(" --------------------------------------------- \n");
	printf("|                    Light                    |\n");
	printf("|                    ~~~~~                    |\n");
	printf("|                                             |\n");
	printf("| Light point coordinates: %5.1f,%5.1f,%5.1f  |\n",
			scene_info->L_cordinates_lp.x,
			scene_info->L_cordinates_lp.y,
			scene_info->L_cordinates_lp.z);
	printf("|         Light brightness ratio: %4.1f        |\n",
			scene_info->L_brightness);
	printf("|               RGB: %3d,%3d,%3d              |\n",
			scene_info->L_rgb_code >> 16 & 0xFF,
			scene_info->L_rgb_code >> 8 & 0xFF,
			scene_info->L_rgb_code & 0xFF);
	printf(" --------------------------------------------- \n");
}

void	print_scene_info(t_scene_info *scene_info)
{
	print_ambient_lighting(scene_info);
	print_camera(scene_info);
	print_light(scene_info);
}

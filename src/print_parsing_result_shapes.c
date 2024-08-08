/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing_result_shapes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:19:08 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/08 14:29:24 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	print_spheres(t_scene_info *scene_info)
{
	int	iter;

	iter = 0;
	while (iter < scene_info->nb_of_spheres)
	{
		printf(" --------------------------------------------- \n");
		printf("|                 Sphere #%d                   |\n", iter);
		printf("|                                             |\n");
		printf("|       Coordinates: %5.1f,%5.1f,%5.1f        |\n",
			scene_info->spheres[iter].coordinates.x,
			scene_info->spheres[iter].coordinates.y,
			scene_info->spheres[iter].coordinates.z);
		printf("|           Sphere diameter: %5.1f            |\n",
			scene_info->spheres[iter].diameter);
		printf("|               RGB: %3d,%3d,%3d              |\n",
			scene_info->spheres[iter].rgb_code >> 16 & 0xFF,
			scene_info->spheres[iter].rgb_code >> 8 & 0xFF,
			scene_info->spheres[iter].rgb_code & 0xFF);
		printf(" --------------------------------------------- \n");
		iter++;
	}
}

void	print_planes(t_scene_info *scene_info)
{
	int	iter;

	iter = 0;
	while (iter < scene_info->nb_of_planes)
	{
		printf(" --------------------------------------------- \n");
		printf("|                  Plane #%d                   |\n", iter);
		printf("|                                             |\n");
		printf("|       Coordinates: %5.1f,%5.1f,%5.1f        |\n",
			scene_info->planes[iter].coordinates.x,
			scene_info->planes[iter].coordinates.y,
			scene_info->planes[iter].coordinates.z);
		printf("|     Orientation vector: %4.1f,%4.1f,%4.1f      |\n",
			scene_info->planes[iter].vector.x,
			scene_info->planes[iter].vector.y,
			scene_info->planes[iter].vector.z);
		printf("|               RGB: %3d,%3d,%3d              |\n",
			scene_info->planes[iter].rgb_code >> 16 & 0xFF,
			scene_info->planes[iter].rgb_code >> 8 & 0xFF,
			scene_info->planes[iter].rgb_code & 0xFF);
		printf(" --------------------------------------------- \n");
		iter++;
	}
}

void	print_cylinders(t_scene_info *scene_info, int iter)
{
	while (iter < scene_info->nb_of_cylinders)
	{
		printf(" --------------------------------------------- \n");
		printf("|                 Cylinder #%d                 |\n", iter);
		printf("|                                             |\n");
		printf("|       Coordinates: %5.1f,%5.1f,%5.1f        |\n",
			scene_info->cylinders[iter].coordinates.x,
			scene_info->cylinders[iter].coordinates.y,
			scene_info->cylinders[iter].coordinates.z);
		printf("|     Orientation vector: %4.1f,%4.1f,%4.1f      |\n",
			scene_info->cylinders[iter].vector.x,
			scene_info->cylinders[iter].vector.y,
			scene_info->cylinders[iter].vector.z);
		printf("|           Cylinder diameter: %5.1f          |\n",
			scene_info->cylinders[iter].diameter);
		printf("|            Cylinder height: %5.1f           |\n",
			scene_info->cylinders[iter].height);
		printf("|               RGB: %3d,%3d,%3d              |\n",
			scene_info->cylinders[iter].rgb_code >> 16 & 0xFF,
			scene_info->cylinders[iter].rgb_code >> 8 & 0xFF,
			scene_info->cylinders[iter].rgb_code & 0xFF);
		printf(" --------------------------------------------- \n");
		iter++;
	}
}

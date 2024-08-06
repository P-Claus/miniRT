/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:35:09 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/06 22:15:55 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	check_capital_identifier(t_scene_info *scene_info, char *string,
		t_identifier_count *id_count)
{
	if (string[0] == '\n')
		return (0);
	if (string[0] == 'A' && string[1] == ' ' && id_count->has_A == false)
	{
		if (parse_ambient_lighting(scene_info, string) == 1)
			return (1);
		id_count->has_A = true;
		return (0);
	}
	else if (string[0] == 'C' && string[1] == ' ' && id_count->has_C == false)
	{
		if (parse_camera(scene_info, string) == 1)
			return (1);
		id_count->has_C = true;
		return (0);
	}
	else if (string[0] == 'L' && string[1] == ' ' && id_count->has_L == false)
	{
		if (parse_light(scene_info, string) == 1)
			return (1);
		id_count->has_L = true;
		return (0);
	}
	return (0);
}

int	check_shape_identifier(t_scene_info *scene_info, char *string)
{
	if (string[0] == '\n')
		return (0);
	if (string[0] == 's' && string[1] == 'p')
	{
		if (parse_sphere(scene_info, string) == 1)
			return (1);
	}
	else if (string[0] == 'p' && string[1] == 'l')
	{
		if (parse_plane(scene_info, string) == 1)
			return (1);
	}
	else if (string[0] == 'c' && string[1] == 'y')
	{
		if (parse_cylinder(scene_info, string) == 1)
			return (1);
	}
	return (0);
}

int	read_from_scene(t_scene_info *scene_info, int fd)
{
	char						*buffer;
	static t_identifier_count	id_count;
	int							counter;

	counter = 0;
	id_count.has_A = false;
	id_count.has_L = false;
	id_count.has_C = false;
	while (counter < 6)
	{
		buffer = get_next_line(fd);
		if (check_capital_identifier(scene_info, buffer, &id_count) == 1 ||
			check_shape_identifier(scene_info, buffer) == 1)
		{
			free(buffer);
			exit_handler("Error\nFormat error\n");
		}
		//    printf("\n--------------------------------------\n");
		//    printf("The buffer is: \n%s\n", buffer);
		//    printf("\n--------------------------------------\n");
		free(buffer);
		counter++;
	}
	print_scene_info(scene_info);
	/*
  printf("\n--------------------------------------\n");
  printf("A || lighting ratio: %.1f || RGB: %d\n", scene_info->A_lighting,
         scene_info->A_rgb_code);
  printf("C || viewpoint coordinates: x:%.1f, y:%.1f, z:%.1f || orientation "
         "vector: x:%.1f, y:%.1f, z:%.1f || FOV: %d\n",
         scene_info->C_coordinates_vp.x, scene_info->C_coordinates_vp.y,
         scene_info->C_coordinates_vp.z, scene_info->C_coordinates_o.x,
         scene_info->C_coordinates_o.y, scene_info->C_coordinates_o.z,
         scene_info->C_fov);
  printf("L || light coordinates: x%.1f, y:%.1f, z:%.1f || light brightness: "
         "%.1f || RGB: %d\n",
         scene_info->L_cordinates_lp.x, scene_info->L_cordinates_lp.y,
         scene_info->L_cordinates_lp.z, scene_info->L_brightness,
         scene_info->L_rgb_code);
  printf("sp || coordinates: x:%f, y:%f, z:%f || diameter: %f || RGB: %d\n",
         scene_info->sphere.coordinates.x, scene_info->sphere.coordinates.y,
         scene_info->sphere.coordinates.z, scene_info->sphere.diameter,
         scene_info->sphere.rgb_code);
  printf("pl || coordinates: x:%f, y:%f, z:%f || vector: x:%f, y:%f, z:%f || "
         "RGB: %d\n",
         scene_info->plane.coordinates.x, scene_info->plane.coordinates.y,
         scene_info->plane.coordinates.z, scene_info->plane.vector.x,
         scene_info->plane.vector.y, scene_info->plane.vector.z,
         scene_info->plane.rgb_code);
  printf("cy || coordinates: x:%f, y:%f, z:%f || vector: x:%f, y:%f, z:%f || "
         "diameter: %f || height: %f || RGB: %d\n",
         scene_info->cylinder.coordinates.x, scene_info->cylinder.coordinates.y,
         scene_info->cylinder.coordinates.z, scene_info->cylinder.vector.x,
         scene_info->cylinder.vector.y, scene_info->cylinder.vector.z,
         scene_info->cylinder.diameter, scene_info->cylinder.height,
         scene_info->cylinder.rgb_code);
  printf("\n--------------------------------------\n");
  */
	return (0);
}

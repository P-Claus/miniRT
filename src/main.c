/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:05:08 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/08 12:11:57 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	main(int argc, char **argv)
{
	int							fd;
	static t_identifier_count	id_count;

		t_scene_info	scene_info;
	//	scene_info.C_coordinates_vp = malloc(sizeof(t_camera_coordinates));
	//	if (!scene_info.C_coordinates_vp)
	//		exit_handler("Malloc failure\n");
	if (argc != 2)
		exit_handler("Error\nAdd the .rt file as single argument\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_handler("Error\nThe file does not exist\nFORMAT: ./miniRT path_to_file\n");
	if (count_identifiers_for_initialization(fd, &id_count, "start") == 1)
	{
		close(fd);
		exit_handler("Error\nError in A, C or L\n");
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	init_scene_info(&scene_info, &id_count);
	read_from_scene(&scene_info, fd, &id_count);
	free(scene_info.spheres);
	free(scene_info.planes);
	free(scene_info.cylinders);
	close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:05:08 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/05 12:24:20 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	main(int argc, char **argv)
{
	int	fd;
	t_scene_info	scene_info;
	
//	scene_info.C_coordinates_vp = malloc(sizeof(t_camera_coordinates));
//	if (!scene_info.C_coordinates_vp)
//		exit_handler("Malloc failure\n");
	if (argc != 2)
		exit_handler("Error\nAdd the .rt file as single argument\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_handler("Error\nThe file does not exist\nFORMAT: ./miniRT path_to_file\n");
	init_scene_info(&scene_info);
	read_from_scene(&scene_info, fd);
//	free(scene_info.C_coordinates_vp);
	close(fd);
}

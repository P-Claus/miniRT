/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:05:08 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/20 17:42:31 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	init_mlx_data(t_mlx_data *data)
{
	memset(data, 0, sizeof(t_mlx_data));
	data->width = SCREEN_WIDTH;
	data->height = SCREEN_HEIGHT;
	data->aspect = data->width / (float)data->height;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->mlx_win = mlx_new_window(data->mlx,
			data->width, data->height, "miniRT");
	if (!data->mlx_win)
		return (free_mlx(data), 1);
	data->render.img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->render.img)
		return (free_mlx(data), 1);
	data->render.addr = mlx_get_data_addr(data->render.img,
			&data->render.bpp,
			&data->render.line_len, &data->render.endian);
	mlx_loop_hook(data->mlx, handle_no_event, data);
	mlx_hook(data->mlx_win, DestroyNotify, 0L, handle_window_destroy, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, handle_keyrelease, data);
	mlx_hook(data->mlx_win, ButtonPress, ButtonPressMask, handle_mouse_press, data);
	mlx_hook(data->mlx_win, ButtonRelease, ButtonReleaseMask, handle_mouse_release, data);
	mlx_do_key_autorepeatoff(data->mlx);
	errno = 0;

	data->scene.camera.right = (t_coordinates){1, 0, 0};
	data->scene.camera.up = (t_coordinates){0, 1, 0};
	data->scene.camera.vector = (t_coordinates){0, 0, -1};
	data->low_res_lev = 5;
	data->speed = 0.5;

	return (0);
}

int	main(int argc, char **argv)
{
	int					fd;
	t_identifier_count	id_count;
	t_mlx_data			mlx_data;

	init_mlx_data(&mlx_data);
	if (argc != 2)
		exit_handler("Error\nAdd the .rt file as single argument\n");
	if (check_extension(argv[1]) == 1)
		exit_handler("Error\nThe file you tried to open doesn't have the .rt extension\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_handler("Error\nThe file does not exist\n");
	if (count_identifiers_for_initialization(fd, &id_count, "start") == 1)
	{
		close(fd);
		exit_handler("Error\nError in A, C or L\n");
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	init_scene_info(&mlx_data.scene, &id_count);
	read_from_scene(&mlx_data.scene, fd, &id_count);

	mlx_loop(mlx_data.mlx);
	free_mlx(&mlx_data);

	free(mlx_data.scene.spheres);
	free(mlx_data.scene.planes);
	free(mlx_data.scene.cylinders);
	free(mlx_data.scene.cones);
	close(fd);
}

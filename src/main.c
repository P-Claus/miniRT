/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:05:08 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/17 22:18:33 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	cleanup(t_mlx_data *mlx_data)
{
	if (mlx_data->mlx_win)
		mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
	if (mlx_data->mlx)
	{
		mlx_destroy_display(mlx_data->mlx);
		free(mlx_data->mlx);
	}
}

int	handle_no_event(t_mlx_data *data)
{
	if (!data || !data->mlx_win)
		return (1);
	return (0);
}

int	handle_keypress(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx);
	return (0);
}

int	handle_window_destroy(t_mlx_data *data)
{
	printf("WINDOW DESTROYED\n");
	mlx_loop_end(data->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	int							fd;
	static t_identifier_count	id_count;
	t_scene_info				scene_info;
	t_mlx_data					mlx_data;

	mlx_data.mlx = mlx_init();
	if (!mlx_data.mlx)
		return (1);
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, 860, 540, "miniRT");
	if (!mlx_data.mlx_win)
	{
		free(mlx_data.mlx);
		return (1);
	}
	mlx_loop_hook(mlx_data.mlx, handle_no_event, &mlx_data);
	mlx_hook(mlx_data.mlx_win, DestroyNotify, 0L, handle_window_destroy, &mlx_data);
	mlx_hook(mlx_data.mlx_win, KeyPress, KeyPressMask, handle_keypress, &mlx_data);

	if (argc != 2)
		exit_handler("Error\nAdd the .rt file as single argument\n");
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
	init_scene_info(&scene_info, &id_count);
	read_from_scene(&scene_info, fd, &id_count);
	free(scene_info.spheres);
	free(scene_info.planes);
	free(scene_info.cylinders);
	close(fd);

	mlx_loop(mlx_data.mlx);
	cleanup(&mlx_data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:32:53 by pclaus            #+#    #+#             */
/*   Updated: 2024/10/02 13:33:52 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	free_mlx_data(t_mlx_data *mlx_data)
{
	free(mlx_data->scene.spheres);
	free(mlx_data->scene.planes);
	free(mlx_data->scene.cylinders);
	free(mlx_data->scene.cones);
	free_mlx(mlx_data);
}

void	init_scene_setup_menu(t_mlx_data *mlx_data,
			t_identifier_count *id_count, int fd)
{
	init_scene_info(&mlx_data->scene, id_count);
	read_from_scene(&mlx_data->scene, fd, id_count);
	menu_set_select_page(mlx_data, &mlx_data->menu);
	menu_set_del_page(mlx_data, &mlx_data->menu);
}

void	init_mlx_functions(t_mlx_data *data)
{
	mlx_loop_hook(data->mlx, handle_no_event, data);
	mlx_hook(data->mlx_win, DestroyNotify, 0L, handle_window_destroy, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask,
		handle_keypress, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask,
		handle_keyrelease, data);
	mlx_hook(data->mlx_win, ButtonPress, ButtonPressMask,
		handle_mouse_press, data);
	mlx_hook(data->mlx_win, ButtonRelease, ButtonReleaseMask,
		handle_mouse_release, data);
	mlx_do_key_autorepeatoff(data->mlx);
	mlx_set_font(data->mlx, data->mlx_win, FONT);
}

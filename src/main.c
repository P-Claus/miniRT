/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:05:08 by pclaus            #+#    #+#             */
/*   Updated: 2024/10/03 18:44:58 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	init_image(t_mlx_data *data, t_my_img *img, t_pixel_coord size, int color)
{
	img->img = mlx_new_image(data->mlx, size.x, size.y);
	if (!img->img)
		return (1);
	img->addr = mlx_get_data_addr(
			img->img, &img->bpp, &img->line_len, &img->endian);
	if (color)
		img_draw_rect(*img, (t_pixel_coord){0, 0}, size, color);
	return (0);
}

int	init_ui_viewport( t_mlx_data *data, t_ui_viewport *ui_elem,
		t_pixel_coord pos, t_pixel_coord size)
{
	ui_elem->pos = pos;
	ui_elem->size = size;
	ui_elem->aspect = size.x / (float)size.y;
	return (init_image(data, &ui_elem->render, size, 0));
}

int	init_menu(t_mlx_data *data, t_ui_menu *menu)
{
	menu->size = (t_pixel_coord){MENU_WIDTH, SCREEN_HEIGHT};
	menu->pos.x = SCREEN_WIDTH - MENU_WIDTH;
	menu->pos.y = 0;
	if (init_image(data, &menu->bg, menu->size, 0x00282828))
		return (1);
	img_draw_rect(menu->bg, (t_pixel_coord){16, 46},
		(t_pixel_coord){menu->size.x - 32, SCREEN_HEIGHT - 72}, 0x001e1e1e);
	menu->show = MENU_SHOW;
	if (menu_init_pages(data, menu))
		return (1);
	menu->curr_page = &menu->pages[UI_MENU_PAGE_HOME];
	usleep(80000);
	return (0);
}

int	init_mlx_data(t_mlx_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->mlx_win = mlx_new_window(data->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT");
	if (!data->mlx_win)
		return (free_mlx(data), 1);
	if (init_ui_viewport(data, &data->full_render, (t_pixel_coord){0, 0},
		(t_pixel_coord){SCREEN_WIDTH, SCREEN_HEIGHT}))
		return (free_mlx(data), 1);
	if (init_ui_viewport(data, &data->viewport, (t_pixel_coord){0, 0},
		(t_pixel_coord){SCREEN_WIDTH - MENU_WIDTH, SCREEN_HEIGHT}))
		return (free_mlx(data), 1);
	if (init_menu(data, &data->menu))
		return (free_mlx(data), 1);
	errno = 0;
	init_mlx_functions(data);
	data->scene.camera.right = (t_coordinates){1, 0, 0};
	data->scene.camera.up = (t_coordinates){0, 1, 0};
	data->scene.camera.vector = (t_coordinates){0, 0, -1};
	data->low_res_lev = 8;
	data->speed = 0.5;
	return (0);
}

int	main(int argc, char **argv)
{
	int					fd;
	t_identifier_count	id_count;
	t_mlx_data			*mlx_data;

	mlx_data = ft_calloc(1, sizeof(t_mlx_data));
	file_error_check(mlx_data, argc, argv, &fd);
	if (count_identifiers_for_initialization(fd, &id_count, "start") == 1)
	{
		close(fd);
		free_mlx_data(mlx_data);
		exit_handler("Error\nError in A, C or L\n");
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (init_scene_setup_menu(mlx_data, &id_count, fd) == 1)
	{
		close(fd);
		free_mlx(mlx_data);
		exit_handler("Error\nFormat error\n");
	}
	mlx_loop(mlx_data->mlx);
	free_mlx_data(mlx_data);
	close(fd);
}

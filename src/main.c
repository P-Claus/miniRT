/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:05:08 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/24 11:50:11 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	init_image(t_mlx_data *data, t_my_img *img, t_pixel_coord size)
{
	img->img = mlx_new_image(data->mlx, size.x, size.y);
	if (!img->img)
		return (1);
	img->addr = mlx_get_data_addr(img->img,
		&img->bpp, &img->line_len, &img->endian);
	return (0);
}

int	init_ui_viewport(t_mlx_data *data, t_ui_viewport *ui_elem, t_pixel_coord pos, t_pixel_coord size)
{
	ui_elem->pos = pos;
	ui_elem->size = size;
	ui_elem->aspect = size.x / (float)size.y;

	return (init_image(data, &ui_elem->render, size));
}

int	init_menu(t_mlx_data *data, t_ui_menu *menu)
{
	menu->size = (t_pixel_coord){MENU_WIDTH, SCREEN_HEIGHT};
	menu->pos.x = SCREEN_WIDTH - MENU_WIDTH;
	menu->pos.y = 0;
	if (init_image(data, &menu->bg, menu->size))
		return (1);
	memset(menu->bg.addr, 0x28, menu->size.x * menu->size.y * 4);
	menu->show = MENU_SHOW;
	menu_init_pages(data, menu);
	menu->curr_page = &menu->pages[UI_MENU_PAGE_HOME];
	usleep(80000); // Is because shared memory image would be black if we dont wait a bit. (Solve it by opening the program with a loading animation !)
	return (0);
}

int	init_mlx_data(t_mlx_data *data)
{
	memset(data, 0, sizeof(t_mlx_data));

	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->mlx_win = mlx_new_window(data->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT");
	if (!data->mlx_win)
		return (free_mlx(data), 1);

	if (init_ui_viewport(data, &data->full_render, (t_pixel_coord){0, 0}, (t_pixel_coord){SCREEN_WIDTH, SCREEN_HEIGHT}))
		return (free_mlx(data), 1);
	if (init_ui_viewport(data, &data->viewport, (t_pixel_coord){0, 0}, (t_pixel_coord){SCREEN_WIDTH - MENU_WIDTH, SCREEN_HEIGHT}))
		return (free_mlx(data), 1);
	if (init_menu(data, &data->menu))
		return (free_mlx(data), 1);

	mlx_loop_hook(data->mlx, handle_no_event, data);
	mlx_hook(data->mlx_win, DestroyNotify, 0L, handle_window_destroy, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, handle_keyrelease, data);
	mlx_hook(data->mlx_win, ButtonPress, ButtonPressMask, handle_mouse_press, data);
	mlx_hook(data->mlx_win, ButtonRelease, ButtonReleaseMask, handle_mouse_release, data);
	errno = 0;

	mlx_set_font(data->mlx, data->mlx_win, FONT);

	data->scene.camera.right = (t_coordinates){1, 0, 0};
	data->scene.camera.up = (t_coordinates){0, 1, 0};
	data->scene.camera.vector = (t_coordinates){0, 0, -1};

	return (0);
}

int	main(int argc, char **argv)
{
	int					fd;
	t_identifier_count	id_count;
	t_mlx_data			*mlx_data;

	mlx_data = ft_calloc(1, sizeof(t_mlx_data));
	init_mlx_data(mlx_data);
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
	init_scene_info(&mlx_data->scene, &id_count);
	read_from_scene(&mlx_data->scene, fd, &id_count);
	menu_set_select_page(mlx_data, &mlx_data->menu);
	menu_set_del_page(mlx_data, &mlx_data->menu);

	mlx_loop(mlx_data->mlx);

	free(mlx_data->scene.spheres);
	free(mlx_data->scene.planes);
	free(mlx_data->scene.cylinders);
	free_mlx(mlx_data);
	close(fd);
}

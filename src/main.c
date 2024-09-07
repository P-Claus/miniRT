/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:05:08 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/07 20:24:18 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	*my_mlx_new_window(t_xvar *xvar, t_win_list *win, t_ui_viewport ui, char *title)
{
	t_win_list				*new_win;
	XSetWindowAttributes	xswa;
	XGCValues				xgcv;
	Window					parent;

	xswa.background_pixel = 0;
	xswa.border_pixel = -1;
	xswa.colormap = xvar->cmap;
	xswa.event_mask = 0xFFFFFF;	/* all events */
	if (!(new_win = malloc(sizeof(*new_win))))
		return ((void *)0);
	parent = xvar->root;
	if (win && win->window)
		parent = win->window;
	new_win->window = XCreateWindow(xvar->display,parent,ui.pos.x,ui.pos.y,ui.size.x,ui.size.y,
					0,CopyFromParent,InputOutput,xvar->visual,
					CWEventMask|CWBackPixel|CWBorderPixel|
					CWColormap,&xswa);
	mlx_int_anti_resize_win(xvar,new_win->window,ui.size.x,ui.size.y);
	if (title)
		XStoreName(xvar->display,new_win->window,title);
	XSetWMProtocols(xvar->display, new_win->window, &(xvar->wm_delete_window), 1);
	xgcv.foreground = -1;
	xgcv.function = GXcopy;
	xgcv.plane_mask = AllPlanes;
	new_win->gc = XCreateGC(xvar->display,new_win->window,
				GCFunction|GCPlaneMask|GCForeground,&xgcv);
	new_win->next = xvar->win_list;
	xvar->win_list = new_win;
	bzero(&(new_win->hooks), sizeof(new_win->hooks));
	XMapRaised(xvar->display,new_win->window);
	mlx_int_wait_first_expose(xvar,new_win->window);
	return (new_win);
}

void	*my_mlx_new_menu_window(t_xvar *xvar, t_win_list *win, t_ui_elem ui, char *title)
{
	t_win_list				*new_win;
	XSetWindowAttributes	xswa;
	XGCValues				xgcv;
	Window					parent;

	xswa.background_pixel = 0;
	xswa.border_pixel = -1;
	xswa.colormap = xvar->cmap;
	xswa.event_mask = 0xFFFFFF;	/* all events */
	if (!(new_win = malloc(sizeof(*new_win))))
		return ((void *)0);
	parent = xvar->root;
	if (win && win->window)
		parent = win->window;
	new_win->window = XCreateWindow(xvar->display,parent,ui.pos.x,ui.pos.y,ui.size.x,ui.size.y,
					0,CopyFromParent,InputOutput,xvar->visual,
					CWEventMask|CWBackPixel|CWBorderPixel|
					CWColormap,&xswa);
	mlx_int_anti_resize_win(xvar,new_win->window,ui.size.x,ui.size.y);
	if (title)
		XStoreName(xvar->display,new_win->window,title);
	XSetWMProtocols(xvar->display, new_win->window, &(xvar->wm_delete_window), 1);
	xgcv.foreground = -1;
	xgcv.function = GXcopy;
	xgcv.plane_mask = AllPlanes;
	new_win->gc = XCreateGC(xvar->display,new_win->window,
				GCFunction|GCPlaneMask|GCForeground,&xgcv);
	new_win->next = xvar->win_list;
	xvar->win_list = new_win;
	bzero(&(new_win->hooks), sizeof(new_win->hooks));
	XMapRaised(xvar->display,new_win->window);
	mlx_int_wait_first_expose(xvar,new_win->window);
	return (new_win);
}

# define MENU_HEIGHT 20

int	init_screen(t_mlx_data *data)
{
	data->screen.pos.x = 0;
	data->screen.pos.y = 0;
	data->screen.size.x = SCREEN_WIDTH;
	data->screen.size.y = SCREEN_HEIGHT;
	data->screen.aspect = SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	data->screen.window = mlx_new_window(data->mlx,
			data->screen.size.x, data->screen.size.y, "miniRT");
	if (!data->screen.window)
		return (free_mlx(data), 1);
	data->screen.render.img = mlx_new_image(data->mlx, data->screen.size.x, data->screen.size.y);
	if (!data->screen.render.img)
		return (free_mlx(data), 1);
	data->screen.render.addr = mlx_get_data_addr(data->screen.render.img, &data->screen.render.bpp,
			&data->screen.render.line_len, &data->screen.render.endian);
	mlx_hook(data->screen.window, DestroyNotify, 0L, handle_window_destroy, data);
	return (0);
}

int	init_full_render(t_mlx_data *data)
{
	data->full_render.pos.x = 0;
	data->full_render.pos.y = 0;
	data->full_render.size.x = SCREEN_WIDTH;
	data->full_render.size.y = SCREEN_HEIGHT;
	data->full_render.aspect = SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	data->full_render.window = my_mlx_new_window(data->mlx, data->screen.window, data->full_render, NULL);
	if (!data->full_render.window)
		return (free_mlx(data), 1);
	data->full_render.render.img = mlx_new_image(data->mlx, data->full_render.size.x, data->full_render.size.y);
	if (!data->full_render.render.img)
		return (free_mlx(data), 1);
	data->full_render.render.addr = mlx_get_data_addr(data->full_render.render.img, &data->full_render.render.bpp,
			&data->full_render.render.line_len, &data->full_render.render.endian);
	mlx_hook(data->full_render.window, DestroyNotify, 0L, handle_window_destroy, data);
	mlx_hook(data->full_render.window, KeyPress, KeyPressMask, handle_keypress_render, data);
	return (0);
}

int	init_viewport(t_mlx_data *data)
{
	data->viewport.pos.x = 0;
	data->viewport.pos.y = MENU_HEIGHT;
	data->viewport.size.x = SCREEN_WIDTH;
	data->viewport.size.y = (SCREEN_HEIGHT - MENU_HEIGHT);
	data->viewport.aspect = SCREEN_WIDTH / (float)(SCREEN_HEIGHT - MENU_HEIGHT);
	data->viewport.window = my_mlx_new_window(data->mlx,data->screen.window, data->viewport, NULL);
	if (!data->viewport.window)
		return (free_mlx(data), 1);
	data->viewport.render.img = mlx_new_image(data->mlx, data->viewport.size.x, data->viewport.size.y);
	if (!data->viewport.render.img)
		return (free_mlx(data), 1);
	data->viewport.render.addr = mlx_get_data_addr(data->viewport.render.img, &data->viewport.render.bpp,
			&data->viewport.render.line_len, &data->viewport.render.endian);
	mlx_hook(data->viewport.window, DestroyNotify, 0L, handle_window_destroy, data);
	mlx_hook(data->viewport.window, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->viewport.window, KeyRelease, KeyReleaseMask, handle_keyrelease, data);
	mlx_hook(data->viewport.window, ButtonPress, ButtonPressMask, handle_mouse_press, data);
	mlx_hook(data->viewport.window, ButtonRelease, ButtonReleaseMask, handle_mouse_release, data);
	return (0);
}

int	init_menu(t_mlx_data *data)
{
	data->menu.pos.x = 0;
	data->menu.pos.y = 0;
	data->menu.size.x = SCREEN_WIDTH;
	data->menu.size.y = MENU_HEIGHT;
	data->menu.window = my_mlx_new_menu_window(data->mlx,data->screen.window, data->menu, NULL);
	if (!data->menu.window)
		return (free_mlx(data), 1);
	mlx_hook(data->menu.window, DestroyNotify, 0L, handle_window_destroy, data);
	mlx_hook(data->menu.window, ButtonPress, ButtonPressMask, handle_menu_mouse_press, data);
	return (0);
}

int	init_mlx_data(t_mlx_data *data)
{
	memset(data, 0, sizeof(t_mlx_data));
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	init_screen(data);
	init_full_render(data);
	init_viewport(data);
	init_menu(data);
	mlx_do_key_autorepeatoff(data->mlx);
	mlx_loop_hook(data->mlx, handle_no_event, data);
	XMapRaised(((t_xvar *)data->mlx)->display, ((t_win_list *)data->full_render.window)->window);
	XUnmapWindow(((t_xvar *)data->mlx)->display, ((t_win_list *)data->full_render.window)->window);
	errno = 0;
	data->scene.camera.right = (t_coordinates){1, 0, 0};
	data->scene.camera.up = (t_coordinates){0, 1, 0};
	data->scene.camera.vector = (t_coordinates){0, 0, -1};
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
	close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:17:14 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 16:30:05 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

char	*get_obj_name(t_object_type type)
{
	if (type == OBJ_NONE)
		return ("NONE");
	else if (type == OBJ_SPHERE)
		return ("Sphere");
	else if (type == OBJ_PLANE)
		return ("Plane");
	else if (type == OBJ_CYLINDER)
		return ("Cylinder");
	else if (type == OBJ_CONE)
		return ("Cone");
	return ("INVALID_TYPE");
}

void	select_obj(t_mlx_data *data)
{
	t_hit_info		hit;
	t_ui_viewport	ui;

	if (data->menu.show && box_is_clicked(
			data->menu.pos, data->menu.size, data->mouse_last_pos))
		return (menu_page_click(data), (void)0);
	ui = data->full_render;
	if (data->menu.show && !data->full_res)
		ui = data->viewport;
	hit = cast_ray(calc_ray(
				data->scene.camera, ui, data->mouse_last_pos), data->scene);
	if (hit.obj_type == OBJ_NONE
		|| (data->selected.obj_type == hit.obj_type
			&& data->selected.obj_index == hit.obj_index))
	{
		printf("De-selected obj: %s #%zu\n",
			get_obj_name(data->selected.obj_type), data->selected.obj_index);
		data->selected = (t_hit_info){OBJ_NONE, 0, 0, {0, 0, 0}};
		set_menu_page(data);
		return ;
	}
	data->selected = hit;
	set_menu_page(data);
	printf("Selected obj: %s #%zu\n",
		get_obj_name(data->selected.obj_type), data->selected.obj_index);
}

int	handle_mouse_press(int button, int x, int y, t_mlx_data *data)
{
	if (button > 5)
		return (0);
	if (data->menu.show)
		data->menu.show = MENU_SHOW;
	data->mouse_last_pos.x = x;
	data->mouse_last_pos.y = y;
	if (button == 1)
	{
		data->mouse_input_state ^= BTN_LEFT;
		select_obj(data);
	}
	else if (button == 3)
	{
		data->mouse_input_state ^= BTN_RIGHT;
		if (data->menu.curr_input_elem)
		{
			free(data->menu.curr_input_str);
			data->menu.curr_input_elem = NULL;
		}
	}
	else if (button == 4)
	{
		if (data->menu.show && box_is_clicked(data->menu.pos, data->menu.size, data->mouse_last_pos))
			data->menu.curr_page->scroll = fmin(data->menu.curr_page->scroll + ELEM_HEIGHT, 0);
		else
			data->scene.camera.fov = fmax(data->scene.camera.fov - 1, 5);
	}
	else if (button == 5)
	{
		if (data->menu.show && box_is_clicked(data->menu.pos, data->menu.size, data->mouse_last_pos))
			data->menu.curr_page->scroll = fmax(data->menu.curr_page->scroll - ELEM_HEIGHT, fmin(data->menu.curr_page->size.y - data->menu.curr_page->pos.y - ELEM_OFFSET - ELEM_HEIGHT - data->menu.curr_page->n_elems * ELEM_HEIGHT, 0));
		else
			data->scene.camera.fov = fmin(data->scene.camera.fov + 1, 175);
	}
	data->full_res = REND_LOW;
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_mlx_data *data)
{
	(void)x;
	(void)y;
	if (button > 5)
		return (0);
	if (button == 1)
		data->mouse_input_state ^= BTN_LEFT;
	else if (button == 3)
		data->mouse_input_state ^= BTN_RIGHT;
	return (0);
}

int	handle_window_destroy(t_mlx_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

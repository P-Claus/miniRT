/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:17:14 by efret             #+#    #+#             */
/*   Updated: 2024/10/03 19:55:55 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	handle_mouse_scroll(int button, t_mlx_data *data)
{
	if (button == 4)
	{
		if (data->menu.show && box_is_clicked(
				data->menu.pos, data->menu.size, data->mouse_last_pos))
			data->menu.curr_page->scroll = 
				fmin(data->menu.curr_page->scroll + ELEM_HEIGHT, 0);
		else
			data->scene.camera.fov = fmax(data->scene.camera.fov - 1, 5);
	}
	else if (button == 5)
	{
		if (data->menu.show && box_is_clicked(
				data->menu.pos, data->menu.size, data->mouse_last_pos))
			data->menu.curr_page->scroll = 
				fmax(data->menu.curr_page->scroll - ELEM_HEIGHT, 
					fmin(data->menu.curr_page->size.y - 
						data->menu.curr_page->pos.y - ELEM_OFFSET - ELEM_HEIGHT
						- data->menu.curr_page->n_elems * ELEM_HEIGHT, 0));
		else
			data->scene.camera.fov = fmin(data->scene.camera.fov + 1, 175);
	}
	else
		return (0);
	return (1);
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
	else if (handle_mouse_scroll(button, data))
		;
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
	if (data->menu.curr_input_elem)
	{
		if (data->menu.curr_input_str)
			free(data->menu.curr_input_str);
		data->menu.curr_input_elem = NULL;
	}
	return (0);
}

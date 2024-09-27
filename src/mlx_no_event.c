/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_no_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:09:01 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 17:21:14 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	mouse_drag(t_mlx_data *data)
{
	t_pixel_coord	mouse;
	t_pixel_coord	diff;
	float			speed;

	if (!(data->mouse_input_state & BTN_RIGHT
			|| data->mouse_input_state & BTN_LEFT))
		return ;
	mlx_mouse_get_pos(data->mlx, data->mlx_win, &mouse.x, &mouse.y);
	diff.x = mouse.x - data->mouse_last_pos.x;
	diff.y = mouse.y - data->mouse_last_pos.y;
	data->mouse_last_pos.x = mouse.x;
	data->mouse_last_pos.y = mouse.y;
	speed = data->speed
		* (1 + ((data->key_input_state & KEY_SHIFT) != 0))
		/ (1 + ((data->key_input_state & KEY_CTRL) != 0));
	if (data->mouse_input_state & BTN_LEFT
		&& data->menu.curr_input_elem
		&& data->menu.curr_input_elem->type == UI_MENU_NBOX)
		menu_nbox_slide(data, data->menu.curr_input_elem, diff);
	if (data->mouse_input_state & BTN_RIGHT
		&& data->selected.obj_type == OBJ_NONE)
		rotate_camera(&data->scene.camera, diff, speed);
	else if (data->mouse_input_state & BTN_RIGHT)
		rotate_obj(data, diff, speed);
}

void	key_inputs(t_mlx_data *data)
{
	float	speed;

	speed = data->speed * data->frame_time
		* (1 + ((data->key_input_state & KEY_SHIFT) != 0))
		/ (1 + ((data->key_input_state & KEY_CTRL) != 0));
	if (data->selected.obj_type == OBJ_NONE)
		move_camera(&data->scene.camera, data->key_input_state, speed);
	else
		move_obj(data, data->key_input_state, speed);
}

void	check_input_states(t_mlx_data *data)
{
	mouse_drag(data);
	key_inputs(data);
	if (data->menu.show && (data->key_input_state || data->mouse_input_state))
		data->menu.show = MENU_SHOW;
}

int	handle_no_event_full_render(t_mlx_data *data)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	data->selected = (t_hit_info){OBJ_NONE, 0, 0, {0, 0, 0}};
	set_menu_page(data);
	printf("Rendering scene ...\n");
	render(data, data->full_render);
	gettimeofday(&end, NULL);
	printf("Rendered in: %.3f ms\n", frame_time(start, end));
	data->full_res = REND_DONE;
	return (0);
}

int	handle_no_event(t_mlx_data *data)
{
	struct timeval	start;
	struct timeval	end;

	if (!data || !data->mlx_win)
		return (1);
	if (data->full_res != REND_DONE)
	{
		if (data->full_res == REND_HIGH)
			return (handle_no_event_full_render(data));
		gettimeofday(&start, NULL);
		check_input_states(data);
		if (data->menu.show == MENU_SHOW)
			menu_draw(data, &data->menu);
		if (!data->menu.show)
			render_low_res(data, data->full_render, data->low_res_lev);
		else
			render_low_res(data, data->viewport, data->low_res_lev);
		gettimeofday(&end, NULL);
		data->frame_time = frame_time(start, end);
		image_add_frametime(data);
	}
	return (0);
}

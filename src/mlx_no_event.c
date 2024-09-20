/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_no_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:09:01 by efret             #+#    #+#             */
/*   Updated: 2024/09/20 17:59:15 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	mouse_drag(t_mlx_data *data)
{
	t_pixel_coord	mouse;
	t_pixel_coord	diff;
	float			speed;

	if (!(data->mouse_input_state & BTN_RIGHT))
		return ;
	mlx_mouse_get_pos(data->mlx, data->mlx_win, &mouse.x, &mouse.y);
	diff.x = mouse.x - data->mouse_last_pos.x;
	diff.y = mouse.y - data->mouse_last_pos.y;
	data->mouse_last_pos.x = mouse.x;
	data->mouse_last_pos.y = mouse.y;
	speed = data->speed
		* (1 + ((data->key_input_state & KEY_SHIFT) != 0))
		/ (1 + ((data->key_input_state & KEY_CTRL) != 0));
	if (data->selected.obj_type == OBJ_NONE)
		rotate_camera(&data->scene.camera, diff, speed);
	else
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
}

void	image_add_frametime(t_mlx_data *data)
{
	char	*tmp;
	char	*str;
	char	*ms;
	char	*decimal;

	ms = ft_itoa(data->frame_time);
	decimal = ft_itoa((data->frame_time - floor(data->frame_time)) * 100);
	if (!ms || !decimal)
		return (free(ms), free(decimal));
	str = ft_strjoin(ms, ".");
	if (!str)
		return (free(ms), free(decimal));
	tmp = ft_strjoin(str, decimal);
	free(str);
	if (!tmp)
		return (free(ms), free(decimal));
	str = ft_strjoin(tmp, "ms");
	if (!str)
		return (free(ms), free(decimal), free(tmp));
	mlx_string_put(data->mlx, data->mlx_win, 15, 15, 0x00FFFFFF, str);
	return (free(ms), free(decimal), free(tmp), free(str));
}

int	handle_no_event(t_mlx_data *data)
{
	struct timeval	start;
	struct timeval	end;

	if (!data || !data->mlx_win)
		return (1);
	if (data->full_res != REND_DONE)
	{
		gettimeofday(&start, NULL);
		if (data->full_res == REND_HIGH)
		{
			data->selected = (t_hit_info){OBJ_NONE, 0, 0, {0, 0, 0}};
			printf("Rendering scene ...\n");
			render(data);
			gettimeofday(&end, NULL);
			printf("Rendered in: %.3f ms\n", frame_time(start, end));
			data->full_res = REND_DONE;
			return (0);
		}
		check_input_states(data);
		render_low_res(data, data->low_res_lev, data->low_res_lev);
		gettimeofday(&end, NULL);
		data->frame_time = frame_time(start, end);
		image_add_frametime(data);
	}
	return (0);
}

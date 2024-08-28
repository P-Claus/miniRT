/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:17:14 by efret             #+#    #+#             */
/*   Updated: 2024/08/28 22:14:38 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	mouse_drag(t_mlx_data *data)
{
	t_pixel_coord	mouse;

	if (!data->mouse_input_state || data->key_input_state & KEY_SPACE)
		return (0);
	mlx_mouse_get_pos(data->mlx, data->mlx_win, &mouse.x, &mouse.y);
	t_pixel_coord	diff = {mouse.x - data->mouse_last_pos.x, mouse.y - data->mouse_last_pos.y};
	printf("mouse moved from (%i, %i) to (%i, %i) for a difference of (%i, %i)\n", data->mouse_last_pos.x, data->mouse_last_pos.y, mouse.x, mouse.y, diff.x, diff.y);
	data->mouse_last_pos.x = mouse.x;
	data->mouse_last_pos.y = mouse.y;
	data->scene.camera.coordinates.x += diff.x * 0.001 * data->frame_time;
	data->scene.camera.coordinates.y -= diff.y * 0.001 * data->frame_time;
	return (0);
}

int	handle_no_event(t_mlx_data *data)
{
	if (!data || !data->mlx_win)
		return (1);
	mouse_drag(data);
	if (!(data->key_input_state & KEY_SPACE))
		render(data);
	else
		return (0);
	if (data->key_input_state & KEY_A)
		data->scene.camera.coordinates.x -= 0.1 * data->frame_time;
	if (data->key_input_state & KEY_D)
		data->scene.camera.coordinates.x += 0.1 * data->frame_time;
	if (data->key_input_state & KEY_W)
		data->scene.camera.coordinates.z -= 0.1 * data->frame_time;
	if (data->key_input_state & KEY_S)
		data->scene.camera.coordinates.z += 0.1 * data->frame_time;
	if (data->key_input_state & KEY_Q)
		data->scene.camera.coordinates.y -= 0.1 * data->frame_time;
	if (data->key_input_state & KEY_E)
		data->scene.camera.coordinates.y += 0.1 * data->frame_time;
	return (0);
}

int	handle_keypress(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx);
	else if (keysym == XK_space)
		data->key_input_state ^= KEY_SPACE;
	else if (keysym == XK_a)
		data->key_input_state ^= KEY_A;
	else if (keysym == XK_d)
		data->key_input_state ^= KEY_D;
	else if (keysym == XK_w)
		data->key_input_state ^= KEY_W;
	else if (keysym == XK_s)
		data->key_input_state ^= KEY_S;
	else if (keysym == XK_q)
		data->key_input_state ^= KEY_Q;
	else if (keysym == XK_e)
		data->key_input_state ^= KEY_E;
	return (0);
}

int	handle_keyrelease(int keysym, t_mlx_data *data)
{
	if (keysym == XK_a)
		data->key_input_state ^= KEY_A;
	else if (keysym == XK_d)
		data->key_input_state ^= KEY_D;
	else if (keysym == XK_w)
		data->key_input_state ^= KEY_W;
	else if (keysym == XK_s)
		data->key_input_state ^= KEY_S;
	else if (keysym == XK_q)
		data->key_input_state ^= KEY_Q;
	else if (keysym == XK_e)
		data->key_input_state ^= KEY_E;
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_mlx_data *data)
{
	if (button > 5)
		return (0);
	if (button == 1)
	{
		data->mouse_last_pos.x = x;
		data->mouse_last_pos.y = y;
		data->mouse_input_state ^= BTN_LEFT;
		printf("Pressed left mouse button at (%i, %i)\n", x, y);
	}
	else if (button == 3)
	{
		data->mouse_last_pos.x = x;
		data->mouse_last_pos.y = y;
		data->mouse_input_state ^= BTN_RIGHT;
		printf("Pressed right mouse button at (%i, %i)\n", x, y);
	}
	else if (button == 4)
	{
		printf("trying to zoom in\n");
	}
	else if (button == 5)
	{
		printf("trying to zoom out\n");
	}
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_mlx_data *data)
{
	if (button > 3)
		return (0);
	if (button == 1)
	{
		data->mouse_input_state ^= BTN_LEFT;
		printf("Released left mouse button at (%i, %i)\n", x, y);
	}
	else if (button == 3)
	{
		data->mouse_input_state ^= BTN_RIGHT;
		printf("Released right mouse button at (%i, %i)\n", x, y);
	}
	return (0);
}

int	handle_window_destroy(t_mlx_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

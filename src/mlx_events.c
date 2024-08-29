/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:17:14 by efret             #+#    #+#             */
/*   Updated: 2024/08/30 00:18:57 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	rotate_camera(t_camera *camera, t_pixel_coord mouse_diff, float frame_time)
{
	t_quat	q1;
	t_quat	q2;

	camera->yaw = mouse_diff.x * DEG2RAD * 0.005 * frame_time;
	camera->pitch = mouse_diff.y * DEG2RAD * 0.005 * frame_time;
	q1 = quat_axis_rot(camera->right, camera->pitch);
	q2 = quat_axis_rot((t_coordinates){0, 1, 0}, camera->yaw);
	camera->rotation = quat_mult(q1, q2);
	camera->up = quat_rotate_point(camera->up, camera->rotation);
	camera->right = quat_rotate_point(camera->right, camera->rotation);
	camera->vector = quat_rotate_point(camera->vector, camera->rotation);
}

void	mouse_drag(t_mlx_data *data)
{
	t_pixel_coord	mouse;

	if (!data->mouse_input_state || data->key_input_state & KEY_SPACE)
		return ;
	mlx_mouse_get_pos(data->mlx, data->mlx_win, &mouse.x, &mouse.y);
	t_pixel_coord	diff = {mouse.x - data->mouse_last_pos.x, mouse.y - data->mouse_last_pos.y};
	//printf("mouse moved from (%i, %i) to (%i, %i) for a difference of (%i, %i)\n", data->mouse_last_pos.x, data->mouse_last_pos.y, mouse.x, mouse.y, diff.x, diff.y);
	data->mouse_last_pos.x = mouse.x;
	data->mouse_last_pos.y = mouse.y;
	rotate_camera(&data->scene.camera, diff, data->frame_time);
}

void	move_camera(t_camera *camera, long key_state, float frame_time)
{
	t_coordinates	move_dir;
	t_coordinates	world_move_dir;

	if (!key_state)
		return ;
	move_dir.x = ((key_state & KEY_D) > 0) - ((key_state & KEY_A) > 0);
	move_dir.y = ((key_state & KEY_E) > 0) - ((key_state & KEY_Q) > 0);
	move_dir.z = ((key_state & KEY_S) > 0) - ((key_state & KEY_W) > 0);
	//move_dir = vec3_normalize(move_dir);

	world_move_dir.x = vec3_dot(camera->right, move_dir);
	world_move_dir.y = vec3_dot(camera->up, move_dir);
	world_move_dir.z = vec3_dot(camera->vector, move_dir);
	world_move_dir = vec3_normalize(world_move_dir);

	camera->coordinates = vec3_sum(camera->coordinates, vec3_scalar(move_dir, 0.1 * frame_time));
}

int	handle_no_event(t_mlx_data *data)
{
	if (!data || !data->mlx_win)
		return (1);
	mouse_drag(data);
	if (!(data->key_input_state & KEY_SPACE))
	{
		move_camera(&data->scene.camera, data->key_input_state, data->frame_time);
		render(data);
	}
	else
		return (0);
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
		data->scene.camera.fov = fmax(data->scene.camera.fov - 1, 30);
	}
	else if (button == 5)
	{
		data->scene.camera.fov = fmin(data->scene.camera.fov + 1, 130);
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

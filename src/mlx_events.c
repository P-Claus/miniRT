/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:17:14 by efret             #+#    #+#             */
/*   Updated: 2024/09/04 17:01:00 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	rotate_camera(t_camera *camera, t_pixel_coord mouse_diff, float frame_time)
{
	t_quat	q_yaw;
	t_quat	q_pitch;
	float	yaw_diff;
	float	pitch_diff;

	(void)frame_time;
	yaw_diff = mouse_diff.x * DEG2RAD;
	pitch_diff = mouse_diff.y * DEG2RAD;
	if (camera->pitch + pitch_diff <= -(90 * DEG2RAD) || 90 * DEG2RAD <= camera->pitch + pitch_diff)
		pitch_diff = 0;
	camera->yaw += yaw_diff;
	camera->pitch += pitch_diff;
	q_yaw = quat_axis_rot((t_coordinates){0, 1, 0}, camera->yaw);
	q_pitch = quat_axis_rot((t_coordinates){1, 0, 0}, camera->pitch);
	camera->rotation = quat_mult(q_yaw, q_pitch);

	camera->vector = vec3_normalize(quat_rotate_point((t_coordinates){0, 0, -1}, camera->rotation));
	camera->right = vec3_normalize(quat_rotate_point((t_coordinates){1, 0, 0}, camera->rotation));
	camera->up = vec3_normalize(quat_rotate_point((t_coordinates){0, 1, 0}, camera->rotation));
}

void	rotate_obj(t_mlx_data *data, t_pixel_coord mouse_diff, float frame_time)
{
	t_quat	q_yaw;
	t_quat	q_pitch;
	t_quat	q_roll;
	t_quat	q;
	t_coordinates	rot_diffs;

	(void)frame_time;
	if (data->selected.obj_type == OBJ_SPHERE)
		return;

	if (data->key_input_state & KEY_CTRL)
	{
		rot_diffs.x = 0;
		rot_diffs.y = -mouse_diff.y * DEG2RAD;
		rot_diffs.z = mouse_diff.x * DEG2RAD;
	}
	else
	{
		rot_diffs.x = mouse_diff.x * DEG2RAD;
		rot_diffs.y = -mouse_diff.y * DEG2RAD;
		rot_diffs.z = 0;
	}

	q_yaw = quat_axis_rot((t_coordinates){0, 1, 0}, rot_diffs.x);
	q_pitch = quat_axis_rot((t_coordinates){1, 0, 0}, rot_diffs.y);
	q_roll = quat_axis_rot((t_coordinates){0, 0, 1}, rot_diffs.z);
	q = quat_mult(q_yaw, q_pitch);
	q = quat_mult(q, q_roll);

	if (data->selected.obj_type == OBJ_PLANE)
		data->scene.planes[data->selected.obj_index].vector = vec3_normalize(quat_rotate_point(data->scene.planes[data->selected.obj_index].vector, q));
	else if (data->selected.obj_type == OBJ_CYLINDER)
		data->scene.cylinders[data->selected.obj_index].vector = vec3_normalize(quat_rotate_point(data->scene.cylinders[data->selected.obj_index].vector, q));
}

void	mouse_drag(t_mlx_data *data)
{
	t_pixel_coord	mouse;
	t_pixel_coord	diff;

	if (!(data->mouse_input_state & BTN_RIGHT))
		return ;
	mlx_mouse_get_pos(data->mlx, data->mlx_win, &mouse.x, &mouse.y);
	diff.x = mouse.x - data->mouse_last_pos.x;
	diff.y = mouse.y - data->mouse_last_pos.y;
	data->mouse_last_pos.x = mouse.x;
	data->mouse_last_pos.y = mouse.y;
	if (data->selected.obj_type == OBJ_NONE)
		rotate_camera(&data->scene.camera, diff, data->frame_time);
	else
		rotate_obj(data, diff, data->frame_time);
}

void	move_camera(t_camera *camera, long key_state, float frame_time)
{
	t_coordinates	move_dir;
	t_coordinates	world_move_dir;

	if (!key_state)
		return ;
	move_dir.x = ((key_state & KEY_D) > 0) - ((key_state & KEY_A) > 0);
	move_dir.y = ((key_state & KEY_E) > 0) - ((key_state & KEY_Q) > 0);
	move_dir.z = ((key_state & KEY_W) > 0) - ((key_state & KEY_S) > 0);
	if (vec3_norm(move_dir) < 1e-6)
		return ;
	world_move_dir.x = vec3_dot(camera->right, move_dir);
	world_move_dir.y = vec3_dot(camera->up, move_dir);
	world_move_dir.z = vec3_dot(camera->vector, move_dir);
	world_move_dir = vec3_normalize(world_move_dir);
	world_move_dir = vec3_scalar(world_move_dir, 0.01 * frame_time);
	camera->coordinates = vec3_sum(camera->coordinates, world_move_dir);
}

void	move_obj(t_mlx_data *data, long key_state, float frame_time)
{
	t_coordinates	move_dir;

	if (!key_state)
		return ;
	move_dir.x = ((key_state & KEY_D) > 0) - ((key_state & KEY_A) > 0);
	move_dir.y = ((key_state & KEY_E) > 0) - ((key_state & KEY_Q) > 0);
	move_dir.z = ((key_state & KEY_S) > 0) - ((key_state & KEY_W) > 0);
	if (vec3_norm(move_dir) < 1e-6)
		return ;
	move_dir = vec3_scalar(vec3_normalize(move_dir), 0.01 * frame_time);
	if (data->selected.obj_type == OBJ_SPHERE)
		data->scene.spheres[data->selected.obj_index].coordinates = vec3_sum(data->scene.spheres[data->selected.obj_index].coordinates, move_dir);
	else if (data->selected.obj_type == OBJ_PLANE)
		data->scene.planes[data->selected.obj_index].coordinates = vec3_sum(data->scene.planes[data->selected.obj_index].coordinates, move_dir);
	else if (data->selected.obj_type == OBJ_CYLINDER)
		data->scene.cylinders[data->selected.obj_index].coordinates = vec3_sum(data->scene.cylinders[data->selected.obj_index].coordinates, move_dir);
}

void	key_inputs(t_mlx_data *data)
{
	if (data->selected.obj_type == OBJ_NONE)
		move_camera(&data->scene.camera, data->key_input_state, data->frame_time);
	else
		move_obj(data, data->key_input_state, data->frame_time);
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
			data->selected = (t_hit_info){OBJ_NONE, 0, 0, (t_coordinates){0, 0, 0}};
			printf("Rendering scene ...\n");
			render(data);
			gettimeofday(&end, NULL);
			printf("Rendered in: %.3f ms\n", frame_time(start, end));
			data->full_res = REND_DONE;
			return (0);
		}
		check_input_states(data);
		render_low_res(data, 5, 5);
		gettimeofday(&end, NULL);
		data->frame_time = frame_time(start, end);
		image_add_frametime(data);
	}
	else
		return (0);
	return (0);
}

int	handle_move_keys(int keysym, long *key_input_state)
{
	if (keysym == XK_a)
		*key_input_state ^= KEY_A;
	else if (keysym == XK_d)
		*key_input_state ^= KEY_D;
	else if (keysym == XK_w)
		*key_input_state ^= KEY_W;
	else if (keysym == XK_s)
		*key_input_state ^= KEY_S;
	else if (keysym == XK_q)
		*key_input_state ^= KEY_Q;
	else if (keysym == XK_e)
		*key_input_state ^= KEY_E;
	else if (keysym == XK_Control_L)
		*key_input_state ^= KEY_CTRL;
	else
		return (0);
	return (1);
}

int	handle_keypress(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx);
	else if (handle_move_keys(keysym, &data->key_input_state))
		data->full_res = REND_LOW;
	else if (keysym == XK_r && !data->key_input_state && !data->mouse_input_state)
		data->full_res = !(data->full_res);
	return (0);
}

int	handle_keyrelease(int keysym, t_mlx_data *data)
{
	if (handle_move_keys(keysym, &data->key_input_state))
		;
	return (0);
}

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
	return ("INVALID_TYPE");
}

void	select_obj(t_mlx_data *data)
{
	t_hit_info	hit;

	hit = cast_ray(calc_ray(data->scene.camera, data, data->mouse_last_pos), data->scene);
	if (hit.obj_type == OBJ_NONE || (data->selected.obj_type == hit.obj_type && data->selected.obj_index == hit.obj_index))
	{
		printf("De-selected obj: %s #%zu\n", get_obj_name(data->selected.obj_type), data->selected.obj_index);
		data->selected = (t_hit_info){OBJ_NONE, 0, 0, (t_coordinates){0, 0, 0}};
		return ;
	}
	data->selected = hit;
	printf("Selected obj: %s #%zu\n", get_obj_name(data->selected.obj_type), data->selected.obj_index);
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
		select_obj(data);
	}
	else if (button == 3)
	{
		data->mouse_last_pos.x = x;
		data->mouse_last_pos.y = y;
		data->mouse_input_state ^= BTN_RIGHT;
	}
	else if (button == 4)
	{
		data->scene.camera.fov = fmax(data->scene.camera.fov - 1, 30);
	}
	else if (button == 5)
	{
		data->scene.camera.fov = fmin(data->scene.camera.fov + 1, 130);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:09:29 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 23:58:59 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	move_camera(t_camera *camera, long key_state, float speed)
{
	t_coordinates	move_dir;
	t_coordinates	world_move_dir;

	if (!key_state)
		return ;
	move_dir.x = ((key_state & KEY_D) != 0) - ((key_state & KEY_A) != 0);
	move_dir.y = ((key_state & KEY_E) != 0) - ((key_state & KEY_Q) != 0);
	move_dir.z = ((key_state & KEY_W) != 0) - ((key_state & KEY_S) != 0);
	if (vec3_norm(move_dir) < 1e-6)
		return ;
	world_move_dir.x = vec3_dot(camera->right, move_dir);
	world_move_dir.y = vec3_dot(camera->up, move_dir);
	world_move_dir.z = vec3_dot(camera->vector, move_dir);
	world_move_dir = vec3_normalize(world_move_dir);
	world_move_dir = vec3_scalar(world_move_dir, 0.01 * speed);
	camera->coordinates = vec3_sum(camera->coordinates, world_move_dir);
}

void	move_obj(t_mlx_data *data, long key_state, float speed)
{
	t_coordinates	move_dir;

	if (!key_state)
		return ;
	move_dir.x = ((key_state & KEY_D) != 0) - ((key_state & KEY_A) != 0);
	move_dir.y = ((key_state & KEY_E) != 0) - ((key_state & KEY_Q) != 0);
	move_dir.z = ((key_state & KEY_S) != 0) - ((key_state & KEY_W) != 0);
	if (vec3_norm(move_dir) < 1e-6)
		return ;
	move_dir = vec3_scalar(vec3_normalize(move_dir), 0.01 * speed);
	if (data->selected.obj_type == OBJ_SPHERE)
		sphere_move(&data->scene.spheres[data->selected.obj_index], move_dir);
	else if (data->selected.obj_type == OBJ_PLANE)
		plane_move(&data->scene.planes[data->selected.obj_index], move_dir);
	else if (data->selected.obj_type == OBJ_CYLINDER)
		cylinder_move(
			&data->scene.cylinders[data->selected.obj_index], move_dir);
	else if (data->selected.obj_type == OBJ_CONE)
		cone_move(&data->scene.cones[data->selected.obj_index], move_dir);
}

void	rotate_camera(
		t_camera *camera, t_pixel_coord mouse_diff, float speed)
{
	t_quat	q_yaw;
	t_quat	q_pitch;
	float	yaw_diff;
	float	pitch_diff;

	yaw_diff = mouse_diff.x * DEG2RAD * 2 * speed;
	pitch_diff = mouse_diff.y * DEG2RAD * 2 * speed;
	if (camera->pitch + pitch_diff <= -(90 * DEG2RAD)
		|| 90 * DEG2RAD <= camera->pitch + pitch_diff)
		pitch_diff = 0;
	camera->yaw -= yaw_diff;
	camera->pitch -= pitch_diff;
	q_yaw = quat_axis_rot((t_coordinates){0, 1, 0}, -camera->yaw);
	q_pitch = quat_axis_rot((t_coordinates){1, 0, 0}, -camera->pitch);
	camera->rotation = quat_mult(q_yaw, q_pitch);
	camera->vector = vec3_normalize(
			quat_rotate_point((t_coordinates){0, 0, -1}, camera->rotation));
	camera->right = vec3_normalize(
			quat_rotate_point((t_coordinates){1, 0, 0}, camera->rotation));
	camera->up = vec3_normalize(
			quat_rotate_point((t_coordinates){0, 1, 0}, camera->rotation));
}

void	rotate_obj(t_mlx_data *data, t_pixel_coord mouse_diff, float speed)
{
	t_quat			q_yaw;
	t_quat			q_pitch;
	t_quat			q_roll;
	t_quat			q;
	t_coordinates	rot_diffs;

	if (data->selected.obj_type == OBJ_SPHERE)
		return ;
	rot_diffs.x = 0;
	rot_diffs.y = -mouse_diff.y * DEG2RAD * 2 * speed;
	rot_diffs.z = 0;
	if (data->key_input_state & KEY_ALT)
		rot_diffs.z = mouse_diff.x * DEG2RAD * 2 * speed;
	else
		rot_diffs.x = mouse_diff.x * DEG2RAD * 2 * speed;
	q_yaw = quat_axis_rot((t_coordinates){0, 1, 0}, rot_diffs.x);
	q_pitch = quat_axis_rot((t_coordinates){1, 0, 0}, rot_diffs.y);
	q_roll = quat_axis_rot((t_coordinates){0, 0, 1}, rot_diffs.z);
	q = quat_mult(quat_mult(q_yaw, q_pitch), q_roll);
	if (data->selected.obj_type == OBJ_PLANE)
		plane_rot(&data->scene.planes[data->selected.obj_index], q);
	else if (data->selected.obj_type == OBJ_CYLINDER)
		cylinder_rot(&data->scene.cylinders[data->selected.obj_index], q);
	else if (data->selected.obj_type == OBJ_CONE)
		cone_rot(&data->scene.cones[data->selected.obj_index], q);
}

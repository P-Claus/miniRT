/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:17:14 by efret             #+#    #+#             */
/*   Updated: 2024/09/20 13:17:40 by efret            ###   ########.fr       */
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
	t_hit_info	hit;

	hit = cast_ray(calc_ray(
				data->scene.camera, data, data->mouse_last_pos), data->scene);
	if (hit.obj_type == OBJ_NONE
		|| (data->selected.obj_type == hit.obj_type
			&& data->selected.obj_index == hit.obj_index))
	{
		printf("De-selected obj: %s #%zu\n",
			get_obj_name(data->selected.obj_type), data->selected.obj_index);
		data->selected = (t_hit_info){OBJ_NONE, 0, 0, {0, 0, 0}};
		return ;
	}
	data->selected = hit;
	printf("Selected obj: %s #%zu\n",
		get_obj_name(data->selected.obj_type), data->selected.obj_index);
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
		data->scene.camera.fov = fmax(data->scene.camera.fov - 1, 5);
	}
	else if (button == 5)
	{
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:27:30 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 17:27:35 by efret            ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:30:21 by efret             #+#    #+#             */
/*   Updated: 2024/10/04 14:47:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_btn_select_plane(t_ui_menu_elem *self, t_mlx_data *data)
{
	int	i;

	i = 0;
	while (i < data->scene.nb_of_planes)
	{
		if (&data->scene.planes[i] == self->data.data)
			break ;
		i++;
	}
	data->selected = (t_hit_info){OBJ_PLANE, i, 0, {0, 0, 0}};
	set_menu_page(data);
	return (0);
}

int	menu_btn_add_plane(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_plane	*planes;
	int		i;

	(void)self;
	planes = malloc(sizeof(t_plane) * (data->scene.nb_of_planes + 1));
	if (!planes)
		return (1);
	i = 0;
	while (i < data->scene.nb_of_planes)
	{
		planes[i] = data->scene.planes[i];
		i++;
	}
	planes[data->scene.nb_of_planes++] = (t_plane){{0, 0, 0},
	{0, 1, 0}, {1, 1, 1}};
	free(data->scene.planes);
	data->scene.planes = planes;
	data->selected = (t_hit_info){OBJ_PLANE, i, 0, {0, 0, 0}};
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	set_menu_page(data);
	return (0);
}

static int	menu_btn_del_plane_2(t_plane **planes, t_plane *del_plane,
		t_plane *scene_planes, int nb_of_scene_planes)
{
	int	i;

	if (nb_of_scene_planes == 1)
		return (*planes = NULL, 0);
	*planes = malloc(sizeof(t_plane) * (nb_of_scene_planes - 1));
	if (!*planes)
		return (1);
	i = 0;
	while (i < nb_of_scene_planes && &scene_planes[i] != del_plane)
	{
		(*planes)[i] = scene_planes[i];
		i++;
	}
	i++;
	while (i < nb_of_scene_planes)
	{
		(*planes)[i - 1] = scene_planes[i];
		i++;
	}
	return (0);
}

int	menu_btn_del_plane(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_plane	*planes;

	if (data->scene.nb_of_planes < 1)
		return (1);
	if (menu_btn_del_plane_2(&planes, self->data.data,
			data->scene.planes, data->scene.nb_of_planes))
		return (1);
	if (data->selected.obj_type == OBJ_PLANE
		&& &data->scene.planes[data->selected.obj_index] == self->data.data)
	{
		data->selected = (t_hit_info){OBJ_NONE, 0, 0, {0, 0, 0}};
		set_menu_page(data);
	}
	free(data->scene.planes);
	data->scene.planes = planes;
	data->scene.nb_of_planes--;
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	return (0);
}

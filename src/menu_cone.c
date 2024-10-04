/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:51:00 by efret             #+#    #+#             */
/*   Updated: 2024/10/04 14:47:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_btn_select_cone(t_ui_menu_elem *self, t_mlx_data *data)
{
	int	i;

	i = 0;
	while (i < data->scene.nb_of_cones)
	{
		if (&data->scene.cones[i] == self->data.data)
			break ;
		i++;
	}
	data->selected = (t_hit_info){OBJ_CONE, i, 0, {0, 0, 0}};
	set_menu_page(data);
	return (0);
}

int	menu_btn_add_cone(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_cone	*cones;
	int		i;

	(void)self;
	cones = malloc(sizeof(t_cone) * (data->scene.nb_of_cones + 1));
	if (!cones)
		return (1);
	i = 0;
	while (i < data->scene.nb_of_cones)
	{
		cones[i] = data->scene.cones[i];
		i++;
	}
	cones[data->scene.nb_of_cones++] = (t_cone){{0, 0, 0},
	{0, 1, 0}, 2, 1, {1, 1, 1}};
	free(data->scene.cones);
	data->scene.cones = cones;
	data->selected = (t_hit_info){OBJ_CONE, i, 0, {0, 0, 0}};
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	set_menu_page(data);
	return (0);
}

static int	menu_btn_del_cone_2(t_cone **cones, t_cone *del_cone,
		t_cone *scene_cones, int nb_of_scene_cones)
{
	int	i;

	if (nb_of_scene_cones == 1)
		return (*cones = NULL, 0);
	*cones = malloc(sizeof(t_cone) * (nb_of_scene_cones - 1));
	if (!*cones)
		return (1);
	i = 0;
	while (i < nb_of_scene_cones && &scene_cones[i] != del_cone)
	{
		(*cones)[i] = scene_cones[i];
		i++;
	}
	i++;
	while (i < nb_of_scene_cones)
	{
		(*cones)[i - 1] = scene_cones[i];
		i++;
	}
	return (0);
}

int	menu_btn_del_cone(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_cone	*cones;

	if (data->scene.nb_of_cones < 1)
		return (1);
	if (menu_btn_del_cone_2(&cones, self->data.data,
			data->scene.cones, data->scene.nb_of_cones))
		return (1);
	if (data->selected.obj_type == OBJ_CONE
		&& &data->scene.cones[data->selected.obj_index] == self->data.data)
	{
		data->selected = (t_hit_info){OBJ_NONE, 0, 0, {0, 0, 0}};
		set_menu_page(data);
	}
	free(data->scene.cones);
	data->scene.cones = cones;
	data->scene.nb_of_cones--;
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	return (0);
}

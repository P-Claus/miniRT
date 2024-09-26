/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:25:02 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 16:48:06 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_btn_select_cylinder(t_ui_menu_elem *self, t_mlx_data *data)
{
	int	i;

	i = 0;
	while (i < data->scene.nb_of_cylinders)
	{
		if (&data->scene.cylinders[i] == self->data.data)
			break ;
		i++;
	}
	data->selected = (t_hit_info){OBJ_CYLINDER, i, 0, {0, 0, 0}};
	set_menu_page(data);
	return (0);
}

int	menu_btn_add_cylinder(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_cylinder	*cylinders;
	int			i;

	(void)self;
	cylinders = malloc(sizeof(t_cylinder) * (data->scene.nb_of_cylinders + 1));
	if (!cylinders)
		return (1);
	i = 0;
	while (i < data->scene.nb_of_cylinders)
	{
		cylinders[i] = data->scene.cylinders[i];
		i++;
	}
	cylinders[data->scene.nb_of_cylinders++] = 
		(t_cylinder){{0, 0, 0}, {0, 1, 0}, 2, 1, {1, 1, 1}};
	free(data->scene.cylinders);
	data->scene.cylinders = cylinders;
	data->selected = (t_hit_info){OBJ_CYLINDER, i, 0, {0, 0, 0}};
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	set_menu_page(data);
	return (0);
}

static int	menu_btn_del_cylinder_2(
		t_cylinder **cylinders, t_cylinder *del_cylinder,
		t_cylinder *scene_cylinders, int nb_of_scene_cylinders)
{
	int	i;

	if (nb_of_scene_cylinders == 1)
		return (*cylinders = NULL, 0);
	*cylinders = malloc(sizeof(t_cylinder) * (nb_of_scene_cylinders - 1));
	if (!*cylinders)
		return (1);
	i = 0;
	while (i < nb_of_scene_cylinders && &scene_cylinders[i] != del_cylinder)
	{
		(*cylinders)[i] = scene_cylinders[i];
		i++;
	}
	i++;
	while (i < nb_of_scene_cylinders)
	{
		(*cylinders)[i - 1] = scene_cylinders[i];
		i++;
	}
	return (0);
}

int	menu_btn_del_cylinder(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_cylinder	*cylinders;

	if (data->scene.nb_of_cylinders < 1)
		return (1);
	if (menu_btn_del_cylinder_2(&cylinders, self->data.data,
			data->scene.cylinders, data->scene.nb_of_cylinders))
		return (1);
	if (data->selected.obj_type == OBJ_CYLINDER
		&& &data->scene.cylinders[data->selected.obj_index] == self->data.data)
	{
		data->selected = (t_hit_info){OBJ_NONE, 0, 0, {0, 0, 0}};
		set_menu_page(data);
	}
	free(data->scene.cylinders);
	data->scene.cylinders = cylinders;
	data->scene.nb_of_cylinders--;
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	return (0);
}

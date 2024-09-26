/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:07:17 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 16:47:43 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_btn_select_sphere(t_ui_menu_elem *self, t_mlx_data *data)
{
	int	i;

	i = 0;
	while (i < data->scene.nb_of_spheres)
	{
		if (&data->scene.spheres[i] == self->data.data)
			break ;
		i++;
	}
	data->selected = (t_hit_info){OBJ_SPHERE, i, 0, {0, 0, 0}};
	set_menu_page(data);
	return (0);
}

int	menu_btn_add_sphere(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_sphere	*spheres;
	int			i;

	(void)self;
	spheres = malloc(sizeof(t_sphere) * (data->scene.nb_of_spheres + 1));
	if (!spheres)
		return (1);
	i = 0;
	while (i < data->scene.nb_of_spheres)
	{
		spheres[i] = data->scene.spheres[i];
		i++;
	}
	spheres[data->scene.nb_of_spheres++] = (t_sphere){{0, 0, 0}, 2, {1, 1, 1}};
	free(data->scene.spheres);
	data->scene.spheres = spheres;
	data->selected = (t_hit_info){OBJ_SPHERE, i, 0, {0, 0, 0}};
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	set_menu_page(data);
	return (0);
}

static int	menu_btn_del_sphere_2(t_sphere **spheres, t_sphere *del_sphere,
		t_sphere *scene_spheres, int nb_of_scene_spheres)
{
	int	i;

	if (nb_of_scene_spheres == 1)
		return (*spheres = NULL, 0);
	*spheres = malloc(sizeof(t_sphere) * (nb_of_scene_spheres - 1));
	if (!*spheres)
		return (1);
	i = 0;
	while (i < nb_of_scene_spheres && &scene_spheres[i] != del_sphere)
	{
		(*spheres)[i] = scene_spheres[i];
		i++;
	}
	i++;
	while (i < nb_of_scene_spheres)
	{
		(*spheres)[i - 1] = scene_spheres[i];
		i++;
	}
	return (0);
}

int	menu_btn_del_sphere(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_sphere	*spheres;

	if (data->scene.nb_of_spheres < 1)
		return (1);
	if (menu_btn_del_sphere_2(&spheres, self->data.data,
			data->scene.spheres, data->scene.nb_of_spheres))
		return (1);
	if (data->selected.obj_type == OBJ_SPHERE
		&& &data->scene.spheres[data->selected.obj_index] == self->data.data)
	{
		data->selected = (t_hit_info){OBJ_NONE, 0, 0, {0, 0, 0}};
		set_menu_page(data);
	}
	free(data->scene.spheres);
	data->scene.spheres = spheres;
	data->scene.nb_of_spheres--;
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	return (0);
}

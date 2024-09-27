/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_page_select.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:24:13 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 16:16:55 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	select_page_add_spheres(t_mlx_data *data, t_ui_menu_page *page)
{
	int	i;

	if (!data->scene.nb_of_spheres)
		return ;
	add_elem_space(page);
	add_elem_text(page, "Spheres");
	i = 0;
	while (i < data->scene.nb_of_spheres)
		add_elem_btn(page, "sphere",
			(t_elem_data){UI_DATA_SPHERE, &data->scene.spheres[i++]},
			menu_btn_select_sphere);
}

static void	select_page_add_cylinders(t_mlx_data *data, t_ui_menu_page *page)
{
	int	i;

	if (!data->scene.nb_of_cylinders)
		return ;
	add_elem_space(page);
	add_elem_text(page, "Cylinders");
	i = 0;
	while (i < data->scene.nb_of_cylinders)
		add_elem_btn(page, "cylinder",
			(t_elem_data){UI_DATA_CYLINDER, &data->scene.cylinders[i++]},
			menu_btn_select_cylinder);
}

static void	select_page_add_planes(t_mlx_data *data, t_ui_menu_page *page)
{
	int	i;

	if (!data->scene.nb_of_planes)
		return ;
	add_elem_space(page);
	add_elem_text(page, "Planes");
	i = 0;
	while (i < data->scene.nb_of_planes)
		add_elem_btn(page, "plane",
			(t_elem_data){UI_DATA_PLANE, &data->scene.planes[i++]},
			menu_btn_select_plane);
}

static void	select_page_add_cones(t_mlx_data *data, t_ui_menu_page *page)
{
	int	i;

	if (!data->scene.nb_of_cones)
		return ;
	add_elem_space(page);
	add_elem_text(page, "cones");
	i = 0;
	while (i < data->scene.nb_of_cones)
		add_elem_btn(page, "cone",
			(t_elem_data){UI_DATA_CONE, &data->scene.cones[i++]},
			menu_btn_select_cone);
}

int	menu_set_select_page(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page	*page;

	page = &data->menu.pages[UI_MENU_PAGE_SELECT];
	if (!page)
		return (1);
	if (page->elements)
		free_elements(&page->elements);
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "SELECT";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	page->scroll = 0;
	add_elem_btn(page, "Home page", (t_elem_data){0, NULL}, menu_btn_home_page);
	select_page_add_spheres(data, page);
	select_page_add_cylinders(data, page);
	select_page_add_planes(data, page);
	select_page_add_cones(data, page);
	return (0);
}

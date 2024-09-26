/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_page_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:25:48 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 00:08:37 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_init_page_cylinder(
		t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "___";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	page->scroll = 0;
	add_elem_btn(page, "Home page", (t_elem_data){0, NULL}, menu_btn_home_page);
	return (0);
}

static void	page_add_cylinder_attributes(t_ui_menu_page *page, t_cylinder *obj)
{
	add_elem_space(page);
	add_elem_text(page, "Attributes");
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"height:",
	{UI_DATA_FLOAT, &obj->height}, {0., INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"diameter:",
	{UI_DATA_FLOAT, &obj->diameter},
	{0., INFINITY, 1.}, menu_nbox_apply_float});
}

void	set_menu_cylinder_page(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page	*page;
	t_cylinder		*obj;

	obj = &data->scene.cylinders[data->selected.obj_index];
	data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_OBJ_CYLINDER];
	page = data->menu.curr_page;
	free_elements(&page->elements);
	page->n_elems = 0;
	page->title = "CYLINDER";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	page->scroll = 0;
	add_elem_btn(page, "Home page", (t_elem_data){0, NULL}, menu_btn_home_page);
	add_elem_space(page);
	add_elem_text(page, "cylinder");
	add_elem_btn(page, "delete",
		(t_elem_data){UI_DATA_CYLINDER, obj}, menu_btn_del_cylinder);
	page_add_pos_block(page, &obj->coordinates);
	page_add_dir_block(page, &obj->vector, 0);
	page_add_rgb_block(page, &obj->rgb);
	page_add_cylinder_attributes(page, obj);
}

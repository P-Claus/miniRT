/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_page_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:25:59 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 18:31:48 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_init_page_plane(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
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

void	set_menu_plane_page(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page	*page;
	t_plane			*obj;

	obj = &data->scene.planes[data->selected.obj_index];
	data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_OBJ_PLANE];
	page = data->menu.curr_page;
	free_elements(&page->elements);
	page->n_elems = 0;
	page->title = "PLANE";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	page->scroll = 0;
	add_elem_btn(page, "Home page", (t_elem_data){0, NULL}, menu_btn_home_page);
	add_elem_space(page);
	add_elem_text(page, "plane");
	add_elem_btn(page, "delete", (t_elem_data){UI_DATA_PLANE, obj}, menu_btn_del_plane);
	add_elem_space(page);
	add_elem_btn(page, "Reset position", (t_elem_data){UI_DATA_COORDS, &obj->coordinates}, menu_btn_reset_pos);
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos x:", {UI_DATA_FLOAT, &obj->coordinates.x}, {-INFINITY, INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos y:", {UI_DATA_FLOAT, &obj->coordinates.y}, {-INFINITY, INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos z:", {UI_DATA_FLOAT, &obj->coordinates.z}, {-INFINITY, INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_space(page);
	add_elem_btn(page, "Reset direction", (t_elem_data){UI_DATA_COORDS, &obj->vector}, menu_btn_reset_dir);
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"dir x:", {UI_DATA_FLOAT, &obj->vector.x}, {-INFINITY, INFINITY, 1.}, NULL});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"dir y:", {UI_DATA_FLOAT, &obj->vector.y}, {-INFINITY, INFINITY, 1.}, NULL});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"dir z:", {UI_DATA_FLOAT, &obj->vector.z}, {-INFINITY, INFINITY, 1.}, NULL});
	add_elem_space(page);
	add_elem_text(page, "Color");
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"red:", {UI_DATA_FLOAT, &obj->rgb.r}, {0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"green:", {UI_DATA_FLOAT, &obj->rgb.g}, {0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"blue:", {UI_DATA_FLOAT, &obj->rgb.b}, {0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_space(page);
	add_elem_text(page, "Attributes");
}

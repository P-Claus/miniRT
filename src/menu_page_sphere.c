/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_page_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:25:37 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 18:29:58 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_init_page_sphere(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
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

void	set_menu_sphere_page(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page	*page;
	t_sphere		*obj;

	obj = &data->scene.spheres[data->selected.obj_index];
	menu->curr_page = &data->menu.pages[UI_MENU_PAGE_OBJ_SPHERE];
	page = menu->curr_page;
	free_elements(&page->elements);
	page->n_elems = 0;
	page->title = "SPHERE";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	page->scroll = 0;
	add_elem_btn(page, "Home page", (t_elem_data){0, NULL}, menu_btn_home_page);
	add_elem_space(page);
	add_elem_text(page, "sphere");
	add_elem_btn(page, "delete", (t_elem_data){UI_DATA_SPHERE, obj}, menu_btn_del_sphere);
	add_elem_space(page);
	add_elem_btn(page, "Reset position", (t_elem_data){UI_DATA_COORDS, &obj->coordinates}, menu_btn_reset_pos);
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos x:", {UI_DATA_FLOAT, &obj->coordinates.x}, {-INFINITY, INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos y:", {UI_DATA_FLOAT, &obj->coordinates.y}, {-INFINITY, INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos z:", {UI_DATA_FLOAT, &obj->coordinates.z}, {-INFINITY, INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_space(page);
	add_elem_text(page, "Color");
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"red:", {UI_DATA_FLOAT, &obj->rgb.r}, {0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"green:", {UI_DATA_FLOAT, &obj->rgb.g}, {0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"blue:", {UI_DATA_FLOAT, &obj->rgb.b}, {0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_space(page);
	add_elem_text(page, "Attributes");
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"diameter:", {UI_DATA_FLOAT, &obj->diameter}, {0., INFINITY, 1.}, menu_nbox_apply_float});
}

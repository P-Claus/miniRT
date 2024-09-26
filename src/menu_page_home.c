/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_page_home.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:22:58 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 18:23:23 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_init_page_home(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "HOME";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	page->scroll = 0;
	add_elem_btn(page, "Select obj page", (t_elem_data){0, NULL}, menu_btn_select_page);
	add_elem_btn(page, "Add obj page", (t_elem_data){0, NULL}, menu_btn_add_page);
	add_elem_btn(page, "Del obj page", (t_elem_data){0, NULL}, menu_btn_del_page);
	add_elem_space(page);
	add_elem_text(page, "Camera");
	add_elem_btn(page, "Reset camera", (t_elem_data){0, NULL}, menu_btn_reset_cam);
	add_elem_space(page);
	add_elem_btn(page, "Reset position", (t_elem_data){UI_DATA_COORDS, &data->scene.camera.coordinates}, menu_btn_reset_cam_pos);
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos x:", {UI_DATA_FLOAT, &data->scene.camera.coordinates.x}, {-INFINITY, INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos y:", {UI_DATA_FLOAT, &data->scene.camera.coordinates.y}, {-INFINITY, INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos z:", {UI_DATA_FLOAT, &data->scene.camera.coordinates.z}, {-INFINITY, INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_space(page);
	add_elem_btn(page, "Reset direction", (t_elem_data){UI_DATA_COORDS, &data->scene.camera.vector}, menu_btn_reset_cam_dir);
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"dir x:", {UI_DATA_FLOAT, &data->scene.camera.vector.x}, {-INFINITY, INFINITY, 1.}, NULL});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"dir y:", {UI_DATA_FLOAT, &data->scene.camera.vector.y}, {-INFINITY, INFINITY, 1.}, NULL});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"dir z:", {UI_DATA_FLOAT, &data->scene.camera.vector.z}, {-INFINITY, INFINITY, 1.}, NULL});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pitch:", {UI_DATA_FLOAT, &data->scene.camera.pitch}, {-INFINITY, INFINITY, 1 * DEG2RAD}, menu_nbox_apply_pitch});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"fov:", {UI_DATA_INT, &data->scene.camera.fov}, {5, 175, 1}, menu_nbox_apply_fov});
	add_elem_space(page);
	add_elem_text(page, "Ambient");
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"intensity:", {UI_DATA_FLOAT, &data->scene.a_lighting.ambient_lighting}, {0, 1., 0.01}, menu_nbox_apply_perc});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"red:", {UI_DATA_FLOAT, &data->scene.a_lighting.rgb.r}, {0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"green:", {UI_DATA_FLOAT, &data->scene.a_lighting.rgb.g}, {0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"blue:", {UI_DATA_FLOAT, &data->scene.a_lighting.rgb.b}, {0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_space(page);
	add_elem_text(page, "Point Light");
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos x:", {UI_DATA_FLOAT, &data->scene.light.coordinates.x}, {-INFINITY, INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos y:", {UI_DATA_FLOAT, &data->scene.light.coordinates.y}, {-INFINITY, INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos z:", {UI_DATA_FLOAT, &data->scene.light.coordinates.z}, {-INFINITY, INFINITY, 1.}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"intensity:", {UI_DATA_FLOAT, &data->scene.light.brightness}, {0, 1., 0.01}, menu_nbox_apply_perc});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"red:", {UI_DATA_FLOAT, &data->scene.light.rgb.r}, {0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"green:", {UI_DATA_FLOAT, &data->scene.light.rgb.g}, {0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"blue:", {UI_DATA_FLOAT, &data->scene.light.rgb.b}, {0, 1., 1. / 255}, menu_nbox_apply_color_float});
	return (0);
}

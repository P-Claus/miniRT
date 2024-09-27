/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_page_home.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:22:58 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 15:41:29 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	menu_init_page_home_cam(t_mlx_data *data, t_ui_menu_page *page)
{
	add_elem_space(page);
	add_elem_text(page, "Camera:");
	add_elem_btn(page, "Reset camera",
		(t_elem_data){0, NULL}, menu_btn_reset_cam);
	page_add_pos_block(page, &data->scene.camera.coordinates);
	page_add_dir_block(page, &data->scene.camera.vector, true);
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"yaw:",
	{UI_DATA_FLOAT, &data->scene.camera.yaw},
	{-INFINITY, INFINITY, 1 * DEG2RAD}, menu_nbox_apply_yaw});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pitch:",
	{UI_DATA_FLOAT, &data->scene.camera.pitch},
	{-INFINITY, INFINITY, 1 * DEG2RAD}, menu_nbox_apply_pitch});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"fov:",
	{UI_DATA_INT, &data->scene.camera.fov},
	{5, 175, 1}, menu_nbox_apply_fov});
}

static void	menu_init_page_home_light(t_mlx_data *data, t_ui_menu_page *page)
{
	add_elem_space(page);
	add_elem_text(page, "Ambient:");
	page_add_rgb_block(page, &data->scene.a_lighting.rgb);
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"intensity:",
	{UI_DATA_FLOAT, &data->scene.a_lighting.ambient_lighting},
	{0, 1., 0.01}, menu_nbox_apply_perc});
	add_elem_space(page);
	add_elem_text(page, "Point Light:");
	page_add_pos_block(page, &data->scene.light.coordinates);
	page_add_rgb_block(page, &data->scene.light.rgb);
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"intensity:",
	{UI_DATA_FLOAT, &data->scene.light.brightness},
	{0, 1., 0.01}, menu_nbox_apply_perc});
}

int	menu_init_page_home(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "HOME";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	page->scroll = 0;
	add_elem_btn(page, "Select obj page",
		(t_elem_data){0, NULL}, menu_btn_select_page);
	add_elem_btn(page, "Add obj page",
		(t_elem_data){0, NULL}, menu_btn_add_page);
	add_elem_btn(page, "Del obj page",
		(t_elem_data){0, NULL}, menu_btn_del_page);
	add_elem_space(page);
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"speed:",
	{UI_DATA_FLOAT, &data->speed},
	{SPEED_MIN, SPEED_MAX, SPEED_STEP}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"res lvl:",
	{UI_DATA_INT, &data->low_res_lev},
	{RES_MIN, RES_MAX, RES_STEP}, menu_nbox_apply_int});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"gamma corr:",
	{UI_DATA_INT, &data->gamma_type},
	{GAMMA_CORRECT, GAMMA_NONE, 1}, menu_nbox_apply_int});
	menu_init_page_home_cam(data, page);
	menu_init_page_home_light(data, page);
	return (0);
}

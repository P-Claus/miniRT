/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_page_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:11:04 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 16:14:09 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	page_add_rgb_block(t_ui_menu_page *page, t_rgb *rgb)
{
	add_elem_space(page);
	add_elem_text(page, "Color");
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"red:",
	{UI_DATA_FLOAT, &rgb->r},
	{0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"green:",
	{UI_DATA_FLOAT, &rgb->g},
	{0, 1., 1. / 255}, menu_nbox_apply_color_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"blue:",
	{UI_DATA_FLOAT, &rgb->b},
	{0, 1., 1. / 255}, menu_nbox_apply_color_float});
}

void	page_add_pos_block(t_ui_menu_page *page, t_coordinates *coords)
{
	add_elem_space(page);
	add_elem_text(page, "Position");
	add_elem_btn(page, "Reset position",
		(t_elem_data){UI_DATA_COORDS, coords}, menu_btn_reset_pos);
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos x:", 
	{UI_DATA_FLOAT, &coords->x},
	{-INFINITY, INFINITY, COORD_STEP}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos y:", 
	{UI_DATA_FLOAT, &coords->y},
	{-INFINITY, INFINITY, COORD_STEP}, menu_nbox_apply_float});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"pos z:", 
	{UI_DATA_FLOAT, &coords->z},
	{-INFINITY, INFINITY, COORD_STEP}, menu_nbox_apply_float});
}

void	page_add_dir_block(t_ui_menu_page *page, t_coordinates *dir, bool cam)
{
	add_elem_space(page);
	add_elem_text(page, "Direction");
	if (cam)
		add_elem_btn(page, "Reset direction",
			(t_elem_data){UI_DATA_COORDS, dir},
			menu_btn_reset_cam_dir);
	else
		add_elem_btn(page, "Reset direction",
			(t_elem_data){UI_DATA_COORDS, dir},
			menu_btn_reset_dir);
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"dir x:", {UI_DATA_FLOAT, &dir->x},
	{-INFINITY, INFINITY, 0.01}, NULL});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"dir y:", {UI_DATA_FLOAT, &dir->y},
	{-INFINITY, INFINITY, 0.01}, NULL});
	add_elem_nbox_bs(page, (t_nbox_norm_bs){"dir z:", {UI_DATA_FLOAT, &dir->z},
	{-INFINITY, INFINITY, 0.01}, NULL});
}

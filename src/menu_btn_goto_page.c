/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_btn_goto_page.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:28:38 by efret             #+#    #+#             */
/*   Updated: 2024/09/25 17:30:58 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_btn_home_page(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_HOME];
	data->selected.obj_type = OBJ_NONE;
	return (0);
}

int	menu_btn_add_page(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_ADD];
	data->selected.obj_type = OBJ_NONE;
	return (0);
}

int	menu_btn_del_page(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_DEL];
	data->selected.obj_type = OBJ_NONE;
	return (0);
}

int	menu_btn_select_page(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_SELECT];
	data->selected.obj_type = OBJ_NONE;
	return (0);
}

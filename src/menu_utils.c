/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:51:45 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 18:20:12 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_init_pages(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page	*pages;

	errno = 0;
	pages = malloc((UI_MENU_PAGE_END + 1) * sizeof(t_ui_menu_page));
	if (!pages)
		return (1);
	menu->pages = pages;
	menu_init_page_home(data, menu, &pages[UI_MENU_PAGE_HOME]);
	menu_init_page_select(data, menu, &pages[UI_MENU_PAGE_SELECT]);
	menu_init_page_add(data, menu, &pages[UI_MENU_PAGE_ADD]);
	menu_init_page_del(data, menu, &pages[UI_MENU_PAGE_DEL]);
	menu_init_page_sphere(data, menu, &pages[UI_MENU_PAGE_OBJ_SPHERE]);
	menu_init_page_cylinder(data, menu, &pages[UI_MENU_PAGE_OBJ_CYLINDER]);
	menu_init_page_plane(data, menu, &pages[UI_MENU_PAGE_OBJ_PLANE]);
	menu_init_page_cone(data, menu, &pages[UI_MENU_PAGE_OBJ_CONE]);
	menu_init_page_end(data, menu, &pages[UI_MENU_PAGE_END]);
	if (errno)
		return (1);
	return (0);
}

void	set_menu_page(t_mlx_data *data)
{
	if (data->menu.curr_input_elem)
	{
		if (data->menu.curr_input_str)
		{
			free(data->menu.curr_input_str);
			data->menu.curr_input_str = NULL;
		}
		data->menu.curr_input_elem = NULL;
	}
	if (data->selected.obj_type == OBJ_NONE)
		data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_HOME];
	else if (data->selected.obj_type == OBJ_SPHERE)
		set_menu_sphere_page(data, &data->menu);
	else if (data->selected.obj_type == OBJ_CYLINDER)
		set_menu_cylinder_page(data, &data->menu);
	else if (data->selected.obj_type == OBJ_PLANE)
		set_menu_plane_page(data, &data->menu);
	else if (data->selected.obj_type == OBJ_CONE)
		set_menu_cone_page(data, &data->menu);
	if (data->menu.show)
		data->menu.show = MENU_SHOW;
}

/* Drawing the menu and pages */

void	menu_draw_page(t_mlx_data *data, t_ui_menu_page page)
{
	t_ui_menu_elem	*elem;
	t_pixel_coord	pos;

	mlx_string_put(data->mlx, data->mlx_win,
		page.pos.x + page.size.x / 2 - ft_strlen(page.title) * 4,
		page.pos.y + 15, 0x00DDDDDD, page.title);
	pos = page.pos;
	pos.y += ELEM_OFFSET + ELEM_HEIGHT + page.scroll;
	elem = page.elements;
	while (elem && pos.y <= page.pos.y + page.size.y - 20)
	{
		if (pos.y - ELEM_HEIGHT >= page.pos.y + ELEM_OFFSET)
			elem->draw(elem, pos, data);
		pos.y += ELEM_HEIGHT;
		elem = elem->next;
	}
	if (page.scroll < 0)
		mlx_string_put(data->mlx, data->mlx_win,
			page.pos.x + page.size.x / 2 - 4,
			page.pos.y + ELEM_OFFSET, 0x00DDDDDD, "^");
	if (elem)
		mlx_string_put(data->mlx, data->mlx_win,
			page.pos.x + page.size.x / 2 - 4,
			page.pos.y + page.size.y,
			0x00DDDDDD, "v");
}

int	menu_draw(t_mlx_data *data, t_ui_menu *menu)
{
	menu->show = MENU_DRAWN;
	mlx_put_image_to_window(data->mlx, data->mlx_win, menu->bg.img,
		menu->pos.x, menu->pos.y);
	mlx_put_image_to_window(data->mlx, data->mlx_win, menu->page_bg.img,
		menu->page_pos.x, menu->page_pos.y);
	mlx_string_put(data->mlx, data->mlx_win,
		menu->pos.x + menu->size.x / 2 - 4 * 4,
		menu->pos.y + 10 + 5, 0x00CCCCCC, "MENU");
	menu_draw_page(data, *menu->curr_page);
	return (0);
}

int	box_is_clicked(t_pixel_coord pos, t_pixel_coord size, t_pixel_coord mouse)
{
	mouse.x -= pos.x;
	mouse.y -= pos.y;
	if (mouse.x < 0 || mouse.x > size.x || mouse.y < 0 || mouse.y > size.y)
		return (0);
	return (1);
}

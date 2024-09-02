/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:51:45 by efret             #+#    #+#             */
/*   Updated: 2024/09/02 22:45:20 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_draw_space(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	(void)data;
	return (0);
}

int	menu_draw_text(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	(void)data;
	t_pixel_coord	pos = {self->page->menu->pos.x + self->page->menu_pos.x + self->page_pos.x, self->page->menu->pos.y + self->page->menu_pos.y + self->page_pos.y};
	mlx_string_put(data->mlx, data->mlx_win, pos.x, pos.y, 0x00FFFFFF, self->str);
	return (0);
}

int	menu_draw_btn(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	(void)data;
	t_pixel_coord	pos = {self->page->menu->pos.x + self->page->menu_pos.x + self->page_pos.x, self->page->menu->pos.y + self->page->menu_pos.y + self->page_pos.y};
	mlx_string_put(data->mlx, data->mlx_win, pos.x, pos.y, 0x00FFFFFF, self->str);
	return (0);
}

int	menu_draw_nbox(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	(void)data;
	t_pixel_coord	pos = {self->page->menu->pos.x + self->page->menu_pos.x + self->page_pos.x, self->page->menu->pos.y + self->page->menu_pos.y + self->page_pos.y};
	mlx_string_put(data->mlx, data->mlx_win, pos.x, pos.y, 0x00FFFFFF, self->str);
	return (0);
}

int	menu_init_page_home(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	t_ui_menu_elem	*elems;

	elems = malloc(3 * sizeof(t_ui_menu_elem));
	if (!elems)
		return (page->title = NULL, 1);
	page->title = "HOME";
	page->menu_pos = (t_pixel_coord){60, 50};
	page->menu = menu;
	page->size = (t_pixel_coord){200, SCREEN_HEIGHT - 200};
	page->scroll = 0;
	elems[0] = (t_ui_menu_elem){UI_MENU_BTN, "Button1", page, 0, (t_pixel_coord){0, 10 * 0}, menu_draw_btn, NULL};
	elems[1] = (t_ui_menu_elem){UI_MENU_BTN, "Button2", page, 1, (t_pixel_coord){0, 10 * 1}, menu_draw_btn, NULL};
	elems[2] = (t_ui_menu_elem){UI_MENU_END, "END", page, 2, (t_pixel_coord){0, 0}, NULL, NULL};
	page->elements = elems;
	return (0);
}

int	menu_init_page_end(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	(void)menu;
	*page = (t_ui_menu_page){NULL, NULL, NULL, (t_pixel_coord){0, 0}, (t_pixel_coord){0, 0}, 0};
	return (0);
}

int	menu_init_pages(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page	*pages;

	pages = malloc(2 * sizeof(t_ui_menu_page));
	if (!pages)
		return (1);
	menu_init_page_home(data, menu, &pages[UI_MENU_PAGE_HOME]);
	menu_init_page_end(data, menu, &pages[UI_MENU_PAGE_END]);
	menu->pages = pages;
	return (0);
}

void	menu_draw_page(t_mlx_data *data, t_ui_menu_page page)
{
	int i;

	i = 0;
	while (page.elements[i].type != UI_MENU_END)
	{
		page.elements[i].draw(&page.elements[i], data);
		i++;
	}
}

int	menu_draw(t_mlx_data *data, t_ui_menu *menu)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, menu->bg.img, menu->pos.x, menu->pos.y);
	mlx_string_put(data->mlx, data->mlx_win, menu->pos.x + menu->size.x / 2 - 4 * 4, menu->pos.y + 10 + 5, 0x00CCCCCC, "MENU");
	menu_draw_page(data, menu->pages[UI_MENU_PAGE_HOME]);
	menu->show = MENU_DRAWN;
	return (0);
}

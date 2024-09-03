/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:51:45 by efret             #+#    #+#             */
/*   Updated: 2024/09/03 14:54:44 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_draw_space(t_ui_menu_elem *self, t_pixel_coord pos, t_mlx_data *data)
{
	(void)self;
	(void)data;
	(void)pos;
	return (0);
}

int	menu_draw_text(t_ui_menu_elem *self, t_pixel_coord pos, t_mlx_data *data)
{
	(void)self;
	(void)data;
	if (!self->str)
		return (1);
	pos.x += data->menu.curr_page.size.x / 2 - 4 * ft_strlen(self->str);
	mlx_string_put(data->mlx, data->mlx_win, pos.x, pos.y, 0x00FFFFFF, self->str);
	return (0);
}

int	menu_draw_btn(t_ui_menu_elem *self, t_pixel_coord pos, t_mlx_data *data)
{
	(void)self;
	(void)data;
	if (!self->str)
		return (1);
	pos.x += data->menu.curr_page.size.x / 2 - 4 * ft_strlen(self->str);
	mlx_string_put(data->mlx, data->mlx_win, pos.x, pos.y, 0x0000d9ff, self->str);
	return (0);
}

int	menu_btn_reset_cam_pos(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->scene.camera.coordinates = (t_coordinates){0, 0, 0};
	data->scene.camera.yaw = 0;
	data->scene.camera.pitch = 0;
	data->scene.camera.vector = (t_coordinates){0, 0, -1};
	data->scene.camera.right = (t_coordinates){1, 0, 0};
	data->scene.camera.up = (t_coordinates){0, 1, 0};
	return (0);
}

int	menu_draw_nbox(t_ui_menu_elem *self, t_pixel_coord pos, t_mlx_data *data)
{
	(void)self;
	(void)data;
	mlx_string_put(data->mlx, data->mlx_win, pos.x, pos.y, 0x00FFFFFF, self->str);
	return (0);
}


/* Event utilities */
int	box_is_clicked(t_pixel_coord pos, t_pixel_coord size, t_pixel_coord mouse)
{
	mouse.x -= pos.x;
	mouse.y -= pos.y;
	if (mouse.x < 0 || mouse.x > size.x || mouse.y < 0 || mouse.y > size.y)
		return (0);
	return (1);
}

int	menu_page_click(t_mlx_data *data)
{
	int				elem_index;
	t_ui_menu_elem	*elem;

	if (box_is_clicked(data->menu.curr_page.pos, data->menu.curr_page.size, data->mouse_last_pos))
			printf("PAGE CLICK\n");
	if (data->mouse_last_pos.y < data->menu.curr_page.pos.y + ELEM_OFFSET)
		return (0);
	elem_index = (data->mouse_last_pos.y - data->menu.curr_page.pos.y - ELEM_OFFSET) / ELEM_HEIGHT;
	if (elem_index < 0 || elem_index >= data->menu.curr_page.n_elems)
		return (0);
	elem = &data->menu.curr_page.elements[elem_index];
	printf("Element #%i click: %s\n", elem_index, elem->str);
	if (elem->func && data->mouse_input_state & BTN_LEFT)
		data->menu.curr_page.elements[elem_index].func(elem, data);
	return (0);
}


/* Initialising the pages */

int	menu_init_page_home(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	t_ui_menu_elem	*elems;

	page->n_elems = 5;
	elems = malloc((page->n_elems + 1) * sizeof(t_ui_menu_elem));
	if (!elems)
		return (page->title = NULL, 1);
	page->title = "HOME";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 200};
	elems[0] = (t_ui_menu_elem){UI_MENU_TEXT, "Camera", 0, menu_draw_text, NULL};
	elems[1] = (t_ui_menu_elem){UI_MENU_BTN, "Reset position", 1, menu_draw_btn, menu_btn_reset_cam_pos};
	elems[2] = (t_ui_menu_elem){UI_MENU_NBOX, "Box1", 2, menu_draw_nbox, NULL};
	elems[3] = (t_ui_menu_elem){UI_MENU_SPACE, NULL, 3, menu_draw_space, NULL};
	elems[4] = (t_ui_menu_elem){UI_MENU_NBOX, "Box2", 4, menu_draw_nbox, NULL};
	elems[page->n_elems] = (t_ui_menu_elem){UI_MENU_END, "END", page->n_elems, NULL, NULL};
	page->elements = elems;
	return (0);
}

int	menu_init_page_end(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	(void)menu;
	*page = (t_ui_menu_page){NULL, NULL, 0, (t_pixel_coord){0, 0}, (t_pixel_coord){0, 0}};
	return (0);
}

int	menu_init_pages(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page	*pages;

	pages = malloc((UI_MENU_PAGE_END + 1) * sizeof(t_ui_menu_page));
	if (!pages)
		return (1);
	menu_init_page_home(data, menu, &pages[UI_MENU_PAGE_HOME]);
	menu_init_page_end(data, menu, &pages[UI_MENU_PAGE_SELECT]);
	menu_init_page_end(data, menu, &pages[UI_MENU_PAGE_ADD]);
	menu_init_page_end(data, menu, &pages[UI_MENU_PAGE_REMOVE]);
	menu_init_page_end(data, menu, &pages[UI_MENU_PAGE_OBJ_SPHERE]);
	menu_init_page_end(data, menu, &pages[UI_MENU_PAGE_OBJ_CYLINDER]);
	menu_init_page_end(data, menu, &pages[UI_MENU_PAGE_OBJ_PLANE]);
	menu_init_page_end(data, menu, &pages[UI_MENU_PAGE_END]);
	menu->pages = pages;
	return (0);
}

/* Drawing the menu and pages */

void	menu_draw_page(t_mlx_data *data, t_ui_menu_page page)
{
	int				i;
	t_pixel_coord	pos;

	if (page.title == NULL)
		return ;
	i = 0;
	mlx_string_put(data->mlx, data->mlx_win, page.pos.x + page.size.x / 2 - ft_strlen(page.title) * 4, page.pos.y + 15, 0x00DDDDDD, page.title);

	mlx_string_put(data->mlx, data->mlx_win, page.pos.x - 4, page.pos.y + 5, 0x00000000, "x");
	mlx_string_put(data->mlx, data->mlx_win, page.pos.x + page.size.x - 4, page.pos.y + 5, 0x00000000, "x");

	mlx_string_put(data->mlx, data->mlx_win, page.pos.x - 4, page.pos.y + page.size.y - ELEM_OFFSET + 5, 0x00000000, "x");
	mlx_string_put(data->mlx, data->mlx_win, page.pos.x + page.size.x - 4, page.pos.y + page.size.y - ELEM_OFFSET + 5, 0x00000000, "x");

	mlx_string_put(data->mlx, data->mlx_win, page.pos.x - 4, page.pos.y + ELEM_OFFSET + 5, 0x00000000, "x");
	mlx_string_put(data->mlx, data->mlx_win, page.pos.x + page.size.x - 4, page.pos.y + ELEM_OFFSET + 5, 0x00000000, "x");

	pos = page.pos;
	pos.y += ELEM_OFFSET + ELEM_HEIGHT;
	while (page.elements[i].type != UI_MENU_END)
	{
		page.elements[i].draw(&page.elements[i], pos, data);
		pos.y += ELEM_HEIGHT;
		i++;
	}
}

int	menu_draw(t_mlx_data *data, t_ui_menu *menu)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, menu->bg.img, menu->pos.x, menu->pos.y);
	mlx_string_put(data->mlx, data->mlx_win, menu->pos.x + menu->size.x / 2 - 4 * 4, menu->pos.y + 10 + 5, 0x00CCCCCC, "MENU");
	if (data->selected.obj_type == OBJ_NONE)
		menu->curr_page = menu->pages[UI_MENU_PAGE_HOME];
	else if (data->selected.obj_type == OBJ_PLANE)
		menu->curr_page = menu->pages[UI_MENU_PAGE_OBJ_PLANE];
	menu_draw_page(data, menu->curr_page);
	menu->show = MENU_DRAWN;
	return (0);
}

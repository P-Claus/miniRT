/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_event_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:38:27 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 16:43:43 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	menu_nbox_get_input(t_ui_menu_elem *self, t_mlx_data *data)
{
	data->menu.curr_input_elem = self;
	data->menu.curr_input_str = NULL;
	return (0);
}

int	menu_nbox_slide(t_mlx_data *data, t_ui_menu_elem *elem, t_pixel_coord diff)
{
	if (elem->data.data_type == UI_DATA_INT)
		*(int *)elem->data.data = fmin(
				fmax(*(int *)elem->data.data + diff.x * elem->range.step,
					elem->range.data_min),
				elem->range.data_max);
	else if (elem->data.data_type == UI_DATA_FLOAT)
		*(float *)elem->data.data = fmin(
				fmax(*(float *)elem->data.data + diff.x * elem->range.step,
					elem->range.data_min),
				elem->range.data_max);
	rotate_camera(&data->scene.camera, (t_pixel_coord){0, 0}, 0);
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

int	menu_page_click(t_mlx_data *data)
{
	int				elem_index;
	t_ui_menu_elem	*elem;

	if (data->mouse_last_pos.y < data->menu.curr_page->pos.y + ELEM_OFFSET)
		return (0);
	if (data->menu.curr_input_str)
	{
		free(data->menu.curr_input_str);
		data->menu.curr_input_str = NULL;
	}
	data->menu.curr_input_elem = NULL;
	elem_index = (data->mouse_last_pos.y - data->menu.curr_page->pos.y
			- ELEM_OFFSET - data->menu.curr_page->scroll) / ELEM_HEIGHT;
	if (elem_index < 0 || elem_index >= data->menu.curr_page->n_elems)
		return (0);
	elem = data->menu.curr_page->elements;
	while (elem_index--)
		elem = elem->next;
	if (elem->func && elem->type == UI_MENU_NBOX)
		menu_nbox_get_input(elem, data);
	else if (elem->func && data->mouse_input_state & BTN_LEFT)
		elem->func(elem, data);
	return (0);
}

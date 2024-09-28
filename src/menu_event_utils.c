/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_event_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:38:27 by efret             #+#    #+#             */
/*   Updated: 2024/09/28 14:01:41 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	handle_menu_keypress_nbox_str(int keysym, t_mlx_data *data)
{
	if (keysym == XK_BackSpace)
	{
		if (data->menu.curr_input_str == NULL)
			data->menu.curr_input_str = ft_calloc(1, 1);
		ft_strstrip_char(&data->menu.curr_input_str);
	}
	else if (XK_0 <= keysym && keysym <= XK_9)
		ft_strjoin_char(&data->menu.curr_input_str, keysym);
	else if (XK_a <= keysym && keysym <= XK_z)
		ft_strjoin_char(&data->menu.curr_input_str, keysym);
	else if (keysym == XK_space || keysym == XK_comma || keysym == XK_period
		|| keysym == XK_plus || keysym == XK_minus)
		ft_strjoin_char(&data->menu.curr_input_str, keysym);
	else
		return (0);
	return (1);
}

int	handle_menu_keypress(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
	{
		data->menu.curr_input_elem = NULL;
		free(data->menu.curr_input_str);
		data->menu.curr_input_str = NULL;
	}
	else if (keysym == XK_Return)
	{
		if (data->menu.curr_input_str == NULL)
			return (data->menu.curr_input_elem = NULL,
				data->menu.show = MENU_SHOW, 0);
		if (data->menu.curr_input_elem->func)
			data->menu.curr_input_elem->func(data->menu.curr_input_elem, data);
		data->menu.curr_input_elem = NULL;
		free(data->menu.curr_input_str);
		data->menu.curr_input_str = NULL;
	}
	else if (handle_menu_keypress_nbox_str(keysym, data))
		;
	data->menu.show = MENU_SHOW;
	return (0);
}

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

int	menu_page_click(t_mlx_data *data, t_ui_menu_page *page)
{
	int				elem_index;
	t_ui_menu_elem	*elem;

	if (data->menu.curr_input_str)
	{
		free(data->menu.curr_input_str);
		data->menu.curr_input_str = NULL;
	}
	data->menu.curr_input_elem = NULL;
	if (!box_is_clicked(page->pos, page->size, data->mouse_last_pos)
		|| data->mouse_last_pos.y < page->pos.y + ELEM_OFFSET)
		return (0);
	elem_index = (data->mouse_last_pos.y - page->pos.y
			- ELEM_OFFSET - page->scroll) / ELEM_HEIGHT;
	if (elem_index < 0 || elem_index >= page->n_elems)
		return (0);
	elem = page->elements;
	while (elem_index--)
		elem = elem->next;
	if (elem->func && elem->type == UI_MENU_NBOX)
		menu_nbox_get_input(elem, data);
	else if (elem->func && data->mouse_input_state & BTN_LEFT)
		elem->func(elem, data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_draw_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:31:25 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 16:50:09 by efret            ###   ########.fr       */
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
	pos.x += data->menu.curr_page->size.x / 2 - 4 * ft_strlen(self->str);
	mlx_string_put(
		data->mlx, data->mlx_win, pos.x, pos.y, 0x00FFFFFF, self->str);
	return (0);
}

int	menu_draw_btn(t_ui_menu_elem *self, t_pixel_coord pos, t_mlx_data *data)
{
	(void)self;
	(void)data;
	if (!self->str)
		return (1);
	pos.x += data->menu.curr_page->size.x / 2 - 4 * ft_strlen(self->str);
	mlx_string_put(
		data->mlx, data->mlx_win, pos.x, pos.y, 0x0000d9ff, self->str);
	return (0);
}

int	menu_draw_nbox(t_ui_menu_elem *self, t_pixel_coord pos, t_mlx_data *data)
{
	char	*box_text;
	int		color;
	bool	is_curr_input;

	is_curr_input = (data->menu.curr_input_elem == self);
	color = 0x00FFFFFF;
	if (is_curr_input)
		color = 0x0000d9ff;
	mlx_string_put(data->mlx, data->mlx_win, pos.x, pos.y, color, self->str);
	box_text = data->menu.curr_input_str;
	if (is_curr_input && box_text)
		return (mlx_string_put(data->mlx, data->mlx_win,
				pos.x + data->menu.curr_page->size.x - 10 * ft_strlen(box_text),
				pos.y, color, box_text), 0);
	else if (self->data.data_type == UI_DATA_INT)
		box_text = ft_itoa(*((int *)self->data.data));
	else if (self->data.data_type == UI_DATA_FLOAT)
		box_text = ft_ftoa(*((float *)self->data.data), 3);
	else
		box_text = NULL;
	if (box_text)
		mlx_string_put(data->mlx, data->mlx_win,
			pos.x + data->menu.curr_page->size.x - 10 * ft_strlen(box_text),
			pos.y, color, box_text);
	return (free(box_text), 0);
}

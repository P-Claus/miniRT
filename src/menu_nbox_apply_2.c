/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_nbox_apply_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:36:07 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 15:36:56 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_nbox_apply_float(t_ui_menu_elem *self, t_mlx_data *data)
{
	float	new_val;

	if (self->data.data_type != UI_DATA_FLOAT)
		return (1);
	new_val = ft_atof(data->menu.curr_input_str, 6);
	if (new_val < self->range.data_min || self->range.data_max < new_val)
		return (
			printf("Invalid input: expected value between [%f, %f]\n",
				self->range.data_min, self->range.data_max), 1);
	*(float *)self->data.data = new_val;
	return (0);
}

int	menu_nbox_apply_fov(t_ui_menu_elem *self, t_mlx_data *data)
{
	int	new_val;

	if (self->data.data_type != UI_DATA_INT)
		return (1);
	new_val = ft_atoi(data->menu.curr_input_str);
	if (new_val < self->range.data_min || self->range.data_max < new_val)
		return (
			printf("Invalid input: fov should be int in [%f, %f] range.\n",
				self->range.data_min, self->range.data_max));
	*(int *)self->data.data = new_val;
	return (0);
}

int	menu_nbox_apply_color_float(t_ui_menu_elem *self, t_mlx_data *data)
{
	float	new_val;

	if (self->data.data_type != UI_DATA_FLOAT)
		return (1);
	if (data->menu.curr_input_str[0] == 'i')
		new_val = ft_atoi(&data->menu.curr_input_str[1]) / 255.;
	else if (data->menu.curr_input_str[0] == '0'
		&& data->menu.curr_input_str[1] == 'x')
		new_val = ft_atoi_base(
				&data->menu.curr_input_str[2], "0123456789abcdef") / 255.;
	else
		new_val = ft_atof(data->menu.curr_input_str, 6);
	if (new_val < self->range.data_min || self->range.data_max < new_val)
		return (
			printf("Invalid input: color channel value between [%f, %f]\n",
				self->range.data_min, self->range.data_max), 1);
	*(float *)self->data.data = new_val;
	return (0);
}

int	menu_nbox_apply_perc(t_ui_menu_elem *self, t_mlx_data *data)
{
	float	new_val;

	if (self->data.data_type != UI_DATA_FLOAT)
		return (1);
	if (data->menu.curr_input_str[0] == 'p')
		new_val = ft_atoi(&data->menu.curr_input_str[1]) / 100.;
	else
		new_val = ft_atof(data->menu.curr_input_str, 6);
	if (new_val < self->range.data_min || self->range.data_max < new_val)
		return (
			printf("Invalid input: percent value between [%f, %f]\n",
				self->range.data_min, self->range.data_max), 1);
	*(float *)self->data.data = new_val;
	return (0);
}

int	menu_nbox_apply_int(t_ui_menu_elem *self, t_mlx_data *data)
{
	int	new_val;

	if (self->data.data_type != UI_DATA_INT)
		return (1);
	new_val = ft_atoi(data->menu.curr_input_str);
	if (new_val < self->range.data_min || self->range.data_max < new_val)
		return (
			printf("Invalid input: expected value between [%i, %i]\n",
				(int)self->range.data_min, (int)self->range.data_max), 1);
	*(int *)self->data.data = new_val;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_nbox_apply_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:34:51 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 16:46:45 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_nbox_apply_yaw(t_ui_menu_elem *self, t_mlx_data *data)
{
	float	new_val;

	if (self->data.data_type != UI_DATA_FLOAT)
		return (1);
	if (data->menu.curr_input_str[0] == 'd')
		new_val = ft_atof(&data->menu.curr_input_str[1], 6) * DEG2RAD;
	else
		new_val = ft_atof(data->menu.curr_input_str, 6);
	new_val = new_val - M_PI * 2 * floor(new_val / (M_PI * 2));
	*(float *)self->data.data = new_val;
	rotate_camera(&data->scene.camera, (t_pixel_coord){0, 0}, 0);
	return (0);
}

int	menu_nbox_apply_pitch(t_ui_menu_elem *self, t_mlx_data *data)
{
	float	new_val;

	if (self->data.data_type != UI_DATA_FLOAT)
		return (1);
	if (data->menu.curr_input_str[0] == 'd')
		new_val = ft_atof(&data->menu.curr_input_str[1], 6) * DEG2RAD;
	else
		new_val = ft_atof(data->menu.curr_input_str, 6);
	if (new_val < -M_PI_2 || new_val > M_PI_2)
	{
		printf("Invalid input: pitch should be in [-pi/2, pi/2] range.\n");
		return (1);
	}
	*(float *)self->data.data = new_val;
	rotate_camera(&data->scene.camera, (t_pixel_coord){0, 0}, 0);
	return (0);
}

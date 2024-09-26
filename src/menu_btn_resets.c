/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_btn_resets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:26:08 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 16:50:31 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_btn_reset_pos(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)data;
	*((t_coordinates *)self->data.data) = (t_coordinates){0, 0, 0};
	return (0);
}

int	menu_btn_reset_dir(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)data;
	*((t_coordinates *)self->data.data) = (t_coordinates){0, 1, 0};
	return (0);
}

int	menu_btn_reset_cam_pos(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->scene.camera.coordinates = (t_coordinates){0, 0, 0};
	return (0);
}

int	menu_btn_reset_cam_dir(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->scene.camera.yaw = 0;
	data->scene.camera.pitch = 0;
	data->scene.camera.vector = (t_coordinates){0, 0, -1};
	data->scene.camera.right = (t_coordinates){1, 0, 0};
	data->scene.camera.up = (t_coordinates){0, 1, 0};
	return (0);
}

int	menu_btn_reset_cam(t_ui_menu_elem *self, t_mlx_data *data)
{
	menu_btn_reset_cam_pos(self, data);
	menu_btn_reset_cam_dir(self, data);
	return (0);
}

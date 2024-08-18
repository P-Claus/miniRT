/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:36:41 by efret             #+#    #+#             */
/*   Updated: 2024/08/18 17:28:11 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	render(t_mlx_data *data)
{
	static int i = 0;
	int j = data->heigth / 2;

	fast_pixel_put(data, (t_pixel_coord){i, j}, 0x00000000);
	i = (i + 1) % data->width;
	fast_pixel_put(data, (t_pixel_coord){i, j}, 0x00FFFFFF);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->render.img, 0, 0);
}

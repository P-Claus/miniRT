/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:39:59 by efret             #+#    #+#             */
/*   Updated: 2024/08/19 15:27:24 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	on_screen(t_mlx_data *data, t_pixel_coord p)
{
	if (p.x < 0 || data->width <= p.x || p.y < 0 || data->heigth <= p.y)
		return (0);
	return (1);
}

void	fast_pixel_put(t_mlx_data *data, t_pixel_coord p, int color)
{
	int	i;

	if (!data || !data->render.img || !on_screen(data, p))
		return ;
	i = ((int)p.y * data->render.line_len + (int)p.x * (data->render.bpp / 8));
	*(unsigned int *)(data->render.addr + i) = color;
}

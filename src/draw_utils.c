/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:39:59 by efret             #+#    #+#             */
/*   Updated: 2024/08/19 16:53:30 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	fast_pixel_put(t_mlx_data *data, t_pixel_coord p, int color)
{
	int	i;

	if (!data || !data->render.img)
		return ;
	i = (p.y * data->render.line_len + p.x * (data->render.bpp / 8));
	*(unsigned int *)(data->render.addr + i) = color;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:39:59 by efret             #+#    #+#             */
/*   Updated: 2024/09/07 17:51:34 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	fast_pixel_put(t_ui_viewport ui, t_pixel_coord p, int color)
{
	int	i;

	if (!ui.render.img)
		return ;
	i = (p.y * ui.render.line_len + p.x * (ui.render.bpp / 8));
	*(unsigned int *)(ui.render.addr + i) = color;
}

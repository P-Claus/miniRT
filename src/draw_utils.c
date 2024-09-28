/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:39:59 by efret             #+#    #+#             */
/*   Updated: 2024/09/28 14:16:05 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	img_draw_rect(t_my_img img,
		t_pixel_coord pos, t_pixel_coord size, int color)
{
	t_pixel_coord	iter;
	int				i;

	if (!img.img)
		return ;
	iter.y = 0;
	while (iter.y < size.y)
	{
		iter.x = 0;
		while (iter.x < size.x)
		{
			i = ((pos.y + iter.y) * img.line_len
					+ (pos.x + iter.x) * (img.bpp / 8));
			*(unsigned int *)(img.addr + i) = color;
			iter.x++;
		}
		iter.y++;
	}
}

void	fast_pixel_put(t_ui_viewport ui, t_pixel_coord p, int color)
{
	int	i;

	if (!ui.render.img)
		return ;
	i = (p.y * ui.render.line_len + p.x * (ui.render.bpp / 8));
	*(unsigned int *)(ui.render.addr + i) = color;
}

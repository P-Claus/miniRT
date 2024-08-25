/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:45:28 by efret             #+#    #+#             */
/*   Updated: 2024/08/25 13:53:51 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_rgb	color_scalar(t_rgb c, float scale)
{
	return ((t_rgb){c.r * scale, c.g * scale, c.b * scale});
}

int	color_to_int(t_rgb c)
{
	c = color_scalar(c, 255.);
	return (0x00000000 | ((int)c.r << 16) | ((int)c.g << 8) | (int)c.b);
}

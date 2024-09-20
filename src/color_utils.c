/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:45:28 by efret             #+#    #+#             */
/*   Updated: 2024/09/20 18:44:17 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_rgb	color_add(t_rgb a, t_rgb b)
{
	return ((t_rgb){a.r + b.r, a.g + b.g, a.b + b.b});
}

t_rgb	color_scalar(t_rgb c, float scale)
{
	return ((t_rgb){c.r * scale, c.g * scale, c.b * scale});
}

float	color_dot(t_rgb a, t_rgb b)
{
	return (a.r * b.r + a.g * b.g + a.b * b.b);
}

t_rgb	color_hadamard(t_rgb a, t_rgb b)
{
	return ((t_rgb){a.r * b.r, a.g * b.g, a.b * b.b});
}

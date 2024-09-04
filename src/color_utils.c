/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:45:28 by efret             #+#    #+#             */
/*   Updated: 2024/09/04 17:29:56 by efret            ###   ########.fr       */
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

static void	color_clamp(t_rgb *c)
{
	c->r = fmax(fmin(c->r,1),0);
	c->g = fmax(fmin(c->g,1),0);
	c->b = fmax(fmin(c->b,1),0);
}

void	color_gamma_correct_channel(float *channel)
{
	if (*channel < 0.0031308)
		*channel = 12.92 * (*channel);
	else
		*channel = 1.055 * pow(*channel, 0.41666) - 0.055;
}

void	color_gamma_correct(t_rgb *c)
{
	color_gamma_correct_channel(&c->r);
	color_gamma_correct_channel(&c->g);
	color_gamma_correct_channel(&c->b);
}

void color_gamma_correct_fast(t_rgb *c)
{
	c->r = sqrt(c->r);
	c->g = sqrt(c->g);
	c->b = sqrt(c->b);
}

int	color_to_int(t_rgb c)
{
	color_clamp(&c);
#if 1
	color_gamma_correct(&c);
#elif 1
	color_gamma_correct_fast(&c);
#endif
	c = color_scalar(c, 255.);
	return (0x00000000 | ((int)c.r << 16) | ((int)c.g << 8) | (int)c.b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:43:59 by efret             #+#    #+#             */
/*   Updated: 2024/09/20 18:45:03 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	color_clamp(t_rgb *c)
{
	c->r = fmax(fmin(c->r, 1.), 0.);
	c->g = fmax(fmin(c->g, 1.), 0.);
	c->b = fmax(fmin(c->b, 1.), 0.);
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

void	color_gamma_correct_fast(t_rgb *c)
{
	c->r = sqrt(c->r);
	c->g = sqrt(c->g);
	c->b = sqrt(c->b);
}

int	color_to_int(t_rgb c, t_gamma_type gamma_type)
{
	color_clamp(&c);
	if (gamma_type == GAMMA_CORRECT)
		color_gamma_correct(&c);
	else if (gamma_type == GAMMA_FAST)
		color_gamma_correct_fast(&c);
	else if (gamma_type == GAMMA_NONE)
		;
	c = color_scalar(c, 255.);
	return (0x00000000 | ((int)c.r << 16) | ((int)c.g << 8) | (int)c.b);
}

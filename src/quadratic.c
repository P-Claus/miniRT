/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:19:26 by efret             #+#    #+#             */
/*   Updated: 2024/09/05 16:41:39 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	solve_quadratic(float a, float b, float c, float *dist)
{
	float	discr;
	float	d[2];

	if (a >= 0 && a < 1e-5)
		return (*dist = -c / b, true);
	discr = b * b - 4. * a * c;
	if (discr < 0)
		return (false);
	else if (discr == 0)
		*dist = -0.5 * b / a;
	else
	{
		d[0] = -0.5 * (b + sqrt(discr)) / a;
		d[1] = -0.5 * (b - sqrt(discr)) / a;
		if (d[0] > 0 && d[0] < d[1])
			*dist = d[0];
		else
			*dist = d[1];
	}
	return (*dist > 0);
}

bool	solve_quadratic2(float a, float b, float c, float *dist)
{
	float	discr;
	float	d[2];

	if (a >= 0 && a < 1e-5)
		return (*dist = -c / b, true);
	discr = b * b - 4. * a * c;
	if (discr < 0)
		return (false);
	else if (discr == 0)
		*dist = -0.5 * b / a;
	else
	{
		d[0] = -0.5 * (b + sqrt(discr)) / a;
		d[1] = -0.5 * (b - sqrt(discr)) / a;
		if (d[1] > 0 && d[0] < d[1])
			*dist = d[1];
		else
			*dist = d[0];
	}
	return (*dist > 0);
}

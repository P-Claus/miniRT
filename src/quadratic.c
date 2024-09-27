/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:19:26 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 20:00:49 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	solve_quadratic(t_q_vars q_vars, float *dist)
{
	float	discr;
	float	d[2];

	if (q_vars.a >= 0 && q_vars.a < 1e-5)
		return (*dist = -q_vars.c / q_vars.b, true);
	discr = q_vars.b * q_vars.b - 4. * q_vars.a * q_vars.c;
	if (discr < 0)
		return (false);
	else if (discr == 0)
		*dist = -0.5 * q_vars.b / q_vars.a;
	else
	{
		d[0] = -0.5 * (q_vars.b + sqrt(discr)) / q_vars.a;
		d[1] = -0.5 * (q_vars.b - sqrt(discr)) / q_vars.a;
		if (d[0] > 0 && d[0] < d[1])
			*dist = d[0];
		else
			*dist = d[1];
	}
	return (*dist > 0);
}

bool	solve_quadratic2(t_q_vars q_vars, float *dist)
{
	float	discr;
	float	d[2];

	if (q_vars.a >= 0 && q_vars.a < 1e-5)
		return (*dist = -q_vars.c / q_vars.b, true);
	discr = q_vars.b * q_vars.b - 4. * q_vars.a * q_vars.c;
	if (discr < 0)
		return (false);
	else if (discr == 0)
		*dist = -0.5 * q_vars.b / q_vars.a;
	else
	{
		d[0] = -0.5 * (q_vars.b + sqrt(discr)) / q_vars.a;
		d[1] = -0.5 * (q_vars.b - sqrt(discr)) / q_vars.a;
		if (d[0] && d[0] < d[1])
			*dist = d[1];
		else
			*dist = d[0];
	}
	return (*dist > 0);
}

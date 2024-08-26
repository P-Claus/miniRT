/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:19:26 by efret             #+#    #+#             */
/*   Updated: 2024/08/26 17:03:12 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	solve_quadratic(float a, float b, float c, float *dist)
{
	float	discr;
	float	d[2];

	discr = b * b - 4. * a * c;
	if (discr < 0)
		return (false);
	else if (discr == 0)
		*dist = -0.5 * b / a;
	else
	{
		d[0] = -0.5 * (b + sqrt(discr)) / a;
		d[1] = -0.5 * (b - sqrt(discr)) / a;
		if (d[0] < d[1])
			*dist = d[0];
		else
			*dist = d[1];
	}
	return (true);
}

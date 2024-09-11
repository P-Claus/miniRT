/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:24:59 by efret             #+#    #+#             */
/*   Updated: 2024/09/11 15:31:30 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/* Add a and b elementwise */
t_coordinates	vec3_sum(t_coordinates a, t_coordinates b)
{
	return ((t_coordinates){a.x + b.x, a.y + b.y, a.z + b.z});
}

/* Subtract b from a elementwise */
t_coordinates	vec3_diff(t_coordinates a, t_coordinates b)
{
	return ((t_coordinates){a.x - b.x, a.y - b.y, a.z - b.z});
}

/* Return the negative of the vector. Basically scalar multiplication with -1 */
t_coordinates	vec3_neg(t_coordinates a)
{
	return ((t_coordinates){-a.x, -a.y, -a.z});
}

float	vec3_dot(t_coordinates a, t_coordinates b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_coordinates	vec3_cross(t_coordinates a, t_coordinates b)
{
	t_coordinates	cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	return (cross);
}

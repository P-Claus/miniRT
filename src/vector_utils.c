/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:24:59 by efret             #+#    #+#             */
/*   Updated: 2024/08/20 13:33:38 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_coordinates	vec3_sum(t_coordinates a, t_coordinates b)
{
	return ((t_coordinates){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_coordinates	vec3_scalar(t_coordinates a, float scalar)
{
	return ((t_coordinates){a.x * scalar, a.y * scalar, a.z * scalar});
}

float			vec3_dot(t_coordinates a, t_coordinates b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/* Euclidean norm */
float			vec3_norm(t_coordinates a)
{
	return (sqrt(vec3_dot(a, a)));
}

t_coordinates	vec3_normalize(t_coordinates a)
{
	float	hypot;

	hypot = vec3_norm(a);
	if (hypot == 0)
		return ((t_coordinates){INFINITY, INFINITY, INFINITY});
	return (vec3_scalar(a, 1. / hypot));
}

t_coordinates	vec3_cross(t_coordinates a, t_coordinates b)
{
	t_coordinates	cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	return (cross);
}

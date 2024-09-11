/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_norm_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:29:32 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/11 15:31:23 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/* Euclidean norm */
float	vec3_norm(t_coordinates a)
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

t_coordinates	vec3_scalar(t_coordinates a, float scalar)
{
	return ((t_coordinates){a.x * scalar, a.y * scalar, a.z * scalar});
}

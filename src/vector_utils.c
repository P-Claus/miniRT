/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:24:59 by efret             #+#    #+#             */
/*   Updated: 2024/09/13 00:39:31 by efret            ###   ########.fr       */
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

float	vec3_dot2(t_coordinates a)
{
	return (vec3_dot(a, a));
}

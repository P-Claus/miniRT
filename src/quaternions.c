/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:09:17 by efret             #+#    #+#             */
/*   Updated: 2024/08/29 23:48:08 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_quat	quat_axis_rot(t_coordinates axis, float radians)
{
	t_quat	quat;

	quat.r = cos(radians / 2);
	quat.v = vec3_scalar(vec3_normalize(axis), sin(radians / 2));
	return (quat);
}

t_quat	quat_set(float r, t_coordinates v)
{
	t_quat	quat;

	quat.r = r;
	quat.v = v;
	return (quat);
}

t_quat	quat_mult(t_quat a, t_quat b)
{
	t_quat	quat;

	quat.r = a.r * b.r - vec3_dot(a.v, b.v);
	quat.v = vec3_scalar(b.v, a.r);
	quat.v = vec3_sum(quat.v, vec3_scalar(a.v, b.r));
	quat.v = vec3_sum(quat.v, vec3_cross(a.v, b.v));
	return (quat);
}

t_coordinates	quat_rotate_point(t_coordinates p, t_quat q)
{
	t_quat	q_inv;
	t_quat	coord;

	q_inv = quat_set(q.r, vec3_neg(q.v));
	coord = quat_set(0, p);
	coord = quat_mult(q_inv, coord);
	coord = quat_mult(coord, q);
	return (coord.v);
}

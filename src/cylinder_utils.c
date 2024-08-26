/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:07:09 by efret             #+#    #+#             */
/*   Updated: 2024/08/26 17:52:48 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	cylinder_hit(t_ray ray, t_cylinder cylinder, float *dist)
{
	t_coordinates	base = vec3_diff(cylinder.coordinates, vec3_scalar(cylinder.vector, cylinder.height / 2.));
	t_coordinates	l = vec3_diff(base, ray.origin);
	float			r = cylinder.diameter / 2.;

	float	d[2];
	t_coordinates	nxa = vec3_cross(ray.dir, cylinder.vector);
	t_coordinates	lxa = vec3_cross(l, cylinder.vector);
	if (vec3_norm(nxa) < 1e-6)
		return (false);
	float	discr = vec3_dot(nxa, nxa) * r * r - pow(vec3_dot(l, nxa), 2);
	if (discr < 0)
		return (false);
	else if (discr == 0)
		*dist = vec3_dot(nxa, lxa) / vec3_dot(nxa, nxa);
	else
	{
		d[0] = (vec3_dot(nxa, lxa) + sqrt(discr)) / vec3_dot(nxa, nxa);
		d[1] = (vec3_dot(nxa, lxa) - sqrt(discr)) / vec3_dot(nxa, nxa);
		if (d[0] < d[1])
			*dist = d[0];
		else
			*dist = d[1];
	}
	float	t = vec3_dot(cylinder.vector, vec3_diff(vec3_scalar(ray.dir, *dist), l));
	if (t <= 0 || t >= cylinder.height)
	{
		t_disk	cap;
		if (t < 0)
			cap = (t_disk){base, vec3_neg(cylinder.vector), cylinder.diameter, cylinder.rgb};
		else
			cap = (t_disk){vec3_sum(base, vec3_scalar(cylinder.vector, cylinder.height)), cylinder.vector, cylinder.diameter, cylinder.rgb};
		return (disk_hit(ray, cap, dist));
	}
	return (true);
}

t_coordinates	cylinder_normal(t_hit_info hit, t_cylinder cylinder)
{
	t_coordinates	b = vec3_diff(cylinder.coordinates, vec3_scalar(cylinder.vector, cylinder.height / 2.));
	float			t = vec3_dot(cylinder.vector, vec3_diff(hit.coordinates, b));

	if (t <= 1e-4)
		return (vec3_neg(cylinder.vector));
	else if (t >= cylinder.height - 1e-4)
		return (cylinder.vector);
	return (vec3_normalize(vec3_diff(vec3_diff(hit.coordinates, vec3_scalar(cylinder.vector, t)), b)));
}

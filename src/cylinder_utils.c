/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:07:09 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 20:18:24 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

typedef struct s_cy_help
{
	t_coordinates	base;
	float			r;
	t_coordinates	l;
}	t_cy_help;

bool	cylinder_inf_hit(
		t_ray ray, t_cylinder cylinder, t_cy_help help, float *dist)
{
	float			discr;
	float			d[2];
	t_coordinates	nxa;
	t_coordinates	lxa;

	nxa = vec3_cross(ray.dir, cylinder.vector);
	lxa = vec3_cross(help.l, cylinder.vector);
	if (vec3_norm(nxa) < 1e-6)
		return (false);
	discr = vec3_dot(nxa, nxa) * help.r * help.r
		- pow(vec3_dot(help.l, nxa), 2);
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
	return (true);
}

bool	cylinder_hit(t_ray ray, t_cylinder cylinder, float *dist)
{
	t_cy_help	help;
	float		t;
	t_disk		cap;

	help.base = vec3_diff(cylinder.coordinates,
			vec3_scalar(cylinder.vector, cylinder.height / 2.));
	help.l = vec3_diff(help.base, ray.origin);
	help.r = cylinder.diameter / 2.;
	if (!cylinder_inf_hit(ray, cylinder, help, dist))
		return (false);
	t = vec3_dot(cylinder.vector,
			vec3_diff(vec3_scalar(ray.dir, *dist), help.l));
	if (t <= 0 || t >= cylinder.height)
	{
		if (t < 0)
			cap = (t_disk){help.base, vec3_neg(cylinder.vector),
				cylinder.diameter, cylinder.rgb};
		else
			cap = (t_disk){vec3_sum(help.base,
					vec3_scalar(cylinder.vector, cylinder.height)),
				cylinder.vector, cylinder.diameter, cylinder.rgb};
		return (disk_hit(ray, cap, dist));
	}
	return (true);
}

t_coordinates	cylinder_normal(t_hit_info hit, t_cylinder cylinder)
{
	t_coordinates	b;
	float			t;

	b = vec3_diff(cylinder.coordinates,
			vec3_scalar(cylinder.vector, cylinder.height / 2.));
	t = vec3_dot(cylinder.vector, vec3_diff(hit.coordinates, b));
	if (t <= 1e-4)
		return (vec3_neg(cylinder.vector));
	else if (t >= cylinder.height - 1e-4)
		return (cylinder.vector);
	return (vec3_normalize(vec3_diff(vec3_diff(hit.coordinates,
					vec3_scalar(cylinder.vector, t)), b)));
}

void	cylinder_move(t_cylinder *cylinder, t_coordinates move_dir)
{
	cylinder->coordinates = vec3_sum(cylinder->coordinates, move_dir);
}

void	cylinder_rot(t_cylinder *cylinder, t_quat q)
{
	cylinder->vector = vec3_normalize(quat_rotate_point(cylinder->vector, q));
}

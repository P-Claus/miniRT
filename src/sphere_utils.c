/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:15:19 by efret             #+#    #+#             */
/*   Updated: 2024/08/25 16:07:22 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	sphere_hit(t_ray ray, t_sphere sphere, float *dist)
{
	t_coordinates	l;
	float			a;
	float			b;
	float			c;
	float			discr;
	float			d[2];

	l = vec3_diff(ray.origin, sphere.coordinates);
	a = vec3_dot(ray.dir, ray.dir);
	b = 2. * vec3_dot(l, ray.dir);
	c = vec3_dot(l, l) - pow(sphere.diameter / 2, 2);
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (false);
	else if (discr == 0)
		*dist = -0.5 * b / a;
	else
	{
		d[0] = -0.5 * (b + sqrt(discr)) / a;
		d[1] = -0.5 * (b - sqrt(discr)) / a;
	}
	if (d[0] < d[1])
		*dist = d[0];
	else
		*dist = d[1];
	return (true);
}

t_coordinates	sphere_normal(t_hit_info hit, t_sphere sphere)
{
	return (vec3_normalize(vec3_diff(hit.coordinates, sphere.coordinates)));
}

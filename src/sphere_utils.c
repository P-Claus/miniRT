/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:15:19 by efret             #+#    #+#             */
/*   Updated: 2024/09/28 00:22:52 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	sphere_hit(t_ray ray, t_sphere sphere, float *dist)
{
	t_coordinates	l;
	t_q_vars		q_vars;

	l = vec3_diff(ray.origin, sphere.coordinates);
	q_vars.c = vec3_dot(l, l) - pow(sphere.diameter / 2, 2);
	if (q_vars.c <= 1e-6)
		return (false);
	q_vars.a = vec3_dot(ray.dir, ray.dir);
	q_vars.b = 2. * vec3_dot(l, ray.dir);
	return (solve_quadratic(q_vars, dist));
}

t_coordinates	sphere_normal(t_hit_info hit, t_sphere sphere)
{
	return (vec3_normalize(vec3_diff(hit.coordinates, sphere.coordinates)));
}

void	sphere_move(t_sphere *sphere, t_coordinates move_dir)
{
	sphere->coordinates = vec3_sum(sphere->coordinates, move_dir);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:01:31 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/27 23:25:25 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_q_vars	calculate_quadratic_variables(t_ray ray, t_cone cone,
		t_coordinates apex_to_origin)
{
	float		half_angle;
	float		radius;
	t_q_vars	quadratic_variables;

	radius = cone.diameter / 2;
	half_angle = atan(radius / cone.height);
	quadratic_variables.a = pow(vec3_dot(ray.dir, cone.vector), 2)
		- pow(cos(half_angle), 2);
	quadratic_variables.b = 2 * ((vec3_dot(ray.dir, cone.vector)
				* vec3_dot(apex_to_origin, cone.vector)) - vec3_dot(ray.dir,
				apex_to_origin) * pow(cos(half_angle), 2));
	quadratic_variables.c = pow(vec3_dot(apex_to_origin, cone.vector), 2)
		- vec3_dot(apex_to_origin, apex_to_origin) * pow(cos(half_angle), 2);
	return (quadratic_variables);
}

bool	cone_hit_cap(t_ray ray, t_cone cone, float *dist)
{
	t_disk	cap;

	cap.vector = cone.vector;
	cap.rgb = cone.rgb;
	cap.diameter = cone.diameter;
	cap.coordinates = vec3_sum(cone.apex, vec3_scalar(cone.vector,
				cone.height));
	return (disk_hit(ray, cap, dist));
}

int	cone_ray_inside(t_cone cone, t_coordinates apex_to_origin)
{
	float	t;
	bool	in_inf;

	in_inf = (fabs(vec3_dot(cone.vector, vec3_normalize(apex_to_origin)))
			>= cos(atan(cone.diameter / (cone.height * 2))));
	t = vec3_dot(apex_to_origin, cone.vector);
	if (in_inf && (0 <= t && t <= cone.height))
		return (2);
	else if (in_inf)
		return (1);
	return (0);
}

bool	cone_hit(t_ray ray, t_cone cone, float *dist)
{
	float			t;
	t_q_vars		q_vars;
	t_coordinates	apex_to_origin;
	int				inside;

	apex_to_origin = vec3_diff(ray.origin, cone.apex);
	inside = cone_ray_inside(cone, apex_to_origin);
	if (inside == 2)
		return (false);
	q_vars = calculate_quadratic_variables(ray, cone, apex_to_origin);
	if (inside && vec3_dot(cone.vector, ray.dir) < 0)
		return (cone_hit_cap(ray, cone, dist));
	else if (inside && !solve_quadratic2(q_vars, dist))
		return (false);
	else if (!inside && !solve_quadratic(q_vars, dist))
		return (false);
	t = vec3_dot(cone.vector, vec3_diff(vec3_scalar(ray.dir, *dist),
				vec3_neg(apex_to_origin)));
	if (t <= 0)
		return (false);
	else if (t > cone.height)
		return (cone_hit_cap(ray, cone, dist));
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:01:31 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/04 15:16:43 by pclaus           ###   ########.fr       */
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

bool	cone_hit(t_ray ray, t_cone cone, float *dist)
{
	float			t;
	t_disk			cap;
	t_q_vars		q_vars;
	t_coordinates	apex_to_origin;

	apex_to_origin = vec3_diff(ray.origin, cone.apex);
	q_vars = calculate_quadratic_variables(ray, cone, apex_to_origin);
	if (!solve_quadratic(q_vars.a, q_vars.b, q_vars.c, dist))
		return (false);
	t = vec3_dot(cone.vector, vec3_diff(vec3_scalar(ray.dir, *dist),
				vec3_neg(apex_to_origin)));
	if (t <= 0)
		return (false);
	else if (t > cone.height)
	{
		cap.vector = cone.vector;
		cap.rgb = cone.rgb;
		cap.diameter = cone.diameter;
		cap.coordinates = vec3_sum(cone.apex, vec3_scalar(cone.vector,
					cone.height));
		return (disk_hit(ray, cap, dist));
	}
	return (true);
}

t_coordinates	cone_normal(t_hit_info hit, t_cone cone)
{
	t_coordinates	apex_to_point;
	float			projection_len;
	t_coordinates	normal;
	t_coordinates	cross1;
	t_coordinates	cross2;

	apex_to_point = vec3_diff(hit.coordinates, cone.apex);
	projection_len = vec3_dot(cone.vector, apex_to_point);
	if (projection_len <= 1e-4)
		normal = (t_coordinates){-cone.vector.x, -cone.vector.y,
			-cone.vector.z};
	else if (projection_len >= cone.height)
		normal = cone.vector;
	else
	{
		cross1 = vec3_cross(cone.vector, apex_to_point);
		cross2 = vec3_cross(cross1, apex_to_point);
		normal = vec3_normalize(cross2);
	}
	return (normal);
}

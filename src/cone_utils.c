/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:01:31 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/20 12:55:26 by efret            ###   ########.fr       */
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

	float	actual_angle = vec3_dot(cone.vector, vec3_normalize(apex_to_origin));
	float	cone_angle = cos(atan(cone.diameter / (cone.height * 2)));

	// Check if ray origin is inside the infinite cone volume.
	if (fabs(actual_angle) >= cone_angle)
	{
		// If we are on the side of the base hit the disk.
		if(vec3_dot(cone.vector, ray.dir) < 0)
		{
			cap.vector = cone.vector;
			cap.rgb = cone.rgb;
			cap.diameter = cone.diameter;
			cap.coordinates = vec3_sum(cone.apex, vec3_scalar(cone.vector,
						cone.height));
			return (disk_hit(ray, cap, dist));
		}
		else
		{
			q_vars = calculate_quadratic_variables(ray, cone, apex_to_origin);

			if (!solve_quadratic2(q_vars.a, q_vars.b, q_vars.c, dist))
				return (false);
			t = vec3_dot(cone.vector, vec3_diff(vec3_scalar(ray.dir, *dist),
						vec3_neg(apex_to_origin)));
			if (t <= 0)
				return (false);
			else if (t > cone.height)
				return (false);
			else
				return (true);
		}
	}

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
		normal = vec3_neg(cone.vector);
	else if (projection_len >= cone.height - 1e-4)
		normal = cone.vector;
	else
	{
		cross1 = vec3_cross(cone.vector, apex_to_point);
		cross2 = vec3_cross(cross1, apex_to_point);
		normal = vec3_normalize(cross2);
	}
	return (normal);
}

void	cone_move(t_cone *cone, t_coordinates move_dir)
{
	cone->apex = vec3_sum(cone->apex, move_dir);
}

void	cone_rot(t_cone *cone, t_quat q)
{
	cone->vector = vec3_normalize(quat_rotate_point(cone->vector, q));
}

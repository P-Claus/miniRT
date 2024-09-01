/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:01:31 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/01 21:24:27 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	cone_hit(t_ray ray, t_cone cone, float *dist)
{
	t_coordinates	apex_ray_o_v;//the length of the apex to the origin of the ray


	float a;
	float b;
	float c;

	apex_ray_o_v = vec3_diff(ray.origin, cone.apex);

	a = pow(vec3_dot(ray.dir, cone.vector), 2) - pow(cos(10.0f * DEG2RAD), 2);
	b = 2 * ((vec3_dot(ray.dir, cone.vector) * vec3_dot(apex_ray_o_v, cone.vector)) - vec3_dot(ray.dir, apex_ray_o_v) * pow(cos(10.0f * DEG2RAD), 2));
	c = pow(vec3_dot(apex_ray_o_v, cone.vector), 2) - vec3_dot(apex_ray_o_v, apex_ray_o_v) * pow(cos(10.0f * DEG2RAD), 2);
	if (!solve_quadratic(a, b, c, dist))
		return (false);
	float	t = vec3_dot(cone.vector, vec3_diff(vec3_scalar(ray.dir, *dist), vec3_neg(apex_ray_o_v)));
	if (t <= 0)
		return (false);
	else if (t > cone.height)
	{
		t_disk	cap;
		cap.vector = cone.vector;
		cap.rgb = cone.rgb;
		cap.diameter = tan(10.0f * DEG2RAD) * cone.height * 2;
		cap.coordinates = vec3_sum(cone.apex, vec3_scalar(cone.vector, cone.height));
		return (disk_hit(ray, cap, dist));
	}
	return (true);
}

t_coordinates cone_normal(t_hit_info hit, t_cone cone)
{
	t_coordinates apex_to_point = vec3_diff(hit.coordinates, cone.apex);
	float p_len = vec3_dot(cone.vector, apex_to_point);
	if (p_len >= cone.height - 1e-4)
		return (cone.vector);
#if 0
	t_coordinates	projected_on_base = vec3_diff(hit.coordinates, vec3_scalar(cone.vector, vec3_norm(apex_to_point)));
	t_coordinates	normal = vec3_normalize(vec3_diff(projected_on_base, cone.apex));
	return (normal);
#else
	t_coordinates point_on_axis = vec3_sum(cone.apex, vec3_scalar(cone.vector, vec3_norm(apex_to_point)));
	t_coordinates normal = vec3_diff(hit.coordinates, point_on_axis);
	normal = vec3_normalize(normal);
	return (normal);
#endif
}


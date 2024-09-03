/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:01:31 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/03 18:17:30 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	cone_hit(t_ray ray, t_cone cone, float *dist)
{
	t_coordinates	apex_to_origin;//the length of the apex to the origin of the ray


//	float a;
//	float b;
//	float c;
	float	radius = (cone.diameter / 2);
//	float half_angle = atan(radius / cone.height);

//	printf("The radius is: %f\n", radius);
(void)dist;
	//printf("The half-angle is: %f\n", half_angle);

	apex_to_origin = vec3_diff(ray.origin, cone.apex);
	float projection_len = vec3_dot(apex_to_origin, cone.vector);
	printf("The projection length is: %f\n", projection_len);
	t_coordinates point_on_axis = vec3_sum(cone.apex, vec3_scalar(cone.vector, projection_len));
	float	radius_at_projection = (projection_len / cone.height) * radius;
	t_coordinates to_surface_point = vec3_diff(ray.origin, point_on_axis);
	t_coordinates surface_vector = vec3_scalar(vec3_normalize(to_surface_point), radius_at_projection);
	t_coordinates point_on_cone_surface = vec3_sum(point_on_axis, surface_vector);
	t_coordinates origin_to_cone_surface = vec3_diff(point_on_cone_surface, ray.origin);
	(void)origin_to_cone_surface;

//	printf("The vector from O to surface is: %f, %f, %f\n", origin_to_cone_surface.x, origin_to_cone_surface.y, origin_to_cone_surface.z);
/*

	a = pow(vec3_dot(ray.dir, cone.vector), 2) - pow(half_angle, 2);
	b = 2 * ((vec3_dot(ray.dir, cone.vector) * vec3_dot(apex_to_origin, cone.vector)) - vec3_dot(ray.dir, apex_to_origin) * pow(half_angle, 2));
	c = pow(vec3_dot(apex_to_origin, cone.vector), 2) - vec3_dot(apex_to_origin, apex_to_origin) * pow(half_angle, 2);
	if (!solve_quadratic(a, b, c, dist))
		return (false);
	float	t = vec3_dot(cone.vector, vec3_diff(vec3_scalar(ray.dir, *dist), vec3_neg(apex_to_origin)));
	if (t <= 0)
		return (false);
	else if (t > cone.height)
	{
		t_disk	cap;
		cap.vector = cone.vector;
		cap.rgb = cone.rgb;
		cap.diameter = tan(half_angle) * cone.height * 2;
		cap.coordinates = vec3_sum(cone.apex, vec3_scalar(cone.vector, cone.height));
		return (disk_hit(ray, cap, dist));
	}
	*/
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


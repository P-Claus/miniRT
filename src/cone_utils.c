/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:01:31 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/31 22:04:04 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <math.h>

bool	cone_hit(t_ray ray, t_cone cone, float *dist)
{
	t_coordinates	apex_ray_o_v;//the length of the apex to the origin of the ray


	cone.vector = vec3_normalize(cone.vector);
	(void)dist;
	float a;
	float b;
	float c;
	float 	t_min;
	float	t_max;

	apex_ray_o_v = vec3_diff(ray.origin, cone.apex);

	a = pow(vec3_dot(ray.dir, cone.vector), 2) - pow(cos(10.0f * DEG2RAD), 2);
	b = 2 * ((vec3_dot(ray.dir, cone.vector) * vec3_dot(apex_ray_o_v, cone.vector)) - vec3_dot(ray.dir, apex_ray_o_v) * pow(cos(10.0f * DEG2RAD), 2));
	c = pow(vec3_dot(apex_ray_o_v, cone.vector), 2) - vec3_dot(apex_ray_o_v, apex_ray_o_v) * pow(cos(10.0f * DEG2RAD), 2);

	float discriminant = b * b - 4 * a * c;

	/*
	printf("a: %f, b: %f, c:%f, discriminant: %f\n", a, b, c, discriminant);
	printf("apex_ray_o_v : %f, %f, %f\n", apex_ray_o_v.x, apex_ray_o_v.y, apex_ray_o_v.z);
	printf("cone vector: %f , %f, %f\n", cone.vector.x, cone.vector.y, cone.vector.z);
	printf("Ray origin: %f, %f, %f\n", ray.origin.x, ray.origin.y, ray.origin.z);
	*/
	if (discriminant < 0)
	{
		printf("It's false\n");
		return (false);
	}
	else
	{
		t_min = (-b - sqrt(discriminant)) / (2 * a);
		t_max = (-b + sqrt(discriminant)) / (2 * a);
		if (t_min > t_max)
		{
			float temp;
			temp = t_min;
			t_min = t_max;
			t_max = temp;
		}
	}

	if (t_min < 0 && t_max < 0)
		return (false);

	float t = (t_min < 0) ? t_max : t_min;

	/*
	t_coordinates intersection = vec3_sum(ray.origin, vec3_scalar(ray.dir, t));
	printf("Intersection at: %f\n", t);
	printf("The intersection point: %f, %f, %f\n", intersection.x, intersection.y, intersection.z);
*/	
	*dist = t;

	return (true);

}

t_coordinates cone_normal(t_hit_info hit, t_cone cone)
{
	t_coordinates apex_to_point = vec3_diff(hit.coordinates, cone.apex);
	float p_len = vec3_dot(apex_to_point, cone.vector);
	t_coordinates point_on_axis = vec3_sum(cone.apex, vec3_scalar(cone.vector, p_len));
	t_coordinates normal = vec3_diff(hit.coordinates, point_on_axis);
	normal = vec3_normalize(normal);
	return (normal);
}


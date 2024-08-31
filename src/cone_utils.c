/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:01:31 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/31 20:13:27 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <math.h>

bool	cone_hit(t_ray ray, t_cone cone, float *dist)
{
	t_coordinates	apex_ray_o_v;//the length of the apex to the origin of the ray

	(void)dist;
	float a;
	float b;
	float c;
	float 	t_min;
	float	t_max;

	apex_ray_o_v = vec3_diff(ray.origin, cone.apex);

	a = pow(vec3_dot(ray.dir, cone.vector), 2) - pow(cos(25.0f * DEG2RAD), 2);
	b = 2 * ((vec3_dot(ray.dir, cone.vector) * vec3_dot(apex_ray_o_v, cone.vector)) - vec3_dot(ray.dir, apex_ray_o_v) * pow(cos(25.0f * DEG2RAD), 2));
	c = pow(vec3_dot(apex_ray_o_v, cone.vector), 2) - vec3_dot(apex_ray_o_v, apex_ray_o_v) * pow(cos(25.0f * DEG2RAD), 2);

	float discriminant = b * b - 4 * a * c;

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

	t_coordinates intersection_1 = vec3_sum(ray.origin, vec3_scalar(ray.dir, t_min));
	t_coordinates intersection_2 = vec3_sum(ray.origin, vec3_scalar(ray.dir, t_max));

	printf("The first intersection is: %f, %f, %f\n", intersection_1.x, intersection_1.y, intersection_1.z);
	printf("The second intersection is: %f, %f, %f\n", intersection_2.x, intersection_2.y, intersection_2.z);

	return (true);

}

t_coordinates cone_normal(t_hit_info hit, t_cone cone)
{
	(void)hit;
	(void)cone;
	printf("hi mom\n");
	return ((t_coordinates){0.0, 0.0, 0.0});
}


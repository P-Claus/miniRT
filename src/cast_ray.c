/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:35:42 by efret             #+#    #+#             */
/*   Updated: 2024/09/11 15:35:49 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_hit_info	cast_ray(t_ray ray, t_scene_info scene)
{
	t_hit_info	hit;
	float		dist;
	int			i;

	hit.dist = INFINITY;
	hit.obj_index = 0;
	hit.obj_type = OBJ_NONE;
	i = 0;
	while (i < scene.nb_of_spheres)
	{
		if (sphere_hit(ray, scene.spheres[i], &dist) && dist > 0)
		{
			if (dist < hit.dist)
			{
				hit.dist = dist;
				hit.obj_index = i;
				hit.obj_type = OBJ_SPHERE;
			}
		}
		i++;
	}
	i = 0;
	while(i < scene.nb_of_planes)
	{
		if (plane_hit(ray, scene.planes[i], &dist) && dist > 0)
		{
			if (dist < hit.dist)
			{
				hit.dist = dist;
				hit.obj_index = i;
				hit.obj_type = OBJ_PLANE;
			}
		}
		i++;
	}
	i = 0;
	while (i < scene.nb_of_cylinders)
	{
		if (cylinder_hit(ray, scene.cylinders[i], &dist) && dist > 0)
		{
			if (dist < hit.dist)
			{
				hit.dist = dist;
				hit.obj_index = i;
				hit.obj_type = OBJ_CYLINDER;
			}
		}
		i++;
	}
	if (!isinf(hit.dist))
		hit.coordinates = vec3_sum(ray.origin, vec3_scalar(ray.dir, hit.dist));
	return (hit);
}

bool	cast_shadow_ray(t_ray ray, t_scene_info scene, float light_dist)
{
	float		dist;
	int			i;

	i = 0;
	while (i < scene.nb_of_spheres)
	{
		if (sphere_hit(ray, scene.spheres[i], &dist) && dist > 0 && dist < light_dist)
			return (true);
		i++;
	}
	i = 0;
	while(i < scene.nb_of_planes)
	{
		if (plane_hit(ray, scene.planes[i], &dist) && dist > 0 && dist < light_dist)
			return (true);
		i++;
	}
	i = 0;
	while (i < scene.nb_of_cylinders)
	{
		if (cylinder_hit(ray, scene.cylinders[i], &dist) && dist > 0 && dist < light_dist)
			return (true);
		i++;
	}
	return (false);
}

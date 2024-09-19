/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:35:42 by efret             #+#    #+#             */
/*   Updated: 2024/09/19 20:48:20 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	check_sphere_hits(
		t_ray ray, t_sphere *spheres, int nb_objs, t_hit_info *hit)
{
	float	dist;
	int		i;

	i = 0;
	while (i < nb_objs)
	{
		if (sphere_hit(ray, spheres[i], &dist) && dist > 0)
		{
			if (dist < hit->dist)
			{
				hit->dist = dist;
				hit->obj_index = i;
				hit->obj_type = OBJ_SPHERE;
			}
		}
		i++;
	}
}

void	check_plane_hits(
		t_ray ray, t_plane *planes, int nb_objs, t_hit_info *hit)
{
	float	dist;
	int		i;

	i = 0;
	while (i < nb_objs)
	{
		if (plane_hit(ray, planes[i], &dist) && dist > 0)
		{
			if (dist < hit->dist)
			{
				hit->dist = dist;
				hit->obj_index = i;
				hit->obj_type = OBJ_PLANE;
			}
		}
		i++;
	}
}

void	check_cylinder_hits(
		t_ray ray, t_cylinder *cylinders, int nb_objs, t_hit_info *hit)
{
	float	dist;
	int		i;

	i = 0;
	while (i < nb_objs)
	{
		if (cylinder_hit(ray, cylinders[i], &dist) && dist > 0)
		{
			if (dist < hit->dist)
			{
				hit->dist = dist;
				hit->obj_index = i;
				hit->obj_type = OBJ_CYLINDER;
			}
		}
		i++;
	}
}

void	check_cone_hits(
		t_ray ray, t_cone *cones, int nb_objs, t_hit_info *hit)
{
	float	dist;
	int		i;

	i = 0;
	while (i < nb_objs)
	{
		if (cone_hit(ray, cones[i], &dist) && dist > 0)
		{
			if (dist < hit->dist)
			{
				hit->dist = dist;
				hit->obj_index = i;
				hit->obj_type = OBJ_CONE;
			}
		}
		i++;
	}
}

t_hit_info	cast_ray(t_ray ray, t_scene_info scene)
{
	t_hit_info	hit;

	hit.dist = INFINITY;
	hit.obj_index = 0;
	hit.obj_type = OBJ_NONE;
	check_sphere_hits(ray, scene.spheres, scene.nb_of_spheres, &hit);
	check_plane_hits(ray, scene.planes, scene.nb_of_planes, &hit);
	check_cylinder_hits(ray, scene.cylinders, scene.nb_of_cylinders, &hit);
	check_cone_hits(ray, scene.cones, scene.nb_of_cones, &hit);
	if (hit.obj_type != OBJ_NONE)
		hit.coordinates = vec3_sum(ray.origin, vec3_scalar(ray.dir, hit.dist));
	return (hit);
}

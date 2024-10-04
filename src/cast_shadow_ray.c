/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_shadow_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:44:29 by efret             #+#    #+#             */
/*   Updated: 2024/10/04 15:01:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	sphere_obstruct(
		t_ray ray, t_sphere *spheres, int nb_objs, float light_dist)
{
	float	dist;
	int		i;

	i = 0;
	dist = 0;
	while (i < nb_objs)
	{
		if (sphere_hit(ray, spheres[i], &dist) && dist > 0 && dist < light_dist)
			return (true);
		i++;
	}
	return (false);
}

bool	plane_obstruct(
		t_ray ray, t_plane *planes, int nb_objs, float light_dist)
{
	float	dist;
	int		i;

	i = 0;
	dist = 0;
	while (i < nb_objs)
	{
		if (plane_hit(ray, planes[i], &dist) && dist > 0 && dist < light_dist)
			return (true);
		i++;
	}
	return (false);
}

bool	cylinder_obstruct(
		t_ray ray, t_cylinder *cylinders, int nb_objs, float light_dist)
{
	float	dist;
	int		i;

	i = 0;
	dist = 0;
	while (i < nb_objs)
	{
		if (cylinder_hit(
				ray, cylinders[i], &dist) && dist > 0 && dist < light_dist)
			return (true);
		i++;
	}
	return (false);
}

bool	cone_obstruct(
		t_ray ray, t_cone *cones, int nb_objs, float light_dist)
{
	float	dist;
	int		i;

	i = 0;
	dist = 0;
	while (i < nb_objs)
	{
		if (cone_hit(ray, cones[i], &dist) && dist > 0 && dist < light_dist)
			return (true);
		i++;
	}
	return (false);
}

bool	cast_shadow_ray(t_ray ray, t_scene_info scene, float light_dist)
{
	if (sphere_obstruct(ray, scene.spheres, scene.nb_of_spheres, light_dist))
		return (true);
	if (plane_obstruct(ray, scene.planes, scene.nb_of_planes, light_dist))
		return (true);
	if (cylinder_obstruct(
			ray, scene.cylinders, scene.nb_of_cylinders, light_dist))
		return (true);
	if (cone_obstruct(ray, scene.cones, scene.nb_of_cones, light_dist))
		return (true);
	return (false);
}

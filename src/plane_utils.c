/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:42:42 by efret             #+#    #+#             */
/*   Updated: 2024/09/20 12:53:12 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	plane_hit(t_ray ray, t_plane plane, float *dist)
{
	float			denom;
	t_coordinates	c;

	denom = vec3_dot(ray.dir, plane.vector);
	if (denom < -1e-6)
	{
		c = vec3_diff(plane.coordinates, ray.origin);
		*dist = vec3_dot(c, plane.vector) / denom;
		return (*dist > 0);
	}
	return (false);
}

void	plane_move(t_plane *plane, t_coordinates move_dir)
{
	plane->coordinates = vec3_sum(plane->coordinates, move_dir);
}

void	plane_rot(t_plane *plane, t_quat q)
{
	plane->vector = vec3_normalize(quat_rotate_point(plane->vector, q));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:55:11 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 20:26:26 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	disk_hit(t_ray ray, t_disk disk, float *dist)
{
	t_plane			plane;
	t_coordinates	p;
	t_coordinates	v;
	float			d2;

	plane = (t_plane){disk.coordinates, disk.vector, disk.rgb};
	if (plane_hit(ray, plane, dist))
	{
		p = vec3_sum(ray.origin, vec3_scalar(ray.dir, *dist));
		v = vec3_diff(p, disk.coordinates);
		d2 = vec3_dot2(v);
		return (d2 <= pow(disk.diameter / 2., 2));
	}
	return (false);
}

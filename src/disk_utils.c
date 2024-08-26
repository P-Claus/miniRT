/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:55:11 by efret             #+#    #+#             */
/*   Updated: 2024/08/26 16:06:32 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	disk_hit(t_ray ray, t_disk disk, float *dist)
{
	t_plane plane = {disk.coordinates, disk.vector, disk.rgb};
	if (plane_hit(ray, plane, dist))
	{
		t_coordinates	p = vec3_sum(ray.origin, vec3_scalar(ray.dir, *dist));
		t_coordinates	v = vec3_diff(p, disk.coordinates);
		float			d2 = vec3_dot(v, v);
		return (d2 <= pow(disk.diameter / 2., 2));
	}
	return (false);
}

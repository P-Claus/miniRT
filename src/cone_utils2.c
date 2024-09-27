/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:42:55 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 21:43:16 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_coordinates	cone_normal(t_hit_info hit, t_cone cone)
{
	t_coordinates	apex_to_point;
	float			projection_len;
	t_coordinates	normal;
	t_coordinates	cross1;
	t_coordinates	cross2;

	apex_to_point = vec3_diff(hit.coordinates, cone.apex);
	projection_len = vec3_dot(cone.vector, apex_to_point);
	if (projection_len <= 1e-4)
		normal = vec3_neg(cone.vector);
	else if (projection_len >= cone.height - 1e-4)
		normal = cone.vector;
	else
	{
		cross1 = vec3_cross(cone.vector, apex_to_point);
		cross2 = vec3_cross(cross1, apex_to_point);
		normal = vec3_normalize(cross2);
	}
	return (normal);
}

void	cone_move(t_cone *cone, t_coordinates move_dir)
{
	cone->apex = vec3_sum(cone->apex, move_dir);
}

void	cone_rot(t_cone *cone, t_quat q)
{
	cone->vector = vec3_normalize(quat_rotate_point(cone->vector, q));
}

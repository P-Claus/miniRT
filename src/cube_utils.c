/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:51:01 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/28 22:23:44 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float	get_max(float t_min_x, float t_min_y, float t_min_z)
{
	if (t_min_x >= t_min_y && t_min_x >= t_min_z)
		return (t_min_x);
	else if (t_min_y >= t_min_x && t_min_y >= t_min_z)
		return (t_min_y);
	else
		return (t_min_z);
}

float	get_min(float t_max_x, float t_max_y, float t_max_z)
{
	if (t_max_x <= t_max_y && t_max_x <= t_max_z)
		return (t_max_x);
	else if (t_max_y <= t_max_x && t_max_y <= t_max_z)
		return (t_max_y);
	else
		return (t_max_z);
}

bool	cube_hit(t_ray ray, t_cube cube, float *dist)
{
	float	t_min_x;
	float	t_max_x;
	float	t_min_y;
	float	t_max_y;
	float	t_min_z;
	float	t_max_z;
	float	temp;
	float	t_min;
	float	t_max;

	if (ray.dir.x != 0.0) //the ray is not parallel to the xplane
	{
		t_min_x = (cube.min_x - ray.origin.x) / (ray.dir.x);
		t_max_x = (cube.max_x - ray.origin.x) / (ray.dir.x);
		if (t_min_x > t_max_x)
		{
			temp = t_min_x;
			t_min_x = t_max_x;
			t_max_x = temp;
		}
	}
	//the ray is parallel to the x plane
	else
	{
		if (ray.origin.x < cube.min_x || ray.origin.x > cube.max_x)
			return (false);
		t_min_x = -INFINITY;
		t_max_x = INFINITY;
	}
	if (ray.dir.y != 0.0)
	{
		t_min_y = (cube.min_y - ray.origin.y) / (ray.dir.y);
		t_max_y = (cube.max_y - ray.origin.y) / (ray.dir.y);
		if (t_min_y > t_max_y)
		{
			temp = t_min_y;
			t_min_y = t_max_y;
			t_max_y = temp;
		}
	}
	else
	{
		if (ray.origin.y < cube.min_y || ray.origin.y > cube.max_y)
			return (false);
		t_min_y = -INFINITY;
		t_max_y = INFINITY;
	}
	if (ray.dir.z != 0.0)
	{
		t_min_z = (cube.min_z - ray.origin.z) / (ray.dir.z);
		t_max_z = (cube.max_z - ray.origin.z) / (ray.dir.z);
		if (t_min_z > t_max_z)
		{
			temp = t_min_z;
			t_min_z = t_max_z;
			t_max_z = temp;
		}
	}
	else
	{
		if (ray.origin.z < cube.min_z || ray.origin.z > cube.max_z)
			return (false);
		t_min_z = -INFINITY;
		t_max_z = INFINITY;
	}
	//calculate entry and exit points
	t_min = get_max(t_min_x, t_min_y, t_min_z);
	t_max = get_min(t_max_x, t_max_y, t_max_z);

	if (t_min > t_max || t_max < 0.0)
		return (false);

	*dist = t_min > 0.0f ? t_min : t_max;

	return (true);
}

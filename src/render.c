/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:36:41 by efret             #+#    #+#             */
/*   Updated: 2024/09/07 19:13:20 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	per_pixel(t_mlx_data *data, t_ui_viewport ui, t_pixel_coord p);

void	render(t_mlx_data *data, t_ui_viewport ui)
{
	t_pixel_coord	p;

	p.y = 0;
	while (p.y < ui.size.y)
	{
		p.x = 0;
		while (p.x < ui.size.x)
		{
			fast_pixel_put(ui, p, per_pixel(data, ui, p));
			p.x++;
		}
		p.y++;
	}
	mlx_put_image_to_window(data->mlx, ui.window, ui.render.img, 0, 0);
	errno = 0;
}

void	set_pixels(t_ui_viewport ui, int color, t_pixel_coord p, t_pixel_coord dp)
{
	int				j;
	int				i;

	p.x -= dp.x / 2;
	p.y -= dp.y / 2;
	j = 0;
	while (j < dp.y)
	{
		i = 0;
		while (i < dp.x)
		{
			fast_pixel_put(ui, (t_pixel_coord){p.x + i, p.y + j}, color);
			i++;
		}
		j++;
	}
}

void	render_low_res(t_mlx_data *data, t_ui_viewport ui, int dx, int dy)
{
	t_pixel_coord	p;
	int				pixel_color;

	if (dx < 1 || dy < 1)
		return (render_low_res(data, ui, 2, 2));
	p.y = dy / 2;
	while (p.y < ui.size.y)
	{
		p.x = dx / 2;
		while (p.x < ui.size.x)
		{
			pixel_color = per_pixel(data, ui, p);
			set_pixels(ui, pixel_color, p, (t_pixel_coord){dx, dy});
			p.x += dx;
		}
		p.y += dy;
	}
	mlx_put_image_to_window(data->mlx, ui.window, ui.render.img, 0, 0);
	errno = 0;
}

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
	i = 0;
	while(i < scene.nb_of_cones)
	{
		if (cone_hit(ray, scene.cones[i], &dist) && dist > 0)
		{
			if (dist < hit.dist)
			{
				hit.dist = dist;
				hit.obj_index = i;
				hit.obj_type = OBJ_CONE;
			}
		}
		i++;
	}
	if (hit.obj_type != OBJ_NONE)
		hit.coordinates = vec3_sum(ray.origin, vec3_scalar(ray.dir, hit.dist));
	return (hit);
}

t_rgb	color_from_hit(t_hit_info hit, t_scene_info scene)
{
	t_rgb			color;
	t_coordinates	hit_normal;
	t_coordinates	light_dir;
	float	light;

	light_dir = vec3_normalize(vec3_diff(scene.light.coordinates, hit.coordinates));
	if (hit.obj_type == OBJ_SPHERE)
	{
		color = scene.spheres[hit.obj_index].rgb;
		hit_normal = sphere_normal(hit, scene.spheres[hit.obj_index]);
	}
	else if (hit.obj_type == OBJ_PLANE)
	{
		color = scene.planes[hit.obj_index].rgb;
		hit_normal = scene.planes[hit.obj_index].vector;
	}
	else if (hit.obj_type == OBJ_CYLINDER)
	{
		color = scene.cylinders[hit.obj_index].rgb;
		hit_normal = cylinder_normal(hit, scene.cylinders[hit.obj_index]);
	}
	else if (hit.obj_type == OBJ_CONE)
	{
		color = scene.cones[hit.obj_index].rgb;
		hit_normal = cone_normal(hit, scene.cones[hit.obj_index]);
	}
	else
		return ((t_rgb){0, 0, 0,});
	light = fmax(vec3_dot(hit_normal,light_dir), 0.);
	color = color_scalar(color, light);
	return (color);
}

t_ray	calc_ray(t_camera camera, t_ui_viewport ui, t_pixel_coord p)
{
	t_coordinates	ray_dir_screen;
	t_ray			ray;
	t_pixel_uv		uv;
	float			scale;

	scale = tan(DEG2RAD * camera.fov * 0.5);
	uv = (t_pixel_uv){(p.x + 0.5) / ui.size.x, (ui.size.y - p.y - 0.5) / ui.size.y};
	uv.x = (uv.x * 2. - 1.) * scale * ui.aspect;
	uv.y = (uv.y * 2. - 1.) * scale;
	ray.origin = camera.coordinates;
	ray_dir_screen = (t_coordinates){uv.x, uv.y, 1.};
	ray.dir.x = vec3_dot(camera.right, ray_dir_screen);
	ray.dir.y = vec3_dot(camera.up, ray_dir_screen);
	ray.dir.z = vec3_dot(camera.vector, ray_dir_screen);
	ray.dir = vec3_normalize(ray.dir);
	return (ray);
}

int	per_pixel(t_mlx_data *data, t_ui_viewport ui, t_pixel_coord p)
{
	t_ray	ray;

	ray = calc_ray(data->scene.camera, ui, p);

	t_hit_info	hit = cast_ray(ray, data->scene);
	if (hit.obj_type == OBJ_NONE)
		return (0x0087CEEB);

	t_rgb color_coord = color_from_hit(hit, data->scene);
	return (color_to_int(color_coord));
}

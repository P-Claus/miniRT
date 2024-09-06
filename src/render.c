/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:36:41 by efret             #+#    #+#             */
/*   Updated: 2024/09/06 15:10:20 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	per_pixel(t_mlx_data *data, t_pixel_coord p);

void	render(t_mlx_data *data)
{
	t_pixel_coord	p;

	p.y = 0;
	while (p.y < data->height)
	{
		p.x = 0;
		while (p.x < data->width)
		{
			fast_pixel_put(data, p, per_pixel(data, p));
			p.x++;
		}
		p.y++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->render.img, 0, 0);
	errno = 0;
}

void	set_pixels(t_mlx_data *data, int color, t_pixel_coord p, t_pixel_coord dp)
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
			fast_pixel_put(data, (t_pixel_coord){p.x + i, p.y + j}, color);
			i++;
		}
		j++;
	}
}

void	render_low_res(t_mlx_data *data, int dx, int dy)
{
	t_pixel_coord	p;
	int				pixel_color;

	if (dx < 1 || dy < 1)
		return (render_low_res(data, 2, 2));
	p.y = dy / 2;
	while (p.y < data->height)
	{
		p.x = dx / 2;
		while (p.x < data->width)
		{
			pixel_color = per_pixel(data, p);
			set_pixels(data, pixel_color, p, (t_pixel_coord){dx, dy});
			p.x += dx;
		}
		p.y += dy;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->render.img, 0, 0);
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

t_rgb	get_obj_color(t_hit_info hit, t_scene_info scene)
{
	if (hit.obj_type == OBJ_SPHERE)
		return (scene.spheres[hit.obj_index].rgb);
	else if (hit.obj_type == OBJ_PLANE)
		return (scene.planes[hit.obj_index].rgb);
	else if (hit.obj_type == OBJ_CYLINDER)
		return (scene.cylinders[hit.obj_index].rgb);
	return ((t_rgb){0, 0, 0,});
}

t_coordinates	get_obj_normal(t_hit_info hit, t_scene_info scene)
{
	if (hit.obj_type == OBJ_SPHERE)
		return (sphere_normal(hit, scene.spheres[hit.obj_index]));
	else if (hit.obj_type == OBJ_PLANE)
		return (scene.planes[hit.obj_index].vector);
	else if (hit.obj_type == OBJ_CYLINDER)
		return (cylinder_normal(hit, scene.cylinders[hit.obj_index]));
	return ((t_coordinates){0, 0, 0,});
}

t_rgb	phong_shading(t_ray ray, t_hit_info hit, t_scene_info scene)
{
	float light_dist2 = vec3_dot2(vec3_diff(scene.light.coordinates, hit.coordinates));

	t_rgb ambient = {0};
	t_rgb specular = {0};
	t_rgb diffuse = {0};

	/* material has these attributes so maybe as a struct? */
	/* These are empirical, so no real world equivalent and have to be changed to what look you want to achieve */
	t_rgb obj_color = get_obj_color(hit, scene);
	float k_s = 0.9; /* how much does specular reflection contribute ? */
	float alpha = 8; /* how spread out is the specular reflection ? */
	float k_d = 1; /* how much does diffuse reflection contribute ? */
	float k_a = 0.05; /* how much does ambient lighting contribute ? */

	/* each light has these attributes defining their intensities for diffuse and specular reflection */
#if 1
	/* Should include inverse square law */
	t_rgb i_d = color_scalar(scene.light.rgb, scene.light.brightness / (4 * M_PI * light_dist2));
#else
	/* Ignore inverse square law */
	t_rgb i_d = color_scalar(scene.light.rgb, scene.light.brightness);
#endif
	t_rgb i_s = i_d; /* could be a different value, but for simplicity make it the same as diffuse */

	/* normalized vectors */
	t_coordinates light_dir = vec3_normalize(vec3_diff(scene.light.coordinates, hit.coordinates));
	t_coordinates hit_normal = get_obj_normal(hit, scene);
	t_coordinates reflect_dir = vec3_normalize(vec3_diff(vec3_scalar(hit_normal, 2 * vec3_dot(light_dir, hit_normal)), light_dir));
	t_coordinates view_dir = vec3_neg(ray.dir);

	/* PHONG reflection model */
	/* Ip = k_a * i_a + sum_lights(k_d * dot(light_dir, hit_normal) * i_d + k_s * dot(reflect_dir, view_dir) ^ alpha * i_s) */

	/* Ambient light */
	ambient = color_hadamard(obj_color, color_scalar(scene.a_lighting.rgb, scene.a_lighting.ambient_lighting));

# if 1
	/* Don't cast shadow ray if light direction is not in the same hemisphere as the surface normal */
	if (!(vec3_dot(hit_normal, light_dir) < 0 || cast_shadow_ray((t_ray){hit.coordinates, light_dir}, scene, sqrt(light_dist2))))
#else
	/* use a bias to reduce shadow acne */
	if (!cast_shadow_ray((t_ray){vec3_sum(hit.coordinates, vec3_scalar(hit_normal, 1e-4)), light_dir}, scene, sqrt(light_dist2)))
#endif
	{
		diffuse = color_hadamard(obj_color, color_scalar(i_d, fmax(vec3_dot(light_dir, hit_normal), 0.0f)));
		specular = color_scalar(i_s, pow(fmax(vec3_dot(reflect_dir, view_dir), 0.0f), alpha));
	}
	t_rgb hit_color;
	hit_color = color_add(color_scalar(ambient, k_a), color_add(color_scalar(diffuse, k_d), color_scalar(specular, k_s)));
	return (hit_color);
}

t_ray	calc_ray(t_camera camera, t_mlx_data *data, t_pixel_coord p)
{
	t_coordinates	ray_dir_screen;
	t_ray			ray;
	t_pixel_uv		uv;
	float			scale;

	scale = tan(DEG2RAD * camera.fov * 0.5);
	uv = (t_pixel_uv){(p.x + 0.5) / data->width, (data->height - p.y - 0.5) / data->height};
	uv.x = (uv.x * 2. - 1.) * scale * data->aspect;
	uv.y = (uv.y * 2. - 1.) * scale;
	ray.origin = camera.coordinates;
	ray_dir_screen = (t_coordinates){uv.x, uv.y, 1.};
	ray.dir.x = vec3_dot(camera.right, ray_dir_screen);
	ray.dir.y = vec3_dot(camera.up, ray_dir_screen);
	ray.dir.z = vec3_dot(camera.vector, ray_dir_screen);
	ray.dir = vec3_normalize(ray.dir);
	return (ray);
}

int	per_pixel(t_mlx_data *data, t_pixel_coord p)
{
	t_ray	ray;

	ray = calc_ray(data->scene.camera, data, p);

	t_hit_info	hit = cast_ray(ray, data->scene);
	if (isinf(hit.dist))
		return (0);

	t_rgb color_coord = phong_shading(ray, hit, data->scene);
	return (color_to_int(color_coord));
}

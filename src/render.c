/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:36:41 by efret             #+#    #+#             */
/*   Updated: 2024/08/30 15:55:07 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	per_pixel(t_mlx_data *data, t_pixel_coord p);

void	render(t_mlx_data *data)
{
	struct timeval	start;
	struct timeval	end;
	t_pixel_coord	p;

	gettimeofday(&start, NULL);
	p.y = 0;
	while (p.y < data->heigth)
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
	gettimeofday(&end, NULL);
	printf("frametime: %.3f ms\n", frame_time(start, end));
}

t_hit_info	cast_ray(t_ray ray, t_scene_info scene)
{
	t_hit_info	hit;
	float		dist;
	int			i;
	t_cube		cube;

	cube.max_x = 15;
	cube.max_y = 15;
	cube.max_z = 15;
	cube.min_x = -20;
	cube.min_y = -20;
	cube.min_z = -20;
	cube.vector.x = 0.0;
	cube.vector.y = 1.0;
	cube.vector.z = 0.0;

	hit.dist = INFINITY;
	hit.obj_index = 0;
	hit.obj_type = OBJ_NONE;
	i = 0;
	if (cube_hit(ray, &cube, &dist, &hit) && dist > 0)
	{
		if (dist < hit.dist)
		{
			hit.dist = dist;
			hit.obj_index = 0;
			hit.obj_type = OBJ_CUBE;
		}
	}
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

t_rgb	color_from_hit(t_hit_info hit, t_scene_info scene)
{
	t_rgb			color;
	(void)scene;
	t_coordinates	hit_normal = {0.0, 0.0, 0.0};
	t_coordinates	light_dir;
	float	light;
	light_dir = vec3_normalize(vec3_diff(scene.light.coordinates, hit.coordinates));
/*
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
	*/
	if (hit.obj_type == OBJ_CUBE)
	{

		if (fabs(hit.coordinates.x + 20) < 1e-6)
			hit_normal = (t_coordinates){-1.0, 0.0, 0.0};
		else if (fabs(hit.coordinates.x - 15) < EPSILON)
			hit_normal = (t_coordinates){1.0, 0.0, 0.0};
		else if (fabs(hit.coordinates.y + 20) < EPSILON)
			hit_normal = (t_coordinates){0.0, -1.0, 0.0};
		else if (fabs(hit.coordinates.y - 15) < EPSILON)
			hit_normal = (t_coordinates){0.0, 1.0, 0.0};
		else if (fabs(hit.coordinates.z + 20) < EPSILON)
			hit_normal = (t_coordinates){0.0, 0.0, -1.0};
		else if (fabs(hit.coordinates.z - 15) < EPSILON)
			hit_normal = (t_coordinates){0.0, 0.0, 1.0};
	
		color.r = fabs(hit_normal.x);
		color.g = fabs(hit_normal.y);
		color.b = fabs(hit_normal.z);
	}
	else
		return ((t_rgb){0, 255, 0,});
	light = fmax(vec3_dot(hit_normal,light_dir), 0.);
	color = color_scalar(color, light);
	return (color);
}

t_ray calc_ray(t_pixel_uv uv)
{
	t_ray ray;
	t_coordinates ray_dir_screen;

	ray_dir_screen = (t_coordinates){uv.x, uv.y, 1};

	ray.origin = (t_coordinates){100, 0, 0};
	ray.dir.x = vec3_dot((t_coordinates){0, 0, -1}, ray_dir_screen);
	ray.dir.y = vec3_dot((t_coordinates){0, 1, 0}, ray_dir_screen);
	ray.dir.z = vec3_dot((t_coordinates){1, 0, 0}, ray_dir_screen);

	ray.dir = vec3_normalize(ray.dir);
	return (ray);
}

#if 1
/* split up the function to call other functions setting up the framework how I think we'll up up with. */
int	per_pixel(t_mlx_data *data, t_pixel_coord p)
{
	float	fov = 65;
	float	scale = tan(DEG2RAD * fov * 0.5);

	t_pixel_uv uv = (t_pixel_uv){(float)p.x / data->width, (float)(data->heigth - p.y) / data->heigth};
	uv.x = (uv.x * 2. - 1.) * scale * data->aspect;
	uv.y = (uv.y * 2. - 1.) * scale;
	t_ray	ray = calc_ray(uv);

	t_hit_info	hit = cast_ray(ray, data->scene);
	if (isinf(hit.dist))
		return (0);

	t_rgb color_coord = color_from_hit(hit, data->scene);
	return (color_to_int(color_coord));
}
#elif 1
/* Same as the next block, but the scene info is used.
 * !!!NOTE IMPORTANT ONLY USE THIS WITH "one_sphere.rt" FILE */
int	per_pixel(t_mlx_data *data, t_pixel_coord p)
{
	float	fov = 65;
	float	scale = tan(DEG2RAD * fov * 0.5);

	t_pixel_uv uv = (t_pixel_uv){(float)p.x / data->width, (float)(data->heigth - p.y) / data->heigth};
	uv.x = (uv.x * 2. - 1.) * scale * data->aspect;
	uv.y = (uv.y * 2. - 1.) * scale;
	t_coordinates	ray_origin = {0., 0., 100.};
	t_coordinates	ray_dir = {uv.x, uv.y, -1.}; // -1. for the z component to set the screen 1 unit in front of us in the world space. The z axis point towards the screen.
	//ray_dir = vec3_normalize(ray_dir);
	// should normalize (should normalize every direction vector really) but not really necessary to get the distance t
	t_coordinates	sphere_origin = data->scene.spheres[0].coordinates;
	float			sphere_radius = data->scene.spheres[0].diameter / 2.;
	t_coordinates	sphere_color = {
		data->scene.spheres[0].rgb.r,
		data->scene.spheres[0].rgb.g,
		data->scene.spheres[0].rgb.b};

	t_coordinates	L = vec3_diff(ray_origin, sphere_origin);

	float	a = vec3_dot(ray_dir, ray_dir);
	float	b = 2. * vec3_dot(L, ray_dir);
	float	c = vec3_dot(L, L) - pow(sphere_radius, 2);

	float	discr = b * b - 4 * a * c;
	float	dist;
	if (discr < 0)
		return (0);
	else if (discr == 0)
		dist = -0.5 * b / a;
	else
		dist = -0.5 * (b - sqrt(discr)) / a;
	t_coordinates	hit = vec3_sum(ray_origin, vec3_scalar(ray_dir, dist));
	t_coordinates	hit_normal = vec3_normalize(vec3_diff(hit, sphere_origin));

	t_coordinates	light_dir = {-1., -1., -0.5};
	light_dir = vec3_normalize(light_dir);

	float	light = fmax(vec3_dot(hit_normal, vec3_neg(light_dir)), 0.);

	t_coordinates	color_coord = vec3_scalar(sphere_color, light);

	color_coord = vec3_scalar(color_coord, 0xFF);
	int	color = 0x00000000 | ((int)color_coord.x << 16) | ((int)color_coord.y << 8) | (int)color_coord.z;
	return (color);
}
#elif 1
/* Same as the next block, but the sphere origin can be moved and a couple of non-necessary calculations are removed.
 * Also camera fov is now considered. */
int	per_pixel(t_mlx_data *data, t_pixel_coord p)
{
	float	fov = 65;
	float	scale = tan(DEG2RAD * fov * 0.5);

	t_pixel_uv uv = (t_pixel_uv){(float)p.x / data->width, (float)(data->heigth - p.y) / data->heigth};
	uv.x = (uv.x * 2. - 1.) * scale * data->aspect;
	uv.y = (uv.y * 2. - 1.) * scale;
	t_coordinates	ray_origin = {0., 0., 100.};
	t_coordinates	ray_dir = {uv.x, uv.y, -1.}; // -1. for the z component to set the screen 1 unit in front of us in the world space. The z axis point towards the screen.
	//ray_dir = vec3_normalize(ray_dir);
	// should normalize (should normalize every direction vector really) but not really necessary to get the distance t
	t_coordinates	sphere_origin = {0., 0., 0.};
	float			sphere_radius = 35.;

	t_coordinates	L = vec3_diff(ray_origin, sphere_origin);

	float	a = vec3_dot(ray_dir, ray_dir);
	float	b = 2. * vec3_dot(L, ray_dir);
	float	c = vec3_dot(L, L) - pow(sphere_radius, 2);

	float	discr = b * b - 4 * a * c;
	float	dist;
	if (discr < 0)
		return (0);
	else if (discr == 0)
		dist= -0.5 * b / a;
	else
		dist = -0.5 * (b - sqrt(discr)) / a;
	t_coordinates	hit = vec3_sum(ray_origin, vec3_scalar(ray_dir, dist));
	t_coordinates	hit_normal = vec3_normalize(vec3_diff(hit, sphere_origin));

	t_coordinates	light_dir = {-1., -1., -0.5};
	light_dir = vec3_normalize(light_dir);

	float	light = fmax(vec3_dot(hit_normal, vec3_neg(light_dir)), 0.);

#if 0
	t_coordinates	hit_normal_uv = vec3_sum(vec3_scalar(hit_normal, 0.5), (t_coordinates){0.5, 0.5, 0.5});
	t_coordinates	sphere_color = vec3_scalar(hit_normal_uv, 255);
#else
	t_coordinates	sphere_color = {0., 255., 0.};
#endif

	t_coordinates	color_coord = vec3_scalar(sphere_color, light);

	vec3_scalar(color_coord, light);
	int	color = 0x00000000 | ((int)color_coord.x << 16) | ((int)color_coord.y << 8) | (int)color_coord.z;
	return (color);
}
#elif 1
/* map color to a shaded color of a sphere based on the dot between some light direction and the normal of the sphere hitpoint.
 * This results in the most basic light shading of a single sphere and a single light direction. */
int	per_pixel(t_mlx_data *data, t_pixel_coord p)
{
	t_pixel_uv uv = (t_pixel_uv){(float)p.x / data->width, (float)(data->heigth - p.y) / data->heigth};
	uv.x = (uv.x * 2. - 1.) * data->aspect;
	uv.y = uv.y * 2. - 1.;
	t_coordinates	ray_origin = {0., 0., 100.};
	t_coordinates	ray_dir = {uv.x, uv.y, -1.}; // -1. for the z component to set the screen 1 unit in front of us in the world space. The z axis point towards the screen.
	//ray_dir = vec3_normalize(ray_dir);
	// should normalize (should normalize every direction vector really) but not really necessary to get the distance t
	t_coordinates	sphere_origin = {0., 0., 0.};
	float			sphere_radius = 35.;

	float	a = vec3_dot(ray_dir, ray_dir);
	float	b = 2. * vec3_dot(ray_origin, ray_dir);
	float	c = vec3_dot(ray_origin, ray_origin) - pow(sphere_radius, 2);

	float	discr = b * b - 4 * a * c;
	float	t[2] = {NAN, NAN};
	if (discr < 0)
		return (0);
	else if (discr == 0)
		t[0] = t[1] = -0.5 * b / a;
	else
	{
		float	q;
		if (b > 0)
			q = -0.5 * (b + sqrt(discr));
		else
			q = -0.5 * (b - sqrt(discr));
		t[0] = q / a;
		t[1] = c / q;
	}
	float dist = fmin(t[0], t[1]);
	t_coordinates	hit = vec3_sum(ray_origin, vec3_scalar(ray_dir, dist));
	t_coordinates	hit_normal = vec3_normalize(vec3_sum(hit, vec3_scalar(sphere_origin, -1.)));

	t_coordinates	light_dir = {-1., -1., -0.5};
	light_dir = vec3_normalize(light_dir);

	float	light = fmax(vec3_dot(hit_normal, vec3_scalar(light_dir, -1.)), 0.);

#if 0
	t_coordinates	hit_normal_uv = vec3_sum(vec3_scalar(hit_normal, 0.5), (t_coordinates){0.5, 0.5, 0.5});
	t_coordinates	sphere_color = vec3_scalar(hit_normal_uv, 255);
#else
	t_coordinates	sphere_color = {0., 255., 0.};
#endif

	t_coordinates	color_coord = vec3_scalar(sphere_color, light);

	vec3_scalar(color_coord, light);
	int	color = 0x00000000 | ((int)color_coord.x << 16) | ((int)color_coord.y << 8) | (int)color_coord.z;
	return (color);
}
#elif 1
/* map color to the normal vector of a sphere */
int	per_pixel(t_mlx_data *data, t_pixel_coord p)
{
	t_pixel_uv uv = (t_pixel_uv){(float)p.x / data->width, (float)(data->heigth - p.y) / data->heigth};
	uv.x = (uv.x * 2. - 1.) * data->aspect;
	uv.y = uv.y * 2. - 1.;
	t_coordinates	ray_origin = {0., 0., 100.};
	t_coordinates	ray_dir = {uv.x, uv.y, -1.}; // -1. for the z component to set the screen 1 unit in front of us in the world space. The z axis point towards the screen.
	//ray_dir = vec3_normalize(ray_dir);
	// should normalize (should normalize every direction vector really) but not really necessary to get the distance t
	t_coordinates	sphere_origin = {0., 0., 0.};
	float			sphere_radius = 35.;

	float	a = vec3_dot(ray_dir, ray_dir);
	float	b = 2. * vec3_dot(ray_origin, ray_dir);
	float	c = vec3_dot(ray_origin, ray_origin) - pow(sphere_radius, 2);

	float	discr = b * b - 4 * a * c;
	float	t[2] = {NAN, NAN};
	if (discr < 0)
		return (0);
	else if (discr == 0)
		t[0] = t[1] = -0.5 * b / a;
	else
	{
		float	q;
		if (b > 0)
			q = -0.5 * (b + sqrt(discr));
		else
			q = -0.5 * (b - sqrt(discr));
		t[0] = q / a;
		t[1] = c / q;
	}
	float dist = fmin(t[0], t[1]);
	t_coordinates	hit = vec3_sum(ray_origin, vec3_scalar(ray_dir, dist));
	t_coordinates	hit_normal = vec3_normalize(vec3_sum(hit, vec3_scalar(sphere_origin, -1.)));
	hit_normal = vec3_sum(vec3_scalar(hit_normal, 0.5), (t_coordinates){0.5, 0.5, 0.5});
	t_coordinates	color_coord = vec3_scalar(hit_normal, 255);
	int	color = 0x00000000 | ((int)color_coord.x << 16) | ((int)color_coord.y << 8) | (int)color_coord.z;
	return (color);
}
#elif 1
/* map grayscale color to hit distance to a sphere using a more correct method to find the solutions.
 * This method is more accurate because the floating point math has the same sign by calculating a variable q. */
int	per_pixel(t_mlx_data *data, t_pixel_coord p)
{
	t_pixel_uv uv = (t_pixel_uv){(float)p.x / data->width, (float)(data->heigth - p.y) / data->heigth};
	uv.x = (uv.x * 2. - 1.) * data->aspect;
	uv.y = uv.y * 2. - 1.;
	t_coordinates	ray_origin = {0., 0., 100.};
	t_coordinates	ray_dir = {uv.x, uv.y, -1.}; // -1. for the z component to set the screen 1 unit in front of us in the world space. The z axis point towards the screen.
	//ray_dir = vec3_normalize(ray_dir);
	// should normalize (should normalize every direction vector really) but not really necessary to get the distance t
	//t_coordinates	sphere_origin = {0., 0., 0.};
	float			sphere_radius = 35.;

	// hit between a ray and sphere found by solving for t
	// (d.x^2 + d.y^2 + d.z^2)t^2 + 2(o.x*d.x + o.y*d.y + o.z*d.z)t + (o.x^2 + o.y^2 + o.z^2 - r^2) = 0
	// where:
	// o is ray origin
	// d is ray direction
	// r is sphere radius
	// t is the hit distance
	//
	// this is a quadratic equation at^2 + bt + c = 0
	// the kind of hit can be described by the determinant D = b^2 - 4ac
	// D < 0 : no hit
	// D = 0 : ray just touches the sphere, 1 point
	// D > 0 : ray hits the sphere 2 times, we will need the closer one I think
	//
	// solution for t is then t = (-b +- sqrt(D)) / (2a)

	float	a = vec3_dot(ray_dir, ray_dir);
	float	b = 2. * vec3_dot(ray_origin, ray_dir);
	float	c = vec3_dot(ray_origin, ray_origin) - pow(sphere_radius, 2);

	float	discr = b * b - 4 * a * c;
	float	t[2] = {NAN, NAN};
	if (discr < 0)
		return (0);
	else if (discr == 0)
		t[0] = t[1] = -0.5 * b / a;
	else
	{
		float	q;
		if (b > 0)
			q = -0.5 * (b + sqrt(discr));
		else
			q = -0.5 * (b - sqrt(discr));
		t[0] = q / a;
		t[1] = c / q;
	}
	float dist = fmin(t[0], t[1]);
	float max_dist = 100.;
	int color = 0xFF - (int)((fmin(dist, max_dist)) * 255. / max_dist);
	return (color | (color << 8) | (color << 16));
}
#elif 1
/* Map grayscale color to distance to hitpoint to a sphere */
int	per_pixel(t_mlx_data *data, t_pixel_coord p)
{
	t_pixel_uv uv = (t_pixel_uv){(float)p.x / data->width, (float)(data->heigth - p.y) / data->heigth};
	uv.x = (uv.x * 2. - 1.) * data->aspect;
	uv.y = uv.y * 2. - 1.;
	t_coordinates	ray_origin = {0., 0., 100.};
	t_coordinates	ray_dir = {uv.x, uv.y, -1.}; // -1. for the z component to set the screen 1 unit in front of us in the world space. The z axis point towards the screen.
	ray_dir = vec3_normalize(ray_dir);
	// should normalize (should normalize every direction vector really)
	//t_coordinates	sphere_origin = {0., 0., 0.};
	float			sphere_radius = 30;

	// hit between a ray and sphere found by solving for t
	// (d.x^2 + d.y^2 + d.z^2)t^2 + 2(o.x*d.x + o.y*d.y + o.z*d.z)t + (o.x^2 + o.y^2 + o.z^2 - r^2) = 0
	// where:
	// o is ray origin
	// d is ray direction
	// r is sphere radius
	// t is the hit distance
	//
	// this is a quadratic equation at^2 + bt + c = 0
	// the kind of hit can be described by the determinant D = b^2 - 4ac
	// D < 0 : no hit
	// D = 0 : ray just touches the sphere, 1 point
	// D > 0 : ray hits the sphere 2 times, we will need the closer one I think
	//
	// solution for t is then t = (-b +- sqrt(D)) / (2a)

	float a = vec3_dot(ray_dir, ray_dir);
	float b = 2. * vec3_dot(ray_origin, ray_dir);
	float c = vec3_dot(ray_origin, ray_origin) - pow(sphere_radius, 2);

	float det = b * b - 4 * a * c;

	if (det >= 0)
	{
		float t[2] = {(-b + sqrt(det)) / (2 * a), (-b - sqrt(det)) / (2 * a)};
		float dist = fmin(t[0], t[1]);
		float max_dist = 100.;
		int c = 0xFF - (int)((fmin(dist, max_dist)) * 255. / max_dist);
		return (c | (c << 8) | (c << 16));
	}
	return (0);
}
#else
/* Just map the red and green channels to the uv coords */
int	per_pixel(t_mlx_data *data, t_pixel_coord p)
{
	t_pixel_uv uv = (t_pixel_uv){(float)p.x / data->width, (float)(data->heigth - p.y) / data->heigth};
	uv.x = uv.x * 2. - 1.;
	uv.y = uv.y * 2. - 1.;
	int r = (int)(uv.x * 255.0f);
	int g = (int)(uv.y * 255.0f);
	r = r < 0 ? 0 : r;
	g = g < 0 ? 0 : g;
	return (0x00000000 | (g << 8) | (r << 16));
}
#endif

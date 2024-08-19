/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:36:41 by efret             #+#    #+#             */
/*   Updated: 2024/08/19 20:54:47 by efret            ###   ########.fr       */
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

// I know all the scene things are inside the data, for now I've just done this to test the very first step of understanding ray tracing.
#if 1
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

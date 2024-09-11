/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:36:41 by efret             #+#    #+#             */
/*   Updated: 2024/09/11 15:45:23 by efret            ###   ########.fr       */
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

void	set_pixels(
		t_mlx_data *data, int color, t_pixel_coord p, t_pixel_coord dp)
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

t_ray	calc_ray(t_camera camera, t_mlx_data *data, t_pixel_coord p)
{
	t_coordinates	ray_dir_screen;
	t_ray			ray;
	t_pixel_uv		uv;
	float			scale;

	scale = tan(DEG2RAD * camera.fov * 0.5);
	uv = (t_pixel_uv){(p.x + 0.5) / data->width,
		(data->height - p.y - 0.5) / data->height};
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
	t_ray		ray;
	t_hit_info	hit;
	t_rgb		color_coord;

	ray = calc_ray(data->scene.camera, data, p);
	hit = cast_ray(ray, data->scene);
	if (isinf(hit.dist))
		return (0);
	color_coord = phong_shading(ray, hit, data->scene);
	return (color_to_int(color_coord));
}

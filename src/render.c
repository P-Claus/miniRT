/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:36:41 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 20:49:16 by efret            ###   ########.fr       */
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
	mlx_put_image_to_window(data->mlx, data->mlx_win, ui.render.img, ui.pos.x, ui.pos.y);
	errno = 0;
}

void	set_pixels(t_ui_viewport ui, int color, t_pixel_coord p, t_pixel_coord dp)
{
	int				j;
	int				i;

	p.x -= dp.x / 2;
	p.y -= dp.y / 2;
	j = 0;
	while (j < dp.y && p.y + j < ui.size.y)
	{
		i = 0;
		while (i < dp.x && p.x + i < ui.size.x)
		{
			fast_pixel_put(ui, (t_pixel_coord){p.x + i, p.y + j}, color);
			i++;
		}
		j++;
	}
}

void	render_low_res(t_mlx_data *data, t_ui_viewport ui, int lvl)
{
	t_pixel_coord	p;
	int				pixel_color;

	if (lvl < 1)
		return (render_low_res(data, ui, 2));
	p.y = lvl / 2;
	while (p.y < ui.size.y)
	{
		p.x = lvl / 2;
		while (p.x < ui.size.x)
		{
			pixel_color = per_pixel(data, ui, p);
			set_pixels(ui, pixel_color, p, (t_pixel_coord){lvl, lvl});
			p.x += lvl;
		}
		p.y += lvl;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, ui.render.img, ui.pos.x, ui.pos.y);
	errno = 0;
}

t_ray	calc_ray(t_camera camera, t_ui_viewport ui, t_pixel_coord p)
{
	t_coordinates	ray_dir_screen;
	t_ray			ray;
	t_pixel_uv		uv;
	float			scale;

	scale = tan(DEG2RAD * camera.fov * 0.5);
	uv = (t_pixel_uv){(p.x + 0.5) / ui.size.x,
		(ui.size.y - p.y - 0.5) / ui.size.y};
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
	t_ray		ray;
	t_hit_info	hit;
	t_rgb		color_coord;

	ray = calc_ray(data->scene.camera, ui, p);
	hit = cast_ray(ray, data->scene);
	if (hit.obj_type == OBJ_NONE)
		return (0x0087CEEB);
	color_coord = phong_shading(ray, hit, data->scene);
	return (color_to_int(color_coord, data->gamma_type));
}

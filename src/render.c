/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:36:41 by efret             #+#    #+#             */
/*   Updated: 2024/08/19 15:26:27 by efret            ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:36:41 by efret             #+#    #+#             */
/*   Updated: 2024/08/19 14:30:44 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	per_pixel(t_mlx_data *data, t_pixel_coord p);

void	render(t_mlx_data *data)
{
	struct timeval	start;
	struct timeval	end;
	int				i;
	int				j;
	t_pixel_coord	p;

	gettimeofday(&start, NULL);
	j = 0;
	while (j < data->heigth)
	{
		i = 0;
		while (i < data->width)
		{
			p = (t_pixel_coord){i, j};
			fast_pixel_put(data, p, per_pixel(data, p));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->render.img, 0, 0);
	errno = 0;
	gettimeofday(&end, NULL);
	printf("frametime: %.3f ms\n", frame_time(start, end));
}

int	per_pixel(t_mlx_data *data, t_pixel_coord p)
{
	if (p.x == data->width / 2 || p.y == data->heigth / 2)
		return (0x00FFFFFF);
	return (0x00000000);
}

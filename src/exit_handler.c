/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:13:53 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/18 17:00:40 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	exit_handler(char *error)
{
	ft_putstr_color_fd(RED, error, 2);
	exit(1);
}

void	free_mlx(t_mlx_data *mlx_data)
{
	if (mlx_data->mlx_win)
		mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
	if (mlx_data->render.img)
		mlx_destroy_image(mlx_data->mlx, mlx_data->render.img);
	if (mlx_data->mlx)
	{
		mlx_destroy_display(mlx_data->mlx);
		free(mlx_data->mlx);
	}
}

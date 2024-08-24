/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:13:53 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/24 11:42:28 by pclaus           ###   ########.fr       */
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

int	check_extension(char *string)
{
	int	len;

	len = ft_strlen(string);
	if (string[len - 1] == 't' && string[len - 2] == 'r'
		&& string[len - 3] == '.')
		return (0);
	return (1);
}

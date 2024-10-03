/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:44:18 by pclaus            #+#    #+#             */
/*   Updated: 2024/10/03 18:45:06 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	file_error_check(t_mlx_data *mlx_data, int argc, char **argv, int *fd)
{
	if (!mlx_data || init_mlx_data(mlx_data))
		exit_handler("Error starting program\n");
	if (argc != 2)
	{
		free_mlx_data(mlx_data);
		exit_handler("Error\nAdd the .rt file as single argument\n");
	}
	if (check_extension(argv[1]) == 1)
	{
		free_mlx_data(mlx_data);
		exit_handler("Error\nThe file you tried to open doesn't end in .rt\n");
	}
	*fd = open(argv[1], O_RDONLY);
	if (*fd == -1)
	{
		free_mlx_data(mlx_data);
		exit_handler("Error\nThe file does not exist\n");
	}
}

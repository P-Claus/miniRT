/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coordinates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:27:26 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/06 21:59:41 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	parse_coordinates(t_coordinates *coordinates, char *string)
{
	char	**coordinates_split;
	double	coordinate_values[3];
	int		iter;

	iter = -1;
	coordinates_split = ft_split(string, ',');
	if (count_items_in_split(coordinates_split, 3) == 1
		|| check_digits_in_coordinates(coordinates_split) == 1)
	{
		free_split(coordinates_split);
		return (1);
	}
	while (coordinates_split[++iter])
		coordinate_values[iter] = ft_atof(coordinates_split[iter], 2);
	coordinates->x = coordinate_values[0];
	coordinates->y = coordinate_values[1];
	coordinates->z = coordinate_values[2];
	free_split(coordinates_split);
	return (0);
}

int	parse_orientation_vector(t_coordinates *coordinates, char *string, int iter)
{
	char	**coordinates_split;
	double	coordinate_values[3];

	coordinates_split = ft_split(string, ',');
	if (count_items_in_split(coordinates_split, 3) == 1
		|| check_digits_in_coordinates(coordinates_split) == 1)
	{
		free_split(coordinates_split);
		return (1);
	}
	while (coordinates_split[++iter])
	{
		coordinate_values[iter] = ft_atof(coordinates_split[iter], 2);
		if (!(coordinate_values[iter] >= -1.00
				&& coordinate_values[iter] <= 1.00))
		{
			free_split(coordinates_split);
			return (1);
		}
	}
	coordinates->x = coordinate_values[0];
	coordinates->y = coordinate_values[1];
	coordinates->z = coordinate_values[2];
	free_split(coordinates_split);
	return (0);
}

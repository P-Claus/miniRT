/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coordinates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:27:26 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/05 16:13:01 by pclaus           ###   ########.fr       */
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
	printf("x: %f\n", coordinates->x);
	printf("y: %f\n", coordinates->y);
	printf("z: %f\n", coordinates->z);
	free_split(coordinates_split);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:35:09 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/08 14:28:34 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	check_capital_identifier(t_scene_info *scene_info, char *string)
{
	if (string[0] == '\n')
		return (0);
	if (string[0] == 'A' && string[1] == ' ')
	{
		if (parse_ambient_lighting(scene_info, string) == 1)
			return (1);
		return (0);
	}
	else if (string[0] == 'C' && string[1] == ' ')
	{
		if (parse_camera(scene_info, string) == 1)
			return (1);
		return (0);
	}
	else if (string[0] == 'L' && string[1] == ' ')
	{
		if (parse_light(scene_info, string) == 1)
			return (1);
		return (0);
	}
	return (0);
}

int	check_shape_identifier(t_scene_info *scene_info, char *string,
		t_identifier_count *id_count)
{
	if (string[0] == '\n')
		return (0);
	if (string[0] == 's' && string[1] == 'p')
	{
		if (parse_sphere(scene_info, string, id_count) == 1)
			return (1);
	}
	else if (string[0] == 'p' && string[1] == 'l')
	{
		if (parse_plane(scene_info, string, id_count) == 1)
			return (1);
	}
	else if (string[0] == 'c' && string[1] == 'y')
	{
		if (parse_cylinder(scene_info, string, id_count) == 1)
			return (1);
	}
	return (0);
}

int	read_from_scene(t_scene_info *scene_info, int fd,
		t_identifier_count *id_count)
{
	char	*buffer;
	int		counter;

	buffer = "start";
	while (buffer != NULL)
	{
		buffer = get_next_line(fd);
		if (buffer == NULL)
			break ;
		if (check_capital_identifier(scene_info, buffer) == 1
			|| check_shape_identifier(scene_info, buffer, id_count) == 1)
		{
			free(buffer);
			exit_handler("Error\nFormat error\n");
		}
		free(buffer);
		counter++;
	}
	print_parsing_result(scene_info);
	return (0);
}

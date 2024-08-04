/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:35:09 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/04 18:21:02 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	init_scene_info(t_scene_info *scene_info)
{
	scene_info->A_lighting = 0.0;
	scene_info->A_rgb_code = 0;
	return (0);
}

int	check_capital_identifier(t_scene_info *scene_info, char *string,
		t_identifier_count *id_count)
{
	if (string[0] == '\n')
		return (0);
	if (string[0] == 'A' && string[1] == ' ' && id_count->has_A == false)
	{
		if (parse_ambient_lighting(scene_info, string) == 1)
			return (1);
		id_count->has_A = true;
		return (0);
	}
	/*
	else if(string[0] == 'C')
		printf("it's a C\n");
	else if(string[0] == 'L')
		printf("it's an L\n");
	else if(string[0] == 's' && string[1] == 'p')
		printf("it's an sp\n");
	else if(string[0] == 'p' && string[1] == 'l')
		printf("it's a pl\n");
	else if(string[0] == 'c' && string[1] == 'y')
		printf("it's a cy\n");
		*/
	else
		return (1);
}

int	read_from_scene(t_scene_info *scene_info, int fd)
{
	char						*buffer;
	static t_identifier_count	*id_count;

	id_count = malloc(sizeof(t_identifier_count));
	if (!id_count)
		exit_handler("Malloc error\n");
	id_count->has_A = false;
	id_count->has_L = false;
	id_count->has_C = false;
	buffer = get_next_line(fd);
	if (check_capital_identifier(scene_info, buffer, id_count) == 1)
	{
		free(id_count);
		free(buffer);
		exit_handler("Error\nFormat error\n");
	}
	printf("\n--------------------------------------\n");
	printf("The buffer is: \n%s\n", buffer);
	printf("\n--------------------------------------\n");
	printf("\n--------------------------------------\n");
	printf("The ambient lighting ratio is: %f\n", scene_info->A_lighting);
	printf("The rgb of the ambient lighting is: %d\n", scene_info->A_rgb_code);
	printf("\n--------------------------------------\n");
	free(buffer);
	free(id_count);
	return (0);
}

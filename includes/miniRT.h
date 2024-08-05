/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:06:26 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/05 13:52:44 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/incl/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

/*	STRUCTURES	*/

typedef struct s_camera_coordinates
{
	float						x;
	float						y;
	float						z;
}								t_camera_coordinates;

typedef struct s_orientation_coordinates
{
	float						x;
	float						y;
	float						z;
}								t_orientation_coordinates;

typedef struct s_scene_info
{
	float						A_lighting;
	int							A_rgb_code;
	t_camera_coordinates		C_coordinates_vp;
	t_orientation_coordinates	C_coordinates_o;
	int							C_fov;
}								t_scene_info;

typedef struct s_identifier_count
{
	bool						has_A;
	bool						has_L;
	bool						has_C;
}								t_identifier_count;

/*	PARSING	*/
int	parse_ambient_lighting(t_scene_info *scene_info,
							char *string);
int								parse_rgb(t_scene_info *scene_info,
									char *string);
int	parse_camera(t_scene_info *scene_info,
					char *string);
int	parse_coordinates_viewpoint(t_scene_info *scene_info,
								char *string);
int	parse_orientation_vector(t_scene_info *scene_info,
								char *string, int iter);

/*	PARSE UTILS	*/
int								count_items_in_split(char **split,
									int nb_needed);
double							ft_atof(const char *str, int decimal_nb);
void							free_split(char **split);
void	free_split_and_trimmed_rgb(char **split,
								char *trimmed_rgb);

/*	UTILS	*/
int								exit_handler(char *error);

/*	SRC	*/
int								main(int argc, char **argv);
int								init_scene_info(t_scene_info *scene_info);
int								read_from_scene(t_scene_info *scene_info,
									int fd);

#endif

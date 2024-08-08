/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:06:26 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/08 11:57:35 by pclaus           ###   ########.fr       */
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

typedef struct s_coordinates
{
	float			x;
	float			y;
	float			z;
}					t_coordinates;

typedef struct s_sphere
{
	t_coordinates	coordinates;
	float			diameter;
	int				rgb_code;
}					t_sphere;

typedef struct s_plane
{
	t_coordinates	coordinates;
	t_coordinates	vector;
	int				rgb_code;
}					t_plane;

typedef struct s_cylinder
{
	t_coordinates	coordinates;
	t_coordinates	vector;
	float			diameter;
	float			height;
	int				rgb_code;
}					t_cylinder;

typedef struct s_scene_info
{
	float			A_lighting;
	int				A_rgb_code;
	t_coordinates	C_coordinates_vp;
	t_coordinates	C_coordinates_o;
	int				C_fov;
	t_coordinates	L_cordinates_lp;
	float			L_brightness;
	int				L_rgb_code;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
}					t_scene_info;

typedef struct s_identifier_count
{
	int				A_count;
	int				C_count;
	int				L_count;
	int				sp_count;
	int				pl_count;
	int				cy_count;
}					t_identifier_count;

/*	PARSING	*/
int	parse_ambient_lighting(t_scene_info *scene_info,
							char *string);
int					parse_rgb(int *rgb_int, char *string);
int	parse_camera(t_scene_info *scene_info,
					char *string);
int					parse_coordinates(t_coordinates *coordinates, char *string);
int	parse_orientation_vector(t_coordinates *coordinates,
								char *string,
								int iter);
int					parse_light(t_scene_info *scene_info, char *string);
int					parse_sphere(t_scene_info *scene_info, char *string, t_identifier_count *id_count);
int					parse_plane(t_scene_info *scene_info, char *string, t_identifier_count *id_count);
int					parse_cylinder(t_scene_info *scene_info, char *string, t_identifier_count *id_count);

/*	PARSE UTILS	*/
int					count_items_in_split(char **split,
						int nb_needed);
double				ft_atof(const char *str, int decimal_nb);
void				free_split(char **split);
void				free_split_and_trimmed_rgb(char **split,
						char *trimmed_rgb);
int					check_digits_in_coordinates(char **split);
void				init_scene_info(t_scene_info *scene_info, t_identifier_count *id_count);
void				print_scene_info(t_scene_info *scene_info);
int					count_identifiers_for_initialization(int fd, t_identifier_count *id_count,
						char *buffer);

	/*	UTILS	*/
	int exit_handler(char *error);

/*	SRC	*/
int					main(int argc, char **argv);
int					read_from_scene(t_scene_info *scene_info, int fd, t_identifier_count *id_count);

#endif

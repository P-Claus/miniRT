/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:06:26 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/03 13:04:25 by pclaus           ###   ########.fr       */
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
typedef struct s_scene_info
{
	float	A_lighting;
	int		A_rgb_code;
}			t_scene_info;

typedef struct	s_identifier_count
{
	bool	has_A;
	bool	has_L;
	bool	has_C;
}			t_identifier_count;

/*	PARSING	*/
void		parse_ambient_lighting(t_scene_info *scene_info, char *string);
int			parse_rgb(t_scene_info *scene_info, char *string);

/*	PARSE UTILS	*/
int			count_items_in_split(char **split, int nb_needed);
double		ft_atof(const char *str, int decimal_nb);
void		free_split(char **split);

/*	UTILS	*/
int			exit_handler(char *error);

/*	SRC	*/
int			main(int argc, char **argv);
int			init_scene_info(t_scene_info *scene_info);
int			read_from_scene(t_scene_info *scene_info, int fd);

#endif

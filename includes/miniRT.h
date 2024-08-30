/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:06:26 by pclaus            #+#    #+#             */
/*   Updated: 2024/08/30 14:55:39 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/incl/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include "../minilibx_linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include "../minilibx_linux/mlx_int.h"
# include <sys/time.h>

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 860
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 540
# endif

# define DEG2RAD (M_PI / 180.)
# define RAD2DEG (180. / M_PI)
# define EPSILON 0.000001

/*	STRUCTURES	*/

typedef enum e_object_type
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_CYLINDER,
	OBJ_PLANE,
	OBJ_CUBE,
}	t_object_type;


typedef struct s_pixel_coord
{
	int	x;
	int	y;
}	t_pixel_coord;

typedef struct s_pixel_uv
{
	float	x;
	float	y;
}	t_pixel_uv;

typedef struct s_coordinates
{
	float			x;
	float			y;
	float			z;
}					t_coordinates;

typedef struct s_rgb
{
	float			r;
	float			g;
	float			b;
}					t_rgb;

typedef struct s_ray
{
	t_coordinates	origin;
	t_coordinates	dir;
}	t_ray;

typedef struct s_hit_info
{
	int				obj_type;
	size_t			obj_index;
	float			dist;
	t_coordinates	coordinates;
}	t_hit_info;

typedef struct s_a_lighting
{
	float			ambient_lighting;
	t_rgb			rgb;
}					t_a_lighting;

typedef struct s_camera
{
	t_coordinates	coordinates;
	t_coordinates	vector;
	int				fov;
}					t_camera;

typedef struct s_light
{
	t_coordinates	coordinates;
	float			brightness;
	t_rgb			rgb;
}					t_light;

typedef struct s_sphere
{
	t_coordinates	coordinates;
	float			diameter;
	t_rgb			rgb;
}					t_sphere;

typedef struct s_plane
{
	t_coordinates	coordinates;
	t_coordinates	vector;
	t_rgb			rgb;
}					t_plane;

typedef struct s_cylinder
{
	t_coordinates	coordinates;
	t_coordinates	vector;
	float			diameter;
	float			height;
	t_rgb				rgb;
}					t_cylinder;

typedef struct s_disk
{
	t_coordinates	coordinates;
	t_coordinates	vector;
	float			diameter;
	t_rgb			rgb;
}					t_disk;

typedef struct s_scene_info
{
	t_a_lighting	a_lighting;
	t_camera		camera;
	t_light			light;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
	int				nb_of_spheres;
	int				nb_of_planes;
	int				nb_of_cylinders;
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

typedef struct s_cube
{
	float	min_x;
	float	min_y;
	float	min_z;
	float	max_x;
	float	max_y;
	float	max_z;
	t_coordinates	hit_c;
	t_coordinates	vector;
}				t_cube;

typedef struct s_my_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_my_img;

typedef struct s_mlx_data
{
	void			*mlx;
	void			*mlx_win;
	t_my_img		render;
	t_scene_info	scene;
	int				width;
	int				heigth;
	float			aspect;
}	t_mlx_data;

/*	PARSING	*/
int	parse_ambient_lighting(t_scene_info *scene_info,
							char *string);
int					parse_rgb(t_rgb *rgb, char *string);
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
float				ft_atof(const char *str, int decimal_nb);
void				free_split(char **split);
void				free_split_and_trimmed_rgb(char **split,
						char *trimmed_rgb);
void				free_shape_arrays(t_scene_info *scene_info);
int					check_digits_in_coordinates(char **split);
void				init_scene_info(t_scene_info *scene_info, t_identifier_count *id_count);
void				print_parsing_result(t_scene_info *scene_info);
void				print_spheres(t_scene_info *scene_info);
void				print_planes(t_scene_info *scene_info);
void				print_cylinders(t_scene_info *scene_info, int iter);
int					count_identifiers_for_initialization(int fd, t_identifier_count *id_count,
						char *buffer);

/*	UTILS	*/
int					exit_handler(char *error);
void				free_mlx(t_mlx_data *data);
void				fast_pixel_put(t_mlx_data *data, t_pixel_coord p, int color);
struct timeval		time_diff(struct timeval start, struct timeval end);
float				frame_time(struct timeval start, struct timeval end);
int					check_extension(char *string);
bool				solve_quadratic(float a, float b, float c, float *dist);

/* SPHERE UTILS */
bool				sphere_hit(t_ray ray, t_sphere sphere, float *dist);
t_coordinates		sphere_normal(t_hit_info hit, t_sphere sphere);

/* PLANE UTILS */
bool				plane_hit(t_ray ray, t_plane plane, float *dist);

/* CYLINDER UTILS */
bool				cylinder_hit(t_ray ray, t_cylinder cylinder, float *dist);
t_coordinates		cylinder_normal(t_hit_info hit, t_cylinder cylinder);

/* DISK UTILS */
bool				disk_hit(t_ray ray, t_disk disk, float *dist);
/* CUBE UTILS */
bool				cube_hit(t_ray ray, t_cube *cube, float *dist, t_hit_info *hit);

/* VECTOR MATH STUFF */
t_coordinates		vec3_sum(t_coordinates a, t_coordinates b);
t_coordinates		vec3_diff(t_coordinates a, t_coordinates b);
t_coordinates		vec3_neg(t_coordinates a);
t_coordinates		vec3_scalar(t_coordinates a, float scalar);
float				vec3_norm(t_coordinates a);
t_coordinates		vec3_normalize(t_coordinates a);
float				vec3_dot(t_coordinates a, t_coordinates b);
t_coordinates		vec3_cross(t_coordinates a, t_coordinates b);

/* COLOR MATH STUFF */
t_rgb				color_scalar(t_rgb c, float scale);
int					color_to_int(t_rgb c);

/*  MLX_EVENTS  */
int					handle_no_event(t_mlx_data *data);
int					handle_keypress(int keysym, t_mlx_data *data);
int					handle_window_destroy(t_mlx_data *data);

/*	SRC	*/
int					main(int argc, char **argv);
int					read_from_scene(t_scene_info *scene_info, int fd, t_identifier_count *id_count);
void				render(t_mlx_data *data);

#endif

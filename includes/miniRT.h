/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:06:26 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/23 20:21:59 by efret            ###   ########.fr       */
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
#  define SCREEN_WIDTH 1600
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 900
# endif

# define MENU_WIDTH 240

# define DEG2RAD (M_PI / 180.)
# define RAD2DEG (180. / M_PI)

/* KEY_INPUT_STATE BIT MASKS */
# define KEY_W (1 << 2)
# define KEY_A (1 << 3)
# define KEY_S (1 << 4)
# define KEY_D (1 << 5)
# define KEY_Q (1 << 6)
# define KEY_E (1 << 7)
# define KEY_CTRL (1 << 8)

/* MOUSE_INPUT_STATE BIT MASKS */
# define BTN_LEFT (1 << 0)
# define BTN_RIGHT (1 << 1)

/*	STRUCTURES	*/

typedef enum e_render_state
{
	REND_LOW,
	REND_HIGH,
	REND_DONE
}	t_render_state;

typedef enum e_menu_draw_state
{
	MENU_NO_SHOW,
	MENU_SHOW,
	MENU_DRAWN
}	t_menu_draw_state;

typedef enum e_object_type
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_CYLINDER,
	OBJ_PLANE
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

typedef struct s_quat
{
	float			r;
	t_coordinates	v;
}	t_quat;

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
	t_coordinates	up;
	t_coordinates	right;
	int				fov;
	float			pitch;
	float			yaw;
	t_quat			rotation;
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

typedef struct s_my_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_my_img;

typedef struct s_ui_viewport
{
	t_my_img		render;
	t_pixel_coord	pos;
	t_pixel_coord	size;
	float			aspect;
}	t_ui_viewport;

typedef enum e_ui_menu_elem_type
{
	UI_MENU_SPACE,
	UI_MENU_TEXT,
	UI_MENU_BTN,
	UI_MENU_NBOX,
	UI_MENU_END
}	t_ui_menu_elem_type;

typedef enum e_ui_menu_page_type
{
	UI_MENU_PAGE_HOME,
	UI_MENU_PAGE_SELECT,
	UI_MENU_PAGE_ADD,
	UI_MENU_PAGE_REMOVE,
	UI_MENU_PAGE_OBJ_SPHERE,
	UI_MENU_PAGE_OBJ_CYLINDER,
	UI_MENU_PAGE_OBJ_PLANE,
	UI_MENU_PAGE_END,
}	t_ui_menu_page_type;

typedef enum e_data_type
{
	UI_DATA_NONE,
	UI_DATA_INT,
	UI_DATA_FLOAT,
	UI_DATA_COORDS,
	UI_DATA_SPHERE,
	UI_DATA_CYLINDER,
	UI_DATA_PLANE,
}	t_data_type;

# define FONT "-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso10646-1"
# define ELEM_HEIGHT 18
# define ELEM_OFFSET (40 + ELEM_HEIGHT)

typedef struct s_mlx_data t_mlx_data;
typedef struct s_ui_menu_page t_ui_menu_page;
typedef struct s_ui_menu t_ui_menu;
typedef struct s_ui_menu_elem t_ui_menu_elem;

typedef struct s_ui_menu_elem
{
	t_ui_menu_elem_type	type;
	char				*str;
	int					data_type;
	void				*data;
	float				data_min;
	float				data_max;
	float				step;
	int					(*draw)(struct s_ui_menu_elem *self, t_pixel_coord pos, t_mlx_data *data);
	int					(*func)(struct s_ui_menu_elem *self, t_mlx_data *data);
	t_ui_menu_elem		*next;
}	t_ui_menu_elem;

typedef struct s_ui_menu_page
{
	char			*title;
	t_ui_menu_elem	*elements;
	int				n_elems;
	t_pixel_coord	pos;
	t_pixel_coord	size;
}	t_ui_menu_page;

typedef struct s_ui_menu
{
	int				show;
	t_my_img		bg;
	t_pixel_coord	pos;
	t_pixel_coord	size;
	t_ui_menu_page	*curr_page;
	t_ui_menu_page	*pages;
	t_ui_menu_elem	*curr_input_elem;
	char			*curr_input_str;
}	t_ui_menu;

typedef struct s_mlx_data
{
	void			*mlx;
	void			*mlx_win;
	t_ui_viewport	full_render;
	t_ui_viewport	viewport;
	t_ui_menu		menu;
	t_scene_info	scene;
	float			frame_time;
	long			key_input_state;
	int				mouse_input_state;
	t_pixel_coord	mouse_last_pos;
	int				full_res;
	t_hit_info		selected;
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
void				fast_pixel_put(t_ui_viewport ui, t_pixel_coord p, int color);
struct timeval		time_diff(struct timeval start, struct timeval end);
float				frame_time(struct timeval start, struct timeval end);
int					check_extension(char *string);
bool				solve_quadratic(float a, float b, float c, float *dist);

/* RAY TRACING */
t_hit_info			cast_ray(t_ray ray, t_scene_info scene);
t_rgb				color_from_hit(t_hit_info hit, t_scene_info scene);
t_ray				calc_ray(t_camera camera, t_ui_viewport ui, t_pixel_coord p);

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

/* VECTOR MATH STUFF */
t_coordinates		vec3_sum(t_coordinates a, t_coordinates b);
t_coordinates		vec3_diff(t_coordinates a, t_coordinates b);
t_coordinates		vec3_neg(t_coordinates a);
t_coordinates		vec3_scalar(t_coordinates a, float scalar);
float				vec3_norm(t_coordinates a);
t_coordinates		vec3_normalize(t_coordinates a);
float				vec3_dot(t_coordinates a, t_coordinates b);
t_coordinates		vec3_cross(t_coordinates a, t_coordinates b);

/* QUATERNION MATH */
t_quat				quat_axis_rot(t_coordinates axis, float radians);
t_quat				quat_set(float r, t_coordinates v);
t_quat				quat_mult(t_quat a, t_quat b);
t_coordinates		quat_rotate_point(t_coordinates p, t_quat q);

/* COLOR MATH STUFF */
t_rgb				color_scalar(t_rgb c, float scale);
int					color_to_int(t_rgb c);

/*  MLX_EVENTS  */
int					handle_no_event(t_mlx_data *data);
int					handle_keypress(int keysym, t_mlx_data *data);
int					handle_keyrelease(int keysym, t_mlx_data *data);
int					handle_mouse_movement(int x, int y, t_mlx_data *data);
int					handle_mouse_press(int button, int x, int y, t_mlx_data *data);
int					handle_mouse_release(int button, int x, int y, t_mlx_data *data);
int					handle_window_destroy(t_mlx_data *data);

/*	SRC	*/
int					main(int argc, char **argv);
int					read_from_scene(t_scene_info *scene_info, int fd, t_identifier_count *id_count);
void				render(t_mlx_data *data, t_ui_viewport ui);
void				render_low_res(t_mlx_data *data, t_ui_viewport ui, int dx, int dy);

/* MENU UTILS */
int					menu_init_pages(t_mlx_data *data, t_ui_menu *menu);
int					menu_draw(t_mlx_data *data, t_ui_menu *menu);
int					box_is_clicked(t_pixel_coord pos, t_pixel_coord size, t_pixel_coord mouse);
int					menu_page_click(t_mlx_data *data);
int					menu_nbox_slide(t_mlx_data *data, t_ui_menu_elem *elem, t_pixel_coord diff);
int					menu_set_select_page(t_mlx_data *data, t_ui_menu *menu);

void				set_menu_page(t_mlx_data *data);
void				free_elements(t_ui_menu_elem **elems);

int					ft_strjoin_char(char **str, char c);
char				*ft_ftoa(float f, int prec);
int					ft_strstrip_char(char **str);

void				rotate_camera(t_camera *camera, t_pixel_coord mouse_diff, float frame_time);

#endif

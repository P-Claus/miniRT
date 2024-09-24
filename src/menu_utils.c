/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:51:45 by efret             #+#    #+#             */
/*   Updated: 2024/09/24 14:04:27 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_draw_space(t_ui_menu_elem *self, t_pixel_coord pos, t_mlx_data *data)
{
	(void)self;
	(void)data;
	(void)pos;
	return (0);
}

int	menu_draw_text(t_ui_menu_elem *self, t_pixel_coord pos, t_mlx_data *data)
{
	(void)self;
	(void)data;
	if (!self->str)
		return (1);
	pos.x += data->menu.curr_page->size.x / 2 - 4 * ft_strlen(self->str);
	mlx_string_put(data->mlx, data->mlx_win, pos.x, pos.y, 0x00FFFFFF, self->str);
	return (0);
}

int	menu_draw_btn(t_ui_menu_elem *self, t_pixel_coord pos, t_mlx_data *data)
{
	(void)self;
	(void)data;
	if (!self->str)
		return (1);
	pos.x += data->menu.curr_page->size.x / 2 - 4 * ft_strlen(self->str);
	mlx_string_put(data->mlx, data->mlx_win, pos.x, pos.y, 0x0000d9ff, self->str);
	return (0);
}

int	menu_draw_nbox(t_ui_menu_elem *self, t_pixel_coord pos, t_mlx_data *data)
{
	char	*box_text;
	int		color;
	bool	is_curr_input;

	is_curr_input = (data->menu.curr_input_elem == self);
	if (is_curr_input)
		color = 0x0000d9ff;
	else
		color = 0x00FFFFFF;
	mlx_string_put(data->mlx, data->mlx_win, pos.x, pos.y, color, self->str);
	box_text = data->menu.curr_input_str;
	if (is_curr_input && box_text)
		return (mlx_string_put(data->mlx, data->mlx_win, pos.x + data->menu.curr_page->size.x - 10 * ft_strlen(box_text), pos.y, color, box_text), 0);
	else if (self->data_type == UI_DATA_INT)
		box_text = ft_itoa(*((int *)self->data));
	else if (self->data_type == UI_DATA_FLOAT)
		box_text = ft_ftoa(*((float *)self->data), 3);
	else
		box_text = NULL;
	if (box_text)
		mlx_string_put(data->mlx, data->mlx_win, pos.x + data->menu.curr_page->size.x - 10 * ft_strlen(box_text), pos.y, color, box_text);
	free(box_text);
	return (0);
}

/* click functions */

int	menu_btn_reset_pos(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)data;
	*((t_coordinates *)self->data) = (t_coordinates){0, 0, 0};
	return (0);
}

int	menu_btn_reset_dir(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)data;
	*((t_coordinates *)self->data) = (t_coordinates){0, 1, 0};
	return (0);
}

int	menu_btn_reset_cam_pos(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->scene.camera.coordinates = (t_coordinates){0, 0, 0};
	return (0);
}

int	menu_btn_reset_cam_dir(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->scene.camera.yaw = 0;
	data->scene.camera.pitch = 0;
	data->scene.camera.vector = (t_coordinates){0, 0, -1};
	data->scene.camera.right = (t_coordinates){1, 0, 0};
	data->scene.camera.up = (t_coordinates){0, 1, 0};
	return (0);
}

int	menu_btn_reset_cam(t_ui_menu_elem *self, t_mlx_data *data)
{
	menu_btn_reset_cam_pos(self, data);
	menu_btn_reset_cam_dir(self, data);
	return (0);
}

int	menu_nbox_get_input(t_ui_menu_elem *self, t_mlx_data *data)
{
	data->menu.curr_input_elem = self;
	data->menu.curr_input_str = NULL;
	return (0);
}

int	menu_nbox_apply_float(t_ui_menu_elem *self, t_mlx_data *data)
{
	float	new_val;

	if (self->data_type != UI_DATA_FLOAT)
		return (1);
	new_val = ft_atof(data->menu.curr_input_str, 6);
	if (new_val < self->data_min || self->data_max < new_val)
		return (printf("Invalid input: color channel value between [%f, %f]\n", self->data_min, self->data_max), 1);
	*(float *)self->data = new_val;
	return (0);
}

int	menu_nbox_apply_yaw(t_ui_menu_elem *self, t_mlx_data *data)
{
	float	new_val;

	if (self->data_type != UI_DATA_FLOAT)
		return (1);
	if (data->menu.curr_input_str[0] == 'd')
		new_val = ft_atof(&data->menu.curr_input_str[1], 6) * DEG2RAD;
	else
		new_val = ft_atof(data->menu.curr_input_str, 6);
	new_val = new_val - M_PI * 2 * floor(new_val / (M_PI * 2));
	*(float *)self->data = new_val;
	rotate_camera(&data->scene.camera, (t_pixel_coord){0, 0}, 0);
	return (0);
}

int	menu_nbox_apply_pitch(t_ui_menu_elem *self, t_mlx_data *data)
{
	float	new_val;

	if (self->data_type != UI_DATA_FLOAT)
		return (1);
	if (data->menu.curr_input_str[0] == 'd')
		new_val = ft_atof(&data->menu.curr_input_str[1], 6) * DEG2RAD;
	else
		new_val = ft_atof(data->menu.curr_input_str, 6);
	if (new_val < -M_PI_2 || new_val > M_PI_2)
	{
		printf("Invalid input: pitch should be in [-pi/2, pi/2] range.\n");
		return (1);
	}
	*(float *)self->data = new_val;
	rotate_camera(&data->scene.camera, (t_pixel_coord){0, 0}, 0);
	return (0);
}

int	menu_nbox_apply_fov(t_ui_menu_elem *self, t_mlx_data *data)
{
	int	new_val;

	if (self->data_type != UI_DATA_INT)
		return (1);
	new_val = ft_atoi(data->menu.curr_input_str);
	if (new_val < self->data_min || self->data_max < new_val)
	{
		printf("Invalid input: fov should be int in [%f, %f] range.\n", self->data_min, self->data_max);
		return (1);
	}
	*(int *)self->data = new_val;
	return (0);
}

int	menu_nbox_apply_color_float(t_ui_menu_elem *self, t_mlx_data *data)
{
	float	new_val;

	if (self->data_type != UI_DATA_FLOAT)
		return (1);
	if (data->menu.curr_input_str[0] == 'i')
		new_val = ft_atoi(&data->menu.curr_input_str[1]) / 255.;
	else if (data->menu.curr_input_str[0] == '0' && data->menu.curr_input_str[1] == 'x')
		new_val = ft_atoi_base(&data->menu.curr_input_str[2], "0123456789abcdef") / 255.;
	else
		new_val = ft_atof(data->menu.curr_input_str, 6);
	if (new_val < self->data_min || self->data_max < new_val)
		return (printf("Invalid input: color channel value between [%f, %f]\n", self->data_min, self->data_max), 1);
	*(float *)self->data = new_val;
	return (0);
}

int	menu_nbox_apply_perc(t_ui_menu_elem *self, t_mlx_data *data)
{
	float	new_val;

	if (self->data_type != UI_DATA_FLOAT)
		return (1);
	if (data->menu.curr_input_str[0] == 'p')
		new_val = ft_atoi(&data->menu.curr_input_str[1]) / 100.;
	else
		new_val = ft_atof(data->menu.curr_input_str, 6);
	if (new_val < self->data_min || self->data_max < new_val)
		return (printf("Invalid input: percent value between [%f, %f]\n", self->data_min, self->data_max), 1);
	*(float *)self->data = new_val;
	return (0);
}

int	menu_btn_home_page(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_HOME];
	data->selected.obj_type = OBJ_NONE;
	return (0);
}

int	menu_btn_add_page(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_ADD];
	data->selected.obj_type = OBJ_NONE;
	return (0);
}

int	menu_btn_del_page(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_DEL];
	data->selected.obj_type = OBJ_NONE;
	return (0);
}

int	menu_btn_select_page(t_ui_menu_elem *self, t_mlx_data *data)
{
	(void)self;
	data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_SELECT];
	data->selected.obj_type = OBJ_NONE;
	return (0);
}

int	menu_btn_select_sphere(t_ui_menu_elem *self, t_mlx_data *data)
{
	int i;

	i = 0;
	while (i < data->scene.nb_of_spheres)
	{
		if (&data->scene.spheres[i] == self->data)
			break;
		i++;
	}
	data->selected = (t_hit_info){OBJ_SPHERE, i, 0, {0, 0, 0}};
	set_menu_page(data);
	return (0);
}

int	menu_btn_select_cylinder(t_ui_menu_elem *self, t_mlx_data *data)
{
	int i;

	i = 0;
	while (i < data->scene.nb_of_cylinders)
	{
		if (&data->scene.cylinders[i] == self->data)
			break;
		i++;
	}
	data->selected = (t_hit_info){OBJ_CYLINDER, i, 0, {0, 0, 0}};
	set_menu_page(data);
	return (0);
}

int	menu_btn_select_plane(t_ui_menu_elem *self, t_mlx_data *data)
{
	int i;

	i = 0;
	while (i < data->scene.nb_of_planes)
	{
		if (&data->scene.planes[i] == self->data)
			break;
		i++;
	}
	data->selected = (t_hit_info){OBJ_PLANE, i, 0, {0, 0, 0}};
	set_menu_page(data);
	return (0);
}

int	menu_btn_add_sphere(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_sphere	*spheres;
	int			i;

	(void)self;
	spheres = malloc(sizeof(t_sphere) * (data->scene.nb_of_spheres + 1));
	if (!spheres)
		return (1);
	i = 0;
	while (i < data->scene.nb_of_spheres)
	{
		spheres[i] = data->scene.spheres[i];
		i++;
	}
	spheres[data->scene.nb_of_spheres++] = (t_sphere){{0, 0, 0}, 2, {1, 1, 1}};
	free(data->scene.spheres);
	data->scene.spheres = spheres;
	data->selected = (t_hit_info){OBJ_SPHERE, i, 0, {0, 0, 0}};
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	set_menu_page(data);
	return (0);
}

int	menu_btn_add_cylinder(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_cylinder	*cylinders;
	int			i;

	(void)self;
	cylinders = malloc(sizeof(t_cylinder) * (data->scene.nb_of_cylinders + 1));
	if (!cylinders)
		return (1);
	i = 0;
	while (i < data->scene.nb_of_cylinders)
	{
		cylinders[i] = data->scene.cylinders[i];
		i++;
	}
	cylinders[data->scene.nb_of_cylinders++] = (t_cylinder){{0, 0, 0}, {0, 1, 0}, 2, 1, {1, 1, 1}};
	free(data->scene.cylinders);
	data->scene.cylinders = cylinders;
	data->selected = (t_hit_info){OBJ_CYLINDER, i, 0, {0, 0, 0}};
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	set_menu_page(data);
	return (0);
}

int	menu_btn_add_plane(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_plane	*planes;
	int			i;

	(void)self;
	planes = malloc(sizeof(t_plane) * (data->scene.nb_of_planes + 1));
	if (!planes)
		return (1);
	i = 0;
	while (i < data->scene.nb_of_planes)
	{
		planes[i] = data->scene.planes[i];
		i++;
	}
	planes[data->scene.nb_of_planes++] = (t_plane){{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
	free(data->scene.planes);
	data->scene.planes = planes;
	data->selected = (t_hit_info){OBJ_PLANE, i, 0, {0, 0, 0}};
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	set_menu_page(data);
	return (0);
}

int	menu_btn_del_sphere(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_sphere	*spheres;
	int			i;

	if (data->scene.nb_of_spheres < 1)
		return (1);
	if (data->scene.nb_of_spheres == 1)
	{
		spheres = NULL;
	}
	else
	{
		spheres = malloc(sizeof(t_sphere) * (data->scene.nb_of_spheres - 1));
		if (!spheres)
			return (1);
		i = 0;
		while (i < data->scene.nb_of_spheres && &data->scene.spheres[i] != self->data)
		{
			spheres[i] = data->scene.spheres[i];
			i++;
		}
		i++;
		while (i < data->scene.nb_of_spheres)
		{
			spheres[i - 1] = data->scene.spheres[i];
			i++;
		}
	}
	if (data->selected.obj_type == OBJ_SPHERE && &data->scene.spheres[data->selected.obj_index] == self->data)
	{
		data->selected = (t_hit_info){OBJ_NONE, 0, 0, {0, 0, 0}};
		set_menu_page(data);
	}
	free(data->scene.spheres);
	data->scene.spheres = spheres;
	data->scene.nb_of_spheres--;
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	return (0);
}

int	menu_btn_del_cylinder(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_cylinder	*cylinders;
	int			i;

	if (data->scene.nb_of_cylinders < 1)
		return (1);
	if (data->scene.nb_of_cylinders == 1)
	{
		cylinders = NULL;
	}
	else
	{
		cylinders = malloc(sizeof(t_cylinder) * (data->scene.nb_of_cylinders - 1));
		if (!cylinders)
			return (1);
		i = 0;
		while (i < data->scene.nb_of_cylinders && &data->scene.cylinders[i] != self->data)
		{
			cylinders[i] = data->scene.cylinders[i];
			i++;
		}
		i++;
		while (i < data->scene.nb_of_cylinders)
		{
			cylinders[i - 1] = data->scene.cylinders[i];
			i++;
		}
	}
	if (data->selected.obj_type == OBJ_CYLINDER && &data->scene.cylinders[data->selected.obj_index] == self->data)
	{
		data->selected = (t_hit_info){OBJ_NONE, 0, 0, {0, 0, 0}};
		set_menu_page(data);
	}
	free(data->scene.cylinders);
	data->scene.cylinders = cylinders;
	data->scene.nb_of_cylinders--;
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	return (0);
}

int	menu_btn_del_plane(t_ui_menu_elem *self, t_mlx_data *data)
{
	t_plane	*planes;
	int			i;

	if (data->scene.nb_of_planes < 1)
		return (1);
	if (data->scene.nb_of_planes == 1)
	{
		planes = NULL;
	}
	else
	{
		planes = malloc(sizeof(t_plane) * (data->scene.nb_of_planes - 1));
		if (!planes)
			return (1);
		i = 0;
		while (i < data->scene.nb_of_planes && &data->scene.planes[i] != self->data)
		{
			planes[i] = data->scene.planes[i];
			i++;
		}
		i++;
		while (i < data->scene.nb_of_planes)
		{
			planes[i - 1] = data->scene.planes[i];
			i++;
		}
	}
	if (data->selected.obj_type == OBJ_PLANE && &data->scene.planes[data->selected.obj_index] == self->data)
	{
		data->selected = (t_hit_info){OBJ_NONE, 0, 0, {0, 0, 0}};
		set_menu_page(data);
	}
	free(data->scene.planes);
	data->scene.planes = planes;
	data->scene.nb_of_planes--;
	menu_set_select_page(data, &data->menu);
	menu_set_del_page(data, &data->menu);
	return (0);
}

/* Event utilities */
int	menu_nbox_slide(t_mlx_data *data, t_ui_menu_elem *elem, t_pixel_coord diff)
{
	if (elem->data_type == UI_DATA_INT)
		*(int *)elem->data = fmin(fmax(*(int *)elem->data + diff.x * elem->step, elem->data_min), elem->data_max);
	else if (elem->data_type == UI_DATA_FLOAT)
		*(float *)elem->data = fmin(fmax(*(float *)elem->data + diff.x * elem->step, elem->data_min), elem->data_max);
	rotate_camera(&data->scene.camera, (t_pixel_coord){0, 0}, 0);
	return (0);
}

int	box_is_clicked(t_pixel_coord pos, t_pixel_coord size, t_pixel_coord mouse)
{
	mouse.x -= pos.x;
	mouse.y -= pos.y;
	if (mouse.x < 0 || mouse.x > size.x || mouse.y < 0 || mouse.y > size.y)
		return (0);
	return (1);
}

int	menu_page_click(t_mlx_data *data)
{
	int				elem_index;
	t_ui_menu_elem	*elem;

	if (box_is_clicked(data->menu.curr_page->pos, data->menu.curr_page->size, data->mouse_last_pos))
			printf("PAGE CLICK\n");
	if (data->menu.curr_input_elem)
	{
		if (data->menu.curr_input_str)
			free(data->menu.curr_input_str);
		data->menu.curr_input_elem = NULL;
	}
	if (data->mouse_last_pos.y < data->menu.curr_page->pos.y + ELEM_OFFSET)
		return (0);
	elem_index = (data->mouse_last_pos.y - data->menu.curr_page->pos.y - ELEM_OFFSET) / ELEM_HEIGHT;
	if (elem_index < 0 || elem_index >= data->menu.curr_page->n_elems)
		return (0);
	elem = data->menu.curr_page->elements;
	while (elem_index--)
		elem = elem->next;
	printf("Element click: %s\n", elem->str);
	if (elem->func && elem->type == UI_MENU_NBOX)
		menu_nbox_get_input(elem, data);
	else if (elem->func && data->mouse_input_state & BTN_LEFT)
		elem->func(elem, data);
	return (0);
}

/* Menu element list functions */

t_ui_menu_elem	*create_elem_text(char *str)
{
	t_ui_menu_elem	*new_elem;

	new_elem = malloc(sizeof(t_ui_menu_elem));
	if (!new_elem)
		return (NULL);
	*new_elem = (t_ui_menu_elem){UI_MENU_TEXT, str, 0, NULL, 0, 0, 0, menu_draw_text, NULL, NULL};
	return (new_elem);
}

t_ui_menu_elem	*create_elem_space(void)
{
	t_ui_menu_elem	*new_elem;

	new_elem = malloc(sizeof(t_ui_menu_elem));
	if (!new_elem)
		return (NULL);
	*new_elem = (t_ui_menu_elem){UI_MENU_SPACE, NULL, 0, NULL, 0, 0, 0, menu_draw_space, NULL, NULL};
	return (new_elem);
}

t_ui_menu_elem	*create_elem_btn(char *str, int data_type, void *data, int (*func)(t_ui_menu_elem *, t_mlx_data *))
{
	t_ui_menu_elem	*new_elem;

	new_elem = malloc(sizeof(t_ui_menu_elem));
	if (!new_elem)
		return (NULL);
	*new_elem = (t_ui_menu_elem){UI_MENU_BTN, str, data_type, data, 0, 0, 0, menu_draw_btn, func, NULL};
	return (new_elem);
}

t_ui_menu_elem	*create_elem_nbox(char *str, int data_type, void *data, float min, float max, float step, int (*func)(t_ui_menu_elem *, t_mlx_data *))
{
	t_ui_menu_elem	*new_elem;

	new_elem = malloc(sizeof(t_ui_menu_elem));
	if (!new_elem)
		return (NULL);
	*new_elem = (t_ui_menu_elem){UI_MENU_NBOX, str, data_type, data, min, max, step, menu_draw_nbox, func, NULL};
	return (new_elem);
}

int	add_elem_text(t_ui_menu_page *page, char *str)
{
	t_ui_menu_elem	*new_elem;
	t_ui_menu_elem	*page_elem;

	new_elem = create_elem_text(str);
	if (!new_elem)
		return (1);
	page->n_elems++;
	if (page->elements == NULL)
		return (page->elements = new_elem, 0);
	page_elem = page->elements;
	while (page_elem->next)
		page_elem = page_elem->next;
	page_elem->next = new_elem;
	return (0);
}

int	add_elem_space(t_ui_menu_page *page)
{
	t_ui_menu_elem	*new_elem;
	t_ui_menu_elem	*page_elem;

	new_elem = create_elem_space();
	if (!new_elem)
		return (1);
	page->n_elems++;
	if (page->elements == NULL)
		return (page->elements = new_elem, 0);
	page_elem = page->elements;
	while (page_elem->next)
		page_elem = page_elem->next;
	page_elem->next = new_elem;
	return (0);
}

int	add_elem_btn(t_ui_menu_page *page, char *str, int data_type, void *data, int (*func)(t_ui_menu_elem *, t_mlx_data *))
{
	t_ui_menu_elem	*new_elem;
	t_ui_menu_elem	*page_elem;

	new_elem = create_elem_btn(str, data_type, data, func);
	if (!new_elem)
		return (1);
	page->n_elems++;
	if (page->elements == NULL)
		return (page->elements = new_elem, 0);
	page_elem = page->elements;
	while (page_elem->next)
		page_elem = page_elem->next;
	page_elem->next = new_elem;
	return (0);
}

int	add_elem_nbox(t_ui_menu_page *page, char *str, int data_type, void *data, float min, float max, float step, int (*func)(t_ui_menu_elem *, t_mlx_data *))
{
	t_ui_menu_elem	*new_elem;
	t_ui_menu_elem	*page_elem;

	new_elem = create_elem_nbox(str, data_type, data, min, max, step, func);
	if (!new_elem)
		return (1);
	page->n_elems++;
	if (page->elements == NULL)
		return (page->elements = new_elem, 0);
	page_elem = page->elements;
	while (page_elem->next)
		page_elem = page_elem->next;
	page_elem->next = new_elem;
	return (0);
}

void	free_elements(t_ui_menu_elem **elems)
{
	t_ui_menu_elem	*iter;

	if (!*elems)
		return ;
	iter = *elems;
	while (iter)
	{
		iter = (*elems)->next;
		free(*elems);
		(*elems) = iter;
	}
}

/* Initialising the pages */

int	menu_init_page_home(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "HOME";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	add_elem_btn(page, "Select obj page", 0, NULL, menu_btn_select_page);
	add_elem_btn(page, "Add obj page", 0, NULL, menu_btn_add_page);
	add_elem_btn(page, "Del obj page", 0, NULL, menu_btn_del_page);
	add_elem_space(page);
	add_elem_text(page, "Camera");
	add_elem_btn(page, "Reset camera", 0, NULL, menu_btn_reset_cam);
	add_elem_space(page);
	add_elem_btn(page, "Reset position", UI_DATA_COORDS, &data->scene.camera.coordinates, menu_btn_reset_cam_pos);
	add_elem_nbox(page, "pos x:", UI_DATA_FLOAT, &data->scene.camera.coordinates.x, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_nbox(page, "pos y:", UI_DATA_FLOAT, &data->scene.camera.coordinates.y, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_nbox(page, "pos z:", UI_DATA_FLOAT, &data->scene.camera.coordinates.z, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_space(page);
	add_elem_btn(page, "Reset direction", UI_DATA_COORDS, &data->scene.camera.vector, menu_btn_reset_cam_dir);
	add_elem_nbox(page, "dir x:", UI_DATA_FLOAT, &data->scene.camera.vector.x, -INFINITY, INFINITY, 1., NULL);
	add_elem_nbox(page, "dir y:", UI_DATA_FLOAT, &data->scene.camera.vector.y, -INFINITY, INFINITY, 1., NULL);
	add_elem_nbox(page, "dir z:", UI_DATA_FLOAT, &data->scene.camera.vector.z, -INFINITY, INFINITY, 1., NULL);
	add_elem_nbox(page, "yaw:", UI_DATA_FLOAT, &data->scene.camera.yaw, -INFINITY, INFINITY, 1 * DEG2RAD, menu_nbox_apply_yaw);
	add_elem_nbox(page, "pitch:", UI_DATA_FLOAT, &data->scene.camera.pitch, -INFINITY, INFINITY, 1 * DEG2RAD, menu_nbox_apply_pitch);
	add_elem_nbox(page, "fov:", UI_DATA_INT, &data->scene.camera.fov, 5, 175, 1, menu_nbox_apply_fov);
	add_elem_space(page);
	add_elem_text(page, "Ambient");
	add_elem_nbox(page, "intensity:", UI_DATA_FLOAT, &data->scene.a_lighting.ambient_lighting, 0, 1., 0.01, menu_nbox_apply_perc);
	add_elem_nbox(page, "red:", UI_DATA_FLOAT, &data->scene.a_lighting.rgb.r, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_nbox(page, "green:", UI_DATA_FLOAT, &data->scene.a_lighting.rgb.g, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_nbox(page, "blue:", UI_DATA_FLOAT, &data->scene.a_lighting.rgb.b, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_space(page);
	add_elem_text(page, "Point Light");
	add_elem_nbox(page, "pos x:", UI_DATA_FLOAT, &data->scene.light.coordinates.x, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_nbox(page, "pos y:", UI_DATA_FLOAT, &data->scene.light.coordinates.y, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_nbox(page, "pos z:", UI_DATA_FLOAT, &data->scene.light.coordinates.z, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_nbox(page, "intensity:", UI_DATA_FLOAT, &data->scene.light.brightness, 0, 1., 0.01, menu_nbox_apply_perc);
	add_elem_nbox(page, "red:", UI_DATA_FLOAT, &data->scene.light.rgb.r, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_nbox(page, "green:", UI_DATA_FLOAT, &data->scene.light.rgb.g, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_nbox(page, "blue:", UI_DATA_FLOAT, &data->scene.light.rgb.b, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	return (0);
}

int	menu_init_page_sphere(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "___";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	add_elem_btn(page, "Home page", 0, NULL, menu_btn_home_page);
	return (0);
}

int	menu_init_page_cylinder(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "___";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	add_elem_btn(page, "Home page", 0, NULL, menu_btn_home_page);
	return (0);
}

int	menu_init_page_plane(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "___";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	add_elem_btn(page, "Home page", 0, NULL, menu_btn_home_page);
	return (0);
}

void	select_page_add_spheres(t_mlx_data *data, t_ui_menu_page *page)
{
	int	i;

	if (!data->scene.nb_of_spheres)
		return ;
	add_elem_space(page);
	add_elem_text(page, "Spheres");
	i = 0;
	while (i < data->scene.nb_of_spheres)
		add_elem_btn(page, "sphere", UI_DATA_SPHERE, &data->scene.spheres[i++], menu_btn_select_sphere);
}

void	select_page_add_cylinders(t_mlx_data *data, t_ui_menu_page *page)
{
	int	i;

	if (!data->scene.nb_of_cylinders)
		return ;
	add_elem_space(page);
	add_elem_text(page, "Cylinders");
	i = 0;
	while (i < data->scene.nb_of_cylinders)
		add_elem_btn(page, "cylinder", UI_DATA_CYLINDER, &data->scene.cylinders[i++], menu_btn_select_cylinder);
}

void	select_page_add_planes(t_mlx_data *data, t_ui_menu_page *page)
{
	int	i;

	if (!data->scene.nb_of_planes)
		return ;
	add_elem_space(page);
	add_elem_text(page, "Planes");
	i = 0;
	while (i < data->scene.nb_of_planes)
		add_elem_btn(page, "plane", UI_DATA_PLANE, &data->scene.planes[i++], menu_btn_select_plane);
}

int	menu_init_page_select(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "SELECT";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	add_elem_btn(page, "Home page", 0, NULL, menu_btn_home_page);
	select_page_add_spheres(data, page);
	select_page_add_cylinders(data, page);
	select_page_add_planes(data, page);
	return (0);
}

int	menu_set_select_page(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page *page;

	page = &data->menu.pages[UI_MENU_PAGE_SELECT];
	free_elements(&page->elements);
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "SELECT";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	add_elem_btn(page, "Home page", 0, NULL, menu_btn_home_page);
	select_page_add_spheres(data, page);
	select_page_add_cylinders(data, page);
	select_page_add_planes(data, page);
	return (0);
}

int	menu_init_page_add(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "ADD OBJ";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	add_elem_btn(page, "Home page", 0, NULL, menu_btn_home_page);
	add_elem_space(page);
	add_elem_btn(page, "Add sphere", 0, NULL, menu_btn_add_sphere);
	add_elem_btn(page, "Add cylinder", 0, NULL, menu_btn_add_cylinder);
	add_elem_btn(page, "Add plane", 0, NULL, menu_btn_add_plane);
	return (0);
}

void	del_page_add_spheres(t_mlx_data *data, t_ui_menu_page *page)
{
	int	i;

	if (!data->scene.nb_of_spheres)
		return ;
	add_elem_space(page);
	add_elem_text(page, "Spheres");
	i = 0;
	while (i < data->scene.nb_of_spheres)
		add_elem_btn(page, "sphere", UI_DATA_SPHERE, &data->scene.spheres[i++], menu_btn_del_sphere);
}

void	del_page_add_cylinders(t_mlx_data *data, t_ui_menu_page *page)
{
	int	i;

	if (!data->scene.nb_of_cylinders)
		return ;
	add_elem_space(page);
	add_elem_text(page, "Cylinders");
	i = 0;
	while (i < data->scene.nb_of_cylinders)
		add_elem_btn(page, "cylinder", UI_DATA_CYLINDER, &data->scene.cylinders[i++], menu_btn_del_cylinder);
}

void	del_page_add_planes(t_mlx_data *data, t_ui_menu_page *page)
{
	int	i;

	if (!data->scene.nb_of_planes)
		return ;
	add_elem_space(page);
	add_elem_text(page, "Planes");
	i = 0;
	while (i < data->scene.nb_of_planes)
		add_elem_btn(page, "plane", UI_DATA_PLANE, &data->scene.planes[i++], menu_btn_del_plane);
}

int	menu_init_page_del(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "DELETE";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	add_elem_btn(page, "Home page", 0, NULL, menu_btn_home_page);
	del_page_add_spheres(data, page);
	del_page_add_cylinders(data, page);
	del_page_add_planes(data, page);
	return (0);
}

int	menu_set_del_page(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page *page;

	page = &data->menu.pages[UI_MENU_PAGE_DEL];
	free_elements(&page->elements);
	page->n_elems = 0;
	page->elements = NULL;
	page->title = "DELETE";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	add_elem_btn(page, "Home page", 0, NULL, menu_btn_home_page);
	del_page_add_spheres(data, page);
	del_page_add_cylinders(data, page);
	del_page_add_planes(data, page);
	return (0);
}

int	menu_init_page_end(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	(void)menu;
	*page = (t_ui_menu_page){NULL, NULL, 0, {0, 0}, {0, 0}};
	return (0);
}

int	menu_init_pages(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page	*pages;

	pages = malloc((UI_MENU_PAGE_END + 1) * sizeof(t_ui_menu_page));
	if (!pages)
		return (1);
	menu->pages = pages;
	menu_init_page_home(data, menu, &pages[UI_MENU_PAGE_HOME]);
	menu_init_page_select(data, menu, &pages[UI_MENU_PAGE_SELECT]);
	menu_init_page_add(data, menu, &pages[UI_MENU_PAGE_ADD]);
	menu_init_page_del(data, menu, &pages[UI_MENU_PAGE_DEL]);
	menu_init_page_sphere(data, menu, &pages[UI_MENU_PAGE_OBJ_SPHERE]);
	menu_init_page_cylinder(data, menu, &pages[UI_MENU_PAGE_OBJ_CYLINDER]);
	menu_init_page_plane(data, menu, &pages[UI_MENU_PAGE_OBJ_PLANE]);
	menu_init_page_end(data, menu, &pages[UI_MENU_PAGE_END]);
	return (0);
}

void	set_menu_sphere_page(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page	*page;
	t_sphere		*obj;

	obj = &data->scene.spheres[data->selected.obj_index];
	menu->curr_page = &data->menu.pages[UI_MENU_PAGE_OBJ_SPHERE];
	page = menu->curr_page;
	free_elements(&page->elements);
	page->n_elems = 0;
	page->title = "SPHERE";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	add_elem_btn(page, "Home page", 0, NULL, menu_btn_home_page);
	add_elem_space(page);
	add_elem_text(page, "sphere");
	add_elem_btn(page, "delete", UI_DATA_SPHERE, obj, menu_btn_del_sphere);
	add_elem_space(page);
	add_elem_btn(page, "Reset position", UI_DATA_COORDS, &obj->coordinates, menu_btn_reset_pos);
	add_elem_nbox(page, "pos x:", UI_DATA_FLOAT, &obj->coordinates.x, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_nbox(page, "pos y:", UI_DATA_FLOAT, &obj->coordinates.y, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_nbox(page, "pos z:", UI_DATA_FLOAT, &obj->coordinates.z, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_space(page);
	add_elem_text(page, "Color");
	add_elem_nbox(page, "red:", UI_DATA_FLOAT, &obj->rgb.r, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_nbox(page, "green:", UI_DATA_FLOAT, &obj->rgb.g, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_nbox(page, "blue:", UI_DATA_FLOAT, &obj->rgb.b, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_space(page);
	add_elem_text(page, "Attributes");
	add_elem_nbox(page, "diameter:", UI_DATA_FLOAT, &obj->diameter, 0., INFINITY, 1., menu_nbox_apply_float);
}

void	set_menu_cylinder_page(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page	*page;
	t_cylinder		*obj;

	obj = &data->scene.cylinders[data->selected.obj_index];
	data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_OBJ_CYLINDER];
	page = data->menu.curr_page;
	free_elements(&page->elements);
	page->n_elems = 0;
	page->title = "CYLINDER";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	add_elem_btn(page, "Home page", 0, NULL, menu_btn_home_page);
	add_elem_space(page);
	add_elem_text(page, "cylinder");
	add_elem_btn(page, "delete", UI_DATA_CYLINDER, obj, menu_btn_del_cylinder);
	add_elem_space(page);
	add_elem_btn(page, "Reset position", UI_DATA_COORDS, &obj->coordinates, menu_btn_reset_pos);
	add_elem_nbox(page, "pos x:", UI_DATA_FLOAT, &obj->coordinates.x, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_nbox(page, "pos y:", UI_DATA_FLOAT, &obj->coordinates.y, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_nbox(page, "pos z:", UI_DATA_FLOAT, &obj->coordinates.z, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_space(page);
	add_elem_btn(page, "Reset direction", UI_DATA_COORDS, &obj->vector, menu_btn_reset_dir);
	add_elem_nbox(page, "dir x:", UI_DATA_FLOAT, &obj->vector.x, -INFINITY, INFINITY, 1., NULL);
	add_elem_nbox(page, "dir y:", UI_DATA_FLOAT, &obj->vector.y, -INFINITY, INFINITY, 1., NULL);
	add_elem_nbox(page, "dir z:", UI_DATA_FLOAT, &obj->vector.z, -INFINITY, INFINITY, 1., NULL);
	add_elem_space(page);
	add_elem_text(page, "Color");
	add_elem_nbox(page, "red:", UI_DATA_FLOAT, &obj->rgb.r, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_nbox(page, "green:", UI_DATA_FLOAT, &obj->rgb.g, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_nbox(page, "blue:", UI_DATA_FLOAT, &obj->rgb.b, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_space(page);
	add_elem_text(page, "Attributes");
	add_elem_nbox(page, "height:", UI_DATA_FLOAT, &obj->height, 0., INFINITY, 1., menu_nbox_apply_float);
	add_elem_nbox(page, "diameter:", UI_DATA_FLOAT, &obj->diameter, 0., INFINITY, 1., menu_nbox_apply_float);
}

void	set_menu_plane_page(t_mlx_data *data, t_ui_menu *menu)
{
	t_ui_menu_page	*page;
	t_plane			*obj;

	obj = &data->scene.planes[data->selected.obj_index];
	data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_OBJ_PLANE];
	page = data->menu.curr_page;
	free_elements(&page->elements);
	page->n_elems = 0;
	page->title = "PLANE";
	page->pos = (t_pixel_coord){menu->pos.x + 20, menu->pos.y + 50};
	page->size = (t_pixel_coord){menu->size.x - 40, SCREEN_HEIGHT - 80};
	add_elem_btn(page, "Home page", 0, NULL, menu_btn_home_page);
	add_elem_space(page);
	add_elem_text(page, "plane");
	add_elem_btn(page, "delete", UI_DATA_PLANE, obj, menu_btn_del_plane);
	add_elem_space(page);
	add_elem_btn(page, "Reset position", UI_DATA_COORDS, &obj->coordinates, menu_btn_reset_pos);
	add_elem_nbox(page, "pos x:", UI_DATA_FLOAT, &obj->coordinates.x, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_nbox(page, "pos y:", UI_DATA_FLOAT, &obj->coordinates.y, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_nbox(page, "pos z:", UI_DATA_FLOAT, &obj->coordinates.z, -INFINITY, INFINITY, 1., menu_nbox_apply_float);
	add_elem_space(page);
	add_elem_btn(page, "Reset direction", UI_DATA_COORDS, &obj->vector, menu_btn_reset_dir);
	add_elem_nbox(page, "dir x:", UI_DATA_FLOAT, &obj->vector.x, -INFINITY, INFINITY, 1., NULL);
	add_elem_nbox(page, "dir y:", UI_DATA_FLOAT, &obj->vector.y, -INFINITY, INFINITY, 1., NULL);
	add_elem_nbox(page, "dir z:", UI_DATA_FLOAT, &obj->vector.z, -INFINITY, INFINITY, 1., NULL);
	add_elem_space(page);
	add_elem_text(page, "Color");
	add_elem_nbox(page, "red:", UI_DATA_FLOAT, &obj->rgb.r, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_nbox(page, "green:", UI_DATA_FLOAT, &obj->rgb.g, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_nbox(page, "blue:", UI_DATA_FLOAT, &obj->rgb.b, 0, 1., 1. / 255, menu_nbox_apply_color_float);
	add_elem_space(page);
	add_elem_text(page, "Attributes");
}

void	set_menu_page(t_mlx_data *data)
{
	if (data->selected.obj_type == OBJ_NONE)
		data->menu.curr_page = &data->menu.pages[UI_MENU_PAGE_HOME];
	else if (data->selected.obj_type == OBJ_SPHERE)
		set_menu_sphere_page(data, &data->menu);
	else if (data->selected.obj_type == OBJ_CYLINDER)
		set_menu_cylinder_page(data, &data->menu);
	else if (data->selected.obj_type == OBJ_PLANE)
		set_menu_plane_page(data, &data->menu);
	if (data->menu.show)
		data->menu.show = MENU_SHOW;
}

/* Drawing the menu and pages */

void	menu_draw_page(t_mlx_data *data, t_ui_menu_page page)
{
	t_ui_menu_elem	*elem;
	t_pixel_coord	pos;

	if (page.title == NULL)
		return ;
	mlx_string_put(data->mlx, data->mlx_win, page.pos.x + page.size.x / 2 - ft_strlen(page.title) * 4, page.pos.y + 15, 0x00DDDDDD, page.title);

	mlx_string_put(data->mlx, data->mlx_win, page.pos.x - 4, page.pos.y + 5, 0x00000000, "x");
	mlx_string_put(data->mlx, data->mlx_win, page.pos.x + page.size.x - 4, page.pos.y + 5, 0x00000000, "x");

	mlx_string_put(data->mlx, data->mlx_win, page.pos.x - 4, page.pos.y + page.size.y - ELEM_OFFSET + 5, 0x00000000, "x");
	mlx_string_put(data->mlx, data->mlx_win, page.pos.x + page.size.x - 4, page.pos.y + page.size.y - ELEM_OFFSET + 5, 0x00000000, "x");

	mlx_string_put(data->mlx, data->mlx_win, page.pos.x - 4, page.pos.y + ELEM_OFFSET + 5, 0x00000000, "x");
	mlx_string_put(data->mlx, data->mlx_win, page.pos.x + page.size.x - 4, page.pos.y + ELEM_OFFSET + 5, 0x00000000, "x");

	pos = page.pos;
	pos.y += ELEM_OFFSET;
	elem = page.elements;
	while (elem)
	{
		pos.y += ELEM_HEIGHT;
		elem->draw(elem, pos, data);
		elem = elem->next;
	}
}

int	menu_draw(t_mlx_data *data, t_ui_menu *menu)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, menu->bg.img, menu->pos.x, menu->pos.y);
	mlx_string_put(data->mlx, data->mlx_win, menu->pos.x + menu->size.x / 2 - 4 * 4, menu->pos.y + 10 + 5, 0x00CCCCCC, "MENU");
	menu_draw_page(data, *menu->curr_page);
	menu->show = MENU_DRAWN;
	return (0);
}

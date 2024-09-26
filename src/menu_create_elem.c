/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_create_elem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:38:41 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 12:47:46 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_ui_menu_elem	*create_elem_text(char *str)
{
	t_ui_menu_elem	*new_elem;

	new_elem = malloc(sizeof(t_ui_menu_elem));
	if (!new_elem)
		return (NULL);
	*new_elem = 
		(t_ui_menu_elem){UI_MENU_TEXT, str, {0, NULL}, {0, 0, 0},
		menu_draw_text, NULL, NULL};
	return (new_elem);
}

t_ui_menu_elem	*create_elem_space(void)
{
	t_ui_menu_elem	*new_elem;

	new_elem = malloc(sizeof(t_ui_menu_elem));
	if (!new_elem)
		return (NULL);
	*new_elem = 
		(t_ui_menu_elem){UI_MENU_SPACE, NULL, {0, NULL}, {0, 0, 0},
		menu_draw_space, NULL, NULL};
	return (new_elem);
}

t_ui_menu_elem	*create_elem_btn(char *str,
		t_elem_data data, int (*func)(t_ui_menu_elem *, t_mlx_data *))
{
	t_ui_menu_elem	*new_elem;

	new_elem = malloc(sizeof(t_ui_menu_elem));
	if (!new_elem)
		return (NULL);
	*new_elem = 
		(t_ui_menu_elem){UI_MENU_BTN, str, data, {0, 0, 0},
		menu_draw_btn, func, NULL};
	return (new_elem);
}

t_ui_menu_elem	*create_elem_nbox(char *str,
		t_elem_data data, t_elem_range range,
		int (*func)(t_ui_menu_elem *, t_mlx_data *))
{
	t_ui_menu_elem	*new_elem;

	new_elem = malloc(sizeof(t_ui_menu_elem));
	if (!new_elem)
		return (NULL);
	*new_elem = 
		(t_ui_menu_elem){UI_MENU_NBOX, str, data, range,
		menu_draw_nbox, func, NULL};
	return (new_elem);
}

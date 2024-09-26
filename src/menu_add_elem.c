/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_add_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:06:58 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 17:31:11 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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

int	add_elem_btn(t_ui_menu_page *page, char *str,
		t_elem_data data, int (*func)(t_ui_menu_elem *, t_mlx_data *))
{
	t_ui_menu_elem	*new_elem;
	t_ui_menu_elem	*page_elem;

	new_elem = create_elem_btn(str, data, func);
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

int	add_elem_nbox_bs(t_ui_menu_page *page, t_nbox_norm_bs nbox)
{
	t_ui_menu_elem	*new_elem;
	t_ui_menu_elem	*page_elem;

	new_elem = create_elem_nbox(nbox.str, nbox.data, nbox.range, nbox.func);
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

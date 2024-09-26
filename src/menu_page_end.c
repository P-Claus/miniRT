/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_page_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:26:16 by efret             #+#    #+#             */
/*   Updated: 2024/09/26 18:35:14 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	menu_init_page_end(t_mlx_data *data, t_ui_menu *menu, t_ui_menu_page *page)
{
	(void)data;
	(void)menu;
	*page = (t_ui_menu_page){NULL, NULL, 0, {0, 0}, {0, 0}, 0};
	return (0);
}

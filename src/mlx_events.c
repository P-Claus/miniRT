/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:17:14 by efret             #+#    #+#             */
/*   Updated: 2024/08/18 16:36:31 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	handle_no_event(t_mlx_data *data)
{
	if (!data || !data->mlx_win)
		return (1);
	render(data);
	return (0);
}

int	handle_keypress(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx);
	return (0);
}

int	handle_window_destroy(t_mlx_data *data)
{
	printf("WINDOW DESTROYED\n");
	mlx_loop_end(data->mlx);
	return (0);
}

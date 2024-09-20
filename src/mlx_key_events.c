/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:11:23 by efret             #+#    #+#             */
/*   Updated: 2024/09/20 22:05:14 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	handle_move_keys(int keysym, long *key_input_state)
{
	if (keysym == XK_a)
		*key_input_state ^= KEY_A;
	else if (keysym == XK_d)
		*key_input_state ^= KEY_D;
	else if (keysym == XK_w)
		*key_input_state ^= KEY_W;
	else if (keysym == XK_s)
		*key_input_state ^= KEY_S;
	else if (keysym == XK_q)
		*key_input_state ^= KEY_Q;
	else if (keysym == XK_e)
		*key_input_state ^= KEY_E;
	else if (keysym == XK_Alt_L)
		*key_input_state ^= KEY_ALT;
	else if (keysym == XK_Control_L)
		*key_input_state ^= KEY_CTRL;
	else if (keysym == XK_Shift_L)
		*key_input_state ^= KEY_SHIFT;
	else
		return (0);
	return (1);
}

int	handle_keypress(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx);
	else if (handle_move_keys(keysym, &data->key_input_state))
		data->full_res = REND_LOW;
	else if (keysym == XK_r
		&& !data->key_input_state && !data->mouse_input_state)
		data->full_res = !(data->full_res);
	else if (data->full_res != REND_LOW)
		return (0);
	else if (keysym == XK_h)
		data->low_res_lev = fmax(data->low_res_lev - 2, 4);
	else if (keysym == XK_l)
		data->low_res_lev = fmin(data->low_res_lev + 2, 32);
	else if (keysym == XK_Up)
		data->speed = fmin(data->speed + 0.1, 1.6);
	else if (keysym == XK_Down)
		data->speed = fmax(data->speed - 0.1, 0.1);
	else if (keysym == XK_g)
		data->gamma_type = (data->gamma_type + 1) % GAMMA_END;
	return (0);
}

int	handle_keyrelease(int keysym, t_mlx_data *data)
{
	if (handle_move_keys(keysym, &data->key_input_state))
		;
	return (0);
}

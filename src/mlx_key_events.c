/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:11:23 by efret             #+#    #+#             */
/*   Updated: 2024/10/04 14:29:05 by marvin           ###   ########.fr       */
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

int	handle_settings_keys(int keysym, t_mlx_data *data)
{
	if (keysym == XK_h)
		data->low_res_lev = fmax(data->low_res_lev - RES_STEP, RES_MIN);
	else if (keysym == XK_l)
		data->low_res_lev = fmin(data->low_res_lev + RES_STEP, RES_MAX);
	else if (keysym == XK_Up)
		data->speed = fmin(data->speed + SPEED_STEP, SPEED_MAX);
	else if (keysym == XK_Down)
		data->speed = fmax(data->speed - SPEED_STEP, SPEED_MIN);
	else if (keysym == XK_g)
		data->gamma_type = (data->gamma_type + 1) % GAMMA_END;
	else if (keysym == XK_m && !data->full_res)
		data->menu.show = !(data->menu.show);
	else
		return (0);
	return (1);
}

int	handle_keypress(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Home)
		data->menu.curr_page->scroll = 0;
	if (data->menu.curr_input_elem)
		return (handle_menu_keypress(keysym, data));
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx);
	else if (handle_move_keys(keysym, &data->key_input_state))
		data->full_res = REND_LOW;
	else if (keysym == XK_r
		&& !data->key_input_state && !data->mouse_input_state)
		data->full_res = !(data->full_res);
	else if (data->full_res != REND_LOW)
		return (0);
	else if (handle_settings_keys(keysym, data))
		;
	if (data->menu.show == MENU_DRAWN)
		data->menu.show = MENU_SHOW;
	return (0);
}

int	handle_keyrelease(int keysym, t_mlx_data *data)
{
	if (data->menu.curr_input_elem)
		return (0);
	if (handle_move_keys(keysym, &data->key_input_state))
		;
	return (0);
}

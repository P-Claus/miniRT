/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:11:23 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 15:35:31 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	handle_menu_keypress(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
	{
		data->menu.curr_input_elem = NULL;
		free(data->menu.curr_input_str);
		data->menu.curr_input_str = NULL;
	}
	else if (keysym == XK_Return)
	{
		if (data->menu.curr_input_str == NULL)
			return (data->menu.curr_input_elem = NULL,
				data->menu.show = MENU_SHOW, 0);
		if (data->menu.curr_input_elem->func)
			data->menu.curr_input_elem->func(data->menu.curr_input_elem, data);
		data->menu.curr_input_elem = NULL;
		free(data->menu.curr_input_str);
		data->menu.curr_input_str = NULL;
	}
	else if (keysym == XK_BackSpace)
	{
		if (data->menu.curr_input_str == NULL)
			data->menu.curr_input_str = ft_calloc(1, 1);
		ft_strstrip_char(&data->menu.curr_input_str);
	}
	else if (XK_0 <= keysym && keysym <= XK_9)
		ft_strjoin_char(&data->menu.curr_input_str, keysym);
	else if (XK_a <= keysym && keysym <= XK_z)
		ft_strjoin_char(&data->menu.curr_input_str, keysym);
	else if (keysym == XK_space || keysym == XK_comma || keysym == XK_period
		|| keysym == XK_plus || keysym == XK_minus)
		ft_strjoin_char(&data->menu.curr_input_str, keysym);
	data->menu.show = MENU_SHOW;
	return (0);
}

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
	else if (keysym == XK_h)
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

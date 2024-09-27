/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_frame_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:20:41 by efret             #+#    #+#             */
/*   Updated: 2024/09/27 17:21:08 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	image_add_frametime(t_mlx_data *data)
{
	char	*tmp;
	char	*str;
	char	*ms;
	char	*decimal;

	ms = ft_itoa(data->frame_time);
	decimal = ft_itoa((data->frame_time - floor(data->frame_time)) * 100);
	if (!ms || !decimal)
		return (free(ms), free(decimal));
	str = ft_strjoin(ms, ".");
	if (!str)
		return (free(ms), free(decimal));
	tmp = ft_strjoin(str, decimal);
	free(str);
	if (!tmp)
		return (free(ms), free(decimal));
	str = ft_strjoin(tmp, "ms");
	if (!str)
		return (free(ms), free(decimal), free(tmp));
	mlx_string_put(data->mlx, data->mlx_win, 15, 15, 0x00FFFFFF, str);
	return (free(ms), free(decimal), free(tmp), free(str));
}

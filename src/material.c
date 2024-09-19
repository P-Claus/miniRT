/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:15:30 by efret             #+#    #+#             */
/*   Updated: 2024/09/19 20:15:55 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_material	default_material(void)
{
	t_material	ret;

	ret.albedo = (t_rgb){0.18, 0.18, 0.18};
	ret.k_s = 0.8;
	ret.alpha = 7;
	ret.k_d = 1;
	ret.k_a = 0.05;
	return (ret);
}

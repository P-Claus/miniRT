/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:39:47 by efret             #+#    #+#             */
/*   Updated: 2024/08/18 18:00:39 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

struct timeval	time_diff(struct timeval start, struct timeval end)
{
	struct timeval	diff;

	diff.tv_sec = end.tv_sec - start.tv_sec;
	diff.tv_usec = end.tv_usec - start.tv_usec;
	if (diff.tv_usec < 0)
	{
		diff.tv_sec--;
		diff.tv_usec += 1E6;
	}
	if (diff.tv_sec < 0)
		return (errno = EINVAL, diff);
	return (diff);
}

static inline float	time_diff_to_ms(struct timeval diff)
{
	return ((float)diff.tv_sec * 1000 + (float)diff.tv_usec / 1000);
}

float	frame_time(struct timeval start, struct timeval end)
{
	struct timeval	diff;

	diff = time_diff(start, end);
	return (time_diff_to_ms(diff));
}

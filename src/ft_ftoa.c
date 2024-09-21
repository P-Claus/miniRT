/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:34:21 by efret             #+#    #+#             */
/*   Updated: 2024/09/21 16:45:21 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	ft_strjoin_char(char **str, char c)
{
	char *tmp;
	char *new_str;
	size_t	i;

	if (*str == NULL)
	{
		*str = malloc(1);
		if (!*str)
			return (1);
		(*str)[0] = '\0';
	}
	new_str = malloc((ft_strlen(*str) + 2));
	if (!new_str)
		return (1);
	i = -1;
	while ((*str)[++i])
		new_str[i] = (*str)[i];
	new_str[i] = c;
	new_str[i + 1] = '\0';
	tmp = *str;
	*str = new_str;
	free(tmp);
	return (0);
}

char	*ft_ftoa(float f, int prec)
{
	char	*res;
	char	*tmp;
	char	*dec;

	tmp = ft_itoa(f);
	dec = ft_itoa((f - floor(f)) * pow(10, fmax(fmin(prec, 6), 0)));
	if (!tmp || !dec)
		return (free(tmp), free(dec), NULL);
	if (ft_strjoin_char(&tmp, '.'))
		return (free(tmp), free(dec), NULL);
	res = ft_strjoin(tmp, dec);
	return (free(tmp), free(dec), res);
}

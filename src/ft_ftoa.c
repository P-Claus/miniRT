/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:34:21 by efret             #+#    #+#             */
/*   Updated: 2024/09/22 18:00:57 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	ft_strjoin_char(char **str, char c)
{
	char	*tmp;
	char	*new_str;
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

int	ft_strstrip_char(char **str)
{
	size_t	len;

	if (!*str)
		return (0);
	len = strlen(*str);
	if (!len)
		return (0);
	(*str)[len - 1] = 0;
	return (0);
}

int	ft_strjoin2(char **s, char *add)
{
	size_t	len1;
	size_t	len2;
	char	*tmp;

	if (add && !*s)
		*s = ft_calloc(1, 1);
	if (!*s || !add)
		return (1);
	tmp = *s;
	len1 = ft_strlen(tmp);
	len2 = ft_strlen(add);
	*s = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!*s)
		return (free(tmp), 1);
	ft_memcpy(*s, tmp, len1);
	ft_memcpy(&(*s)[len1], add, len2);
	(*s)[len1 + len2] = 0;
	free(tmp);
	free(add);
	return (0);
}

char	*ft_ftoa(float f, int prec)
{
	char	*res;
	int		fract;
	float	zeros;

	res = NULL;
	if (f < 0)
		res = ft_strdup("-");
	if (ft_strjoin2(&res, ft_itoa(floor(fabs(f)))))
		return (free(res), NULL);
	prec = fmin(fmax(prec, 0), 6);
	if (!prec)
		return (res);
	ft_strjoin_char(&res, '.');
	fract = (fabs(f) - floor(fabs(f))) * pow(10, prec);
	zeros = 0;
	if (round(f) != f || !fract)
		zeros = prec - 1 - log10(fract);
	while (zeros-- > 0 && prec-- - 1 > 0)
		ft_strjoin_char(&res, '0');
	if (ft_strjoin2(&res, ft_itoa(fract)))
		return (free(res), NULL);
	return (res);
}

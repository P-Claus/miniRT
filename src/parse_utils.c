/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 08:57:40 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/12 19:46:27 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	count_digits(const char *str)
{
	int		count_b_dot;
	int		count_a_dot;
	int		iter;
	bool	passed_dot;

	count_b_dot = 0;
	count_a_dot = 0;
	iter = 0;
	passed_dot = false;
	if (str[iter] == '-')
		iter++;
	while ((str[iter] >= '0' && str[iter] <= '9') || str[iter] == '.')
	{
		if (str[iter] == '.')
			passed_dot = true;
		if (passed_dot == true)
			count_a_dot++;
		else if (passed_dot == false)
			count_b_dot++;
		iter++;
	}
	if (count_b_dot > 4 || count_a_dot > 4)
		return (false);
	else
		return (true);
}

int	count_items_in_split(char **split, int nb_needed)
{
	int	iter;

	iter = 0;
	while (split[iter])
		iter++;
	if (iter == nb_needed)
		return (0);
	else
		return (1);
}

static int	is_valid_character(char c)
{
	if (!ft_isdigit(c) && !(c == '.') && !(c == '-'))
		return (1);
	return (0);
}

int	check_digits_in_coordinates(char **split, int iter)
{
	int		word_iter;
	bool	passed_dot;
	int		dec_nb;

	dec_nb = 0;
	word_iter = 0;
	passed_dot = false;
	while (split[iter])
	{
		while (split[iter][word_iter] && split[iter][word_iter] != '\0')
		{
			if (is_valid_character(split[iter][word_iter]) || dec_nb > 2)
				return (1);
			if (passed_dot == true)
				dec_nb++;
			if (split[iter][word_iter] == '.')
				passed_dot = true;
			word_iter++;
		}
		iter++;
		dec_nb = 0;
		word_iter = 0;
		passed_dot = false;
	}
	return (0);
}

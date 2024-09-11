/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 08:57:40 by pclaus            #+#    #+#             */
/*   Updated: 2024/09/11 22:16:49 by pclaus           ###   ########.fr       */
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

static void	init_data(int *iter, int *word_iter, int *dec_nb, bool *passed_dot)
{
	iter = 0;
	dec_nb = 0;
	word_iter = 0;
	passed_dot = false;
}

static void	reset_data(int *word_iter, int *dec_nb, bool *passed_dot)
{
	passed_dot = false;
	dec_nb = 0;
	word_iter = 0;
}

int	check_digits_in_coordinates(char **split)
{
	int		iter;
	int		word_iter;
	bool	passed_dot;
	int		dec_nb;

	init_data(&iter, &word_iter, &dec_nb, &passed_dot);
	while (split[iter])
	{
		while (split[iter][word_iter] && split[iter][word_iter] != '\0')
		{
			if ((!ft_isdigit(split[iter][word_iter])
				&& !(split[iter][word_iter] == '.')
				&& !(split[iter][word_iter] == '-'))
				|| dec_nb > 2)
				return (1);
			if (passed_dot == true)
				dec_nb++;
			if (split[iter][word_iter] == '.')
				passed_dot = true;
			word_iter++;
		}
		iter++;
		reset_data(&iter, &word_iter, &passed_dot);
	}
	return (0);
}

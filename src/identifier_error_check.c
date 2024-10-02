/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier_error_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:43:11 by pclaus            #+#    #+#             */
/*   Updated: 2024/10/02 13:56:12 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	init_identifiers_count(t_identifier_count *id_count)
{
	id_count->a_count = 0;
	id_count->c_count = 0;
	id_count->l_count = 0;
	id_count->sp_count = 0;
	id_count->pl_count = 0;
	id_count->cy_count = 0;
	id_count->co_count = 0;
}

static int	identifiers_error_check(t_identifier_count *id_count)
{
	if (id_count->a_count != 1 || id_count->c_count != 1
		|| id_count->l_count != 1)
		return (1);
	return (0);
}

static int	check_capital_identifier(t_identifier_count *id_count, char *buffer)
{
	if (buffer[0] == 'A')
		id_count->a_count++;
	else if (buffer[0] == 'C')
		id_count->c_count++;
	else if (buffer[0] == 'L')
		id_count->l_count++;
	return (0);
}

static int	check_shape_identifier(t_identifier_count *id_count, char *buffer)
{
	if (buffer[0] == 's' && buffer[1] == 'p')
		id_count->sp_count++;
	else if (buffer[0] == 'p' && buffer[1] == 'l')
		id_count->pl_count++;
	else if (buffer[0] == 'c' && buffer[1] == 'y')
		id_count->cy_count++;
	else if (buffer[0] == 'c' && buffer[1] == 'o')
		id_count->co_count++;
	return (0);
}

int	count_identifiers_for_initialization(int fd, t_identifier_count *id_count,
		char *buffer)
{
	init_identifiers_count(id_count);
	while (buffer != NULL)
	{
		buffer = get_next_line(fd);
		if (buffer == NULL)
			break ;
		check_capital_identifier(id_count, buffer);
		check_shape_identifier(id_count, buffer);
		free(buffer);
	}
	free(buffer);
	if (identifiers_error_check(id_count) == 1)
		return (1);
	return (0);
}

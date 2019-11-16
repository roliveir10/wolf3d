/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:19:12 by roliveir          #+#    #+#             */
/*   Updated: 2019/11/16 10:42:41 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				wolf_atoi_player(char *str, int *i)
{
	while (str[*i] == 32)
		(*i)++;
	if (str[*i] == 'X')
		return (1);
	return (0);
}

int				wolf_check_map(short **map, int x, int y)
{
	int			i;
	int			error;

	i = -1;
	error = 1;
	while (++i < x)
		if (!map[0][i])
			error = 0;
	i = -1;
	while (++i < x)
		if (!map[y - 1][i])
			error = 0;
	i = -1;
	while (++i < y)
		if (!map[i][0])
			error = 0;
	i = -1;
	while (++i < y)
		if (!map[i][x - 1])
			error = 0;
	if (!error)
		ft_putendl_fd("wolf3d: map error", 2);
	return (error);
}

int				wolf_check_player(char **str)
{
	int			i;
	int			count;

	i = -1;
	count = 0;
	while ((*str)[++i])
		if ((*str)[i] == 'X')
			count++;
	if (count != 1)
		ft_strdel(str);
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:52:09 by oboutrol          #+#    #+#             */
/*   Updated: 2019/09/22 17:59:49 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

t_dist			ray_cast(t_player player, t_map map)
{
	t_dist		dist;
	int			startx;
	double		f_x;
	int			starty;
	double		f_y;
	int			addx;
	int			addy;

	dist.d = 1;
	dist.norm = 0;
	dist.rel = 0;
	addx = cos(player.angle) > 0 ? 1 : -1;
	addy = sin(player.angle) > 0 ? 1 : -1;
	startx = addx > 0 ? ((int)player.pos.x) + 1 : (int)player.pos.x;
	starty = addy > 0 ? ((int)player.pos.y) + 1 : (int)player.pos.y;
	//startx = (int)player.pos.x + addx;
	//starty = (int)player.pos.y + addy;
	while (startx < map.x && startx > 0)
	{
		f_x = cos(player.angle) * startx + player.pos.y
				- cos(player.angle) * player.pos.x;
		if (!(f_x < 0 || f_x >= map.y))
		{
			if (map.map[startx - 1][(int)f_x] != map.map[startx][(int)f_x])
			{
				dist.d = sqrt(pow(player.pos.x - addx - (double)startx, 2)
						+ pow(player.pos.y - f_x, 2));
				return (dist);
			}
		}
		startx += addx;
	}
	if (cos(player.angle) == 0)
		return (dist);
	while (starty < map.y && starty > 0)
	{
		f_y = (starty - player.pos.y) / cos(player.angle) + player.pos.x;
		if (!(f_y < 0 || f_y > map.x))
		{
			if (map.map[starty - 1][(int)f_y] != map.map[starty][(int)f_y])
			{
				dist.d = sqrt(pow(player.pos.y - addy - (double)starty, 2)
						+ pow(player.pos.x - f_y, 2));
				return (dist);
			}
		}
		starty += addy;
	}
	return (dist);
}

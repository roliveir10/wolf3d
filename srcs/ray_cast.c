/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:52:09 by oboutrol          #+#    #+#             */
/*   Updated: 2019/09/21 19:46:37 by oboutrol         ###   ########.fr       */
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
	int			starty;
	int			addx;
	int			addy;

	dist.d = 0;
	dist.norm = 0;
	dist.rel = 0;
	addx = cos(player.angle) > 0 ? 1 : -1;
	addy = sin(player.angle) > 0 ? 1 : -1;
	startx = addx > 0 ? (int)player.pos.x + 1 : (int)player.pos.x;
	starty = addy > 0 ? (int)player.pos.y + 1 : (int)player.pos.y;
	while (startx <= map.x && startx >= 0)
	{
		ft_putnbr(startx);
		ft_putstr(" _ ");
		printf("%f |\n", cos(player.angle) * startx + player.pos.y
				- cos(player.angle) * player.pos.x);
		startx += addx;
	}
	ft_putstr("----------------\n");
	if (cos(player.angle) == 0)
		return (dist);
	while (starty <= map.y && starty >= 0)
	{
		ft_putnbr(starty);
		ft_putstr(" _ ");
		printf("%f |\n", (starty - player.pos.y) / cos(player.angle)
				+ player.pos.x);
		starty += addy;
	}
	return (dist);
}


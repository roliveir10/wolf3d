/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:52:09 by oboutrol          #+#    #+#             */
/*   Updated: 2019/09/28 19:57:01 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static void		ray_assign_value(t_vector2d pos, t_dda *dda, double alpha)
{
	double		tmpx;
	double		tmpy;

	dda->posx = (int)pos.x;
	dda->posy = (int)pos.y;
	dda->delta_x = fabs(1 / cos(alpha));
	dda->delta_y = fabs(1 / cos(90 * M_PI / 180 - alpha));
	tmpx = cos(alpha);
	tmpy = sin(alpha);
	dda->step_x = tmpx < 0 ? -1 : 1;
	dda->step_y = tmpy < 0 ? -1 : 1;
	if (tmpx < 0)
		dda->next_dx = (pos.x - dda->posx) * dda->delta_x;
	else
		dda->next_dx = (dda->posx + 1.0 - pos.x) * dda->delta_x;
	if (tmpy < 0)
		dda->next_dy = (pos.y - dda->posy) * dda->delta_y;
	else
		dda->next_dy = (dda->posy + 1.0 - pos.y) * dda->delta_y;
}

static void		ray_dda(t_dda *dda, short **map)
{
	while (!dda->hit)
	{
		if (dda->next_dx < dda->next_dy)
		{
			dda->next_dx += dda->delta_x;
			dda->posx += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->next_dy += dda->delta_y;
			dda->posy += dda->step_y;
			dda->side = 1;
		}
		if (map[dda->posy][dda->posx] == 1)
			dda->hit = 1;
	}
}

t_dist			ray_cast(t_player player, t_map map)
{
	t_dda		dda;
	t_dist		dist;

	ft_bzero(&dda, sizeof(t_dda));
	ft_bzero(&dist, sizeof(t_dist));
	ray_assign_value(player.pos, &dda, player.angle);
	ray_dda(&dda, map.map);
	if (dda.side)
	{
		dist.d = (dda.posy - player.pos.y + (1 - dda.step_y) / 2)
			/ sin(player.angle);
		dist.norm += 2;
		if (sin(player.angle) > 0)
			dist.norm++;
	}
	else
	{
		dist.d = (dda.posx - player.pos.x + (1 - dda.step_x) / 2)
			/ sin(90 * M_PI / 180 - player.angle);
		if (cos(player.angle) > 0)
			dist.norm++;
	}
	return (dist);
}

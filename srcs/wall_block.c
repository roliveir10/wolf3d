/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 12:35:11 by oboutrol          #+#    #+#             */
/*   Updated: 2019/09/28 20:48:35 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			wall_block(t_env *env, t_vector2d tmp)
{
	int		x;
	int		y;

	x = (int)env->player.pos.x;
	y = (int)env->player.pos.y;
	if (x >= env->map.x - 1 || x < 0 || y >= env->map.y - 1 || y < 0)
	{
		if (x >= env->map.x - 1 || x < 0)
			env->player.pos.x = tmp.x;
		else if (y >= env->map.y - 1 || y < 0)
			env->player.pos.y = tmp.y;
	}
	x = (int)env->player.pos.x;
	y = (int)env->player.pos.y;
	if (env->map.map[y][x])
	{
		if (!env->map.map[y][(int)tmp.x])
			env->player.pos.x = tmp.x;
		else if (!env->map.map[(int)tmp.y][x])
			env->player.pos.y = tmp.y;
		else
			env->player.pos = tmp;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:11:06 by roliveir          #+#    #+#             */
/*   Updated: 2019/09/28 20:48:57 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		wolf_create_line(t_dist structdist, t_env *env, int pix)
{
	int		size;
	int		i;
	int		limit;
	double	dist;

	int		more;
	more = 0;

	dist = structdist.d;
	i = -1;
	size = dist < 1.0 ? SCREENY : 1.0 / dist * SCREENY;
	limit = (SCREENY - size) / 2;
	while (++i < limit)
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = 0x50AAFF;
	limit += size;
	while (i < limit)
	{
		if (structdist.rel > 0.5) //experimental
			more = 1;//
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = 0x000000
			+ ((int)(i / 10.0) << (8 * structdist.norm + more));
		i++;
	}
	limit += (SCREENY - size) / 2;
	while (i < limit)
	{
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = 0x333333;
		i++;
	}
}

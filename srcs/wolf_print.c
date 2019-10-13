/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:11:06 by roliveir          #+#    #+#             */
/*   Updated: 2019/10/12 23:43:04 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		wolf_create_line(t_dist s, t_env *env, int pix)
{
	int		size;
	int		i;
	int		limit;
	double	dist;

	int		more;
	more = 0;

	dist = s.d;
	i = -1;
	size = dist < 1.0 ? SCREENY : 2 * SCREENY / dist;
	limit = (SCREENY - size) / 2;
	while (++i < limit)
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = 0x50AAFF;
	limit += size;
	while (i < limit && i < SCREENY)
	{
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = s.norm * 10000000;
		i++;
	}
	limit += (SCREENY - size) / 2;
	while (i < limit && i < SCREENY)
	{
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = 0x333333;
		i++;
	}
}

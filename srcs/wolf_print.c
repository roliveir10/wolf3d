/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:11:06 by roliveir          #+#    #+#             */
/*   Updated: 2019/09/22 12:51:55 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		wolf_create_line(double dist, t_env *env, int pix)
{
	int		size;
	int		i;
	int		limit;

	i = -1;
	size = dist < 1.0 ? SCREENY : 1.0 / dist * SCREENY;
	limit = (SCREENY - size) / 2;
	while (++i < limit)
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = 0x50AAFF;
	limit += size;
	while (i < limit)
	{
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = 0x000000;
		i++;
	}
	limit += (SCREENY - size) / 2;
	while (i < limit)
	{
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = 0x333333;
		i++;
	}
}

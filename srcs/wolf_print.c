/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:11:06 by roliveir          #+#    #+#             */
/*   Updated: 2019/10/30 15:46:22 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

void		wolf_create_line(t_dist s, t_env *env, int pix)
{
	int		size;
	int		i;
	int		limit;
	double	dist;
	unsigned int	color;

	int		more;
	more = 0;

	color = s.norm > 2 ? 0x990000 : 0x009900;
	color += s.norm % 2 ? 0x666600 : 0;
	color += s.rel > 0.3 ? 0x000099 : 0;
	color += s.rel >0.6 ? 0x000066 : 0;
	dist = s.d;
	i = -1;
	size = dist < 1.0 ? SCREENY : 2 * SCREENY / dist;
	limit = (SCREENY - size) / 2;
	while (++i < limit)
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = 0x50AAFF;
	limit += size;
	while (i < limit && i < SCREENY)
	{
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = color;
//(unsigned int)(env->t.buffer_ptr[0]);
		i++;
	}
	limit += (SCREENY - size) / 2;
	while (i < limit && i < SCREENY)
	{
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = 0x333333;
		i++;
	}
}

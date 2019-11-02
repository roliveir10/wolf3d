/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:11:06 by roliveir          #+#    #+#             */
/*   Updated: 2019/11/02 15:23:58 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

int		wolf_getcolor(t_texture img, int x, int y, int no)
{
	int		color;
	int		c;

	c = (y * img.width[no] + x) * 4;
	color = img.buffer_ptr[no][c];
	if (color == -120 && img.buffer_ptr[no][c + 1] == 0
		&& img.buffer_ptr[no][c + 2] == -104)
		return (0xFF0000);
	color += (unsigned char)img.buffer_ptr[no][c + 1] * 256;
	color += (unsigned char)img.buffer_ptr[no][c + 2] * 256 * 256;
	return (color);
}

static int	wolf_get_column(t_dist s, t_env *env)
{
	int		column;

	column = (int)(s.rel * env->t.width[s.norm - 1]);
	if (column >= env->t.width[s.norm - 1])
		column = 0;
	return (column);
}

void		wolf_create_line(t_dist s, t_env *env, int pix)
{
	int		size;
	int		i;
	int		limit;
	unsigned int	color;
	int		column;
	int		line;
	int		limit_inf;

	column = wolf_get_column(s, env);
	i = -1;
	size = s.d < 1.0 ? SCREENY : 2 * SCREENY / s.d;
	limit = (SCREENY - size) / 2;
	while (++i < limit)
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = 0x50AAFF;
	limit_inf = limit;
	limit += size;
	while (i < limit && i < SCREENY)
	{
		line = (int)((i - limit_inf) * env->t.height[s.norm - 1] / size);
		if (line >= env->t.height[s.norm - 1])
			line = 0;
		color = wolf_getcolor(env->t, column, line, s.norm - 1);
		if (color > 0xFFFFFF || color <= 0)
			color = 0xFF0000;
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = color;
		i++;
	}
	limit += (SCREENY - size) / 2;
	while (i < limit && i < SCREENY)
	{
		env->mlx.mem_image[i * env->mlx.size_line / 4 + pix] = 0x333333;
		i++;
	}
}

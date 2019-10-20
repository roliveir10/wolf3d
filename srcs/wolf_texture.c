/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 01:58:04 by roliveir          #+#    #+#             */
/*   Updated: 2019/10/13 08:32:09 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <mlx.h>
#include "wolf.h"

int				wolf_load_texture(t_env *env)
{
	int				fd;
	static char		*path[4] = {"textures/brick.xpm", "textures/blur.xpm",
		"textures/rock.xpm", "textures/wood.xpm"};
	int				i;

	i = -1;
	while (++i < 4)
	{
		if ((fd = open(path[i], O_RDONLY)) < 0
			|| !(env->t.buffer[i] = mlx_xpm_file_to_image(env->mlx.mlx,
			path[i], &env->t.width[i], &env->t.height[i])))
		{
			ft_putendl_fd(path[i], 2);
			ft_putstr_fd("wolf: can not read texture\n", 2);
			return (0);
		}
		env->t.buffer_ptr[i] = mlx_get_data_addr(env->t.buffer[i],
				&env->t.pix[i], &env->t.size_line[i], &env->t.endian[i]);
	}
	return (1);
}

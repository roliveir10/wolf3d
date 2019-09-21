/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 01:51:37 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/24 09:52:26 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "wolf.h"

void			wolf_delenv(t_env *env)
{
	int			i;

	i = -1;
	mlx_destroy_image(env->mlx.mlx, env->mlx.image);
	if (env->map.map)
	{
		while (++i < env->map.y)
			ft_memdel((void**)&(env->map.map[i]));
		ft_memdel((void**)&env->map);
	}
	exit(1);
}

static void		wolf_initmlx(t_env *env)
{
	env->mlx.mlx = mlx_init();
	env->mlx.image = mlx_new_image(env->mlx.mlx, SCREENX, SCREENY);
	env->mlx.id = mlx_new_window(env->mlx.mlx, SCREENX, SCREENY, "wolf3d");
	env->mlx.mem_image = (unsigned int*)mlx_get_data_addr(env->mlx.image,
			&env->mlx.pix, &env->mlx.size_line, &env->mlx.endian);
}

int				main(int argc, char **argv)
{
	t_env		env;

	ft_bzero(&env, sizeof(t_env));
	if (!(env.map.map = wolf_init(argc, argv, &env.map.x, &env.map.y)))
		return (1);
	ft_print_digit_tables(env.map.map, env.map.x, env.map.y);
	wolf_initmlx(&env);
	mlx_hook(env.mlx.id, KEYPRESS, 0, wolf_keypress, (void*)&env);
	mlx_hook(env.mlx.id, REDBUTTON, 0, wolf_close, (void*)&env);
	mlx_loop(env.mlx.mlx);
	return (0);
}

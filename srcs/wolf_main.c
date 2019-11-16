/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 01:51:37 by roliveir          #+#    #+#             */
/*   Updated: 2019/11/16 13:57:04 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
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

void			wolf_loop(t_env *env)
{
	int			i;
	t_dist		structdist;
	float		tmp;

	i = -1;
	tmp = SCREENX * ((60.0 * M_PI) / 180);
	while (++i < SCREENX)
	{
		env->player.angle = (i - SCREENX / 2.0) / tmp + env->prot;
		structdist = ray_cast(env->player, env->map);
		structdist.d = structdist.d * cos(-env->player.angle + env->prot);
		wolf_create_line(structdist, env, i);
	}
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.id,
			env->mlx.image, 0, 0);
	return ;
}

int				main(int argc, char **argv)
{
	t_env		env;

	ft_bzero(&env, sizeof(t_env));
	if (!(env.map.map = wolf_init(argc, argv, &env)))
		return (1);
	if (!(wolf_check_map(env.map.map, env.map.x, env.map.y)))
		return (1);
	wolf_initmlx(&env);
	if (!wolf_load_texture(&env))
		return (1);
	wolf_loop(&env);
	mlx_hook(env.mlx.id, KEYPRESS, 0, wolf_keypress, (void*)&env);
	mlx_hook(env.mlx.id, REDBUTTON, 0, wolf_close, (void*)&env);
	mlx_hook(env.mlx.id, KEYRELEASE, 0, wolf_keyrelease, (void*)&env);
	mlx_loop(env.mlx.mlx);
	return (0);
}

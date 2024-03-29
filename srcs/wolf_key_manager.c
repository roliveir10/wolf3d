/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_key_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 02:46:35 by roliveir          #+#    #+#             */
/*   Updated: 2019/11/16 13:46:49 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf.h"

static void		wolf_escap(t_env *env, int keycode)
{
	(void)keycode;
	wolf_delenv(env);
}

static void		wolf_pos(t_env *env, int keycode)
{
	t_vector2d	tmp;

	tmp = env->player.pos;
	if (keycode == KLEFT)
		env->prot -= 3.0 * M_PI / 180.0;
	else if (keycode == KRIGHT)
		env->prot += 3.0 * M_PI / 180.0;
	else if (keycode == KFOR)
	{
		env->player.pos.x += COEFF * cos(env->prot);
		env->player.pos.y += COEFF * sin(env->prot);
	}
	if (keycode == KBACK)
	{
		env->player.pos.x -= COEFF * cos(env->prot);
		env->player.pos.y -= COEFF * sin(env->prot);
	}
	wall_block(env, tmp);
	wolf_loop(env);
}

int				wolf_keypress(int keycode, void *param)
{
	static int	tkey[NBR_KEY] = {KESCAP, KFOR, KBACK, KLEFT, KRIGHT};
	static void	(*func[NBR_KEY])(t_env*, int) = {wolf_escap, wolf_pos,
		wolf_pos, wolf_pos, wolf_pos};
	int			i;

	i = -1;
	while (++i < NBR_KEY)
		if (tkey[i] == keycode)
			((t_env*)param)->keypress[i] = 1;
	i = -1;
	while (++i < NBR_KEY)
		if (((t_env*)param)->keypress[i] == 1)
			func[i]((t_env*)param, tkey[i]);
	return (0);
}

int				wolf_keyrelease(int keycode, void *param)
{
	static int	tkey[NBR_KEY] = {KESCAP, KFOR, KBACK, KLEFT, KRIGHT};
	int			i;

	i = -1;
	while (++i < NBR_KEY)
		if (tkey[i] == keycode)
		{
			((t_env*)param)->keypress[i] = 0;
			return (0);
		}
	return (0);
}

int				wolf_close(void *param)
{
	wolf_delenv((t_env*)param);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_player_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:31:15 by roliveir          #+#    #+#             */
/*   Updated: 2019/11/16 13:33:56 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_vector2d			wolf_get_player_pos(t_env env, t_token *token)
{
	t_vector2d		pos;
	int				count;

	count = 0;
	ft_bzero(&pos, sizeof(t_vector2d));
	while (token && token->next)
	{
		count++;
		if (token->player == 1)
		{
			pos.x = (float)(count % (env.map.x + 1) + 0.5);
			pos.y = (float)(count / (env.map.y + 1) + 0.5);
			break ;
		}
		token = token->next;
	}
	return (pos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 04:21:05 by roliveir          #+#    #+#             */
/*   Updated: 2019/11/16 10:00:41 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wolf.h"

t_token				*wolf_free_tokenlst(t_token **token)
{
	if (*token && (*token)->next)
		wolf_free_tokenlst(&(*token)->next);
	if (*token)
		ft_memdel((void**)token);
	return (NULL);
}

void				wolf_free_map(int y, short ***map)
{
	if (!map || !*map)
		return ;
	while (--y + 1)
		ft_memdel((void**)map[y]);
	ft_memdel((void**)map);
}

t_token				*wolf_alloc_first_token(int value)
{
	t_token			*token;

	if (!(token = (t_token*)ft_memalloc(sizeof(t_token))))
		return (NULL);
	token->value = (short)value;
	return (token);
}

int					wolf_alloc_token(t_token **token, int value)
{
	t_token			*tmp;

	tmp = *token;
	while ((*token)->next)
		*token = (*token)->next;
	if (!((*token)->next = (t_token*)ft_memalloc(sizeof(t_token))))
	{
		wolf_free_tokenlst(&tmp);
		return (0);
	}
	(*token)->next->value = value;
	if (value == -2)
	{
		(*token)->next->value = 0;
		(*token)->next->player = 1;
	}
	(*token)->next->eol = value == -1 ? 1 : 0;
	*token = tmp;
	return (1);
}

short				**wolf_alloc_map(int x, int y)
{
	short			**map;
	int				i;

	i = -1;
	if (!(map = (short**)ft_memalloc(sizeof(short*) * y)))
		return (NULL);
	while (++i < y)
		if (!(map[i] = (short*)ft_memalloc(sizeof(short) * x)))
		{
			wolf_free_map(y, &map);
			return (NULL);
		}
	return (map);
}

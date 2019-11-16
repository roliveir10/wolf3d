/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 03:35:31 by roliveir          #+#    #+#             */
/*   Updated: 2019/11/16 12:41:23 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "wolf.h"

static char			*wolf_getfile(int fd)
{
	char			*str;
	ssize_t			ret;
	char			buf[BUFF_SIZE + 1];

	if (!(str = ft_strnew(1)))
		return (NULL);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!ft_isascii(buf[0]))
			return (ft_strdel(&str));
		if (!(str = ft_strjoinf(str, buf)))
			return (ft_strdel(&str));
	}
	if (ret == -1)
		return (ft_strdel(&str));
	return (str);
}

static t_token		*wolf_get_tokenlst(char *str)
{
	t_token			*token;
	int				i;

	i = 0;
	if (!ft_atoic(str) || !(token = wolf_alloc_first_token(ft_atoi_p(str, &i))))
		return (NULL);
	while (str[i])
	{
		if (!ft_atoic(&str[i]) && str[i] == '\n')
		{
			if (!wolf_alloc_token(&token, -1))
				return (NULL);
			i++;
		}
		else if (ft_atoic(&str[i]))
		{
			if (!wolf_alloc_token(&token, ft_atoi_p(str, &i)))
				return (NULL);
		}
		else if (wolf_atoi_player(str, &i))
		{
			str[i] = '0';
			ft_atoi_p(str, &i);
			if (!wolf_alloc_token(&token, -2))
				return (NULL);
		}
		else
			return (wolf_free_tokenlst(&token));
	}
	return (token);
}

static int			wolf_get_mapsize(t_token *token, int height)
{
	int				save;
	int				tmp;

	tmp = 0;
	save = -1;
	while (token && token->next)
	{
		if (height && token->eol)
			tmp++;
		else if (!height && !token->eol)
			tmp++;
		else if (!height && token->eol && (save == -1 || save == tmp))
		{
			save = tmp;
			tmp = 0;
		}
		token = token->next;
	}
	return (height ? tmp + 1 : tmp);
}

void				wolf_fillmap(t_token *token, short ***map)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (token && token->next)
	{
		if (token->eol)
		{
			i++;
			j = 0;
		}
		else
		{
			(*map)[i][j] = token->value;
			j++;
		}
		token = token->next;
	}
}

short				**wolf_getmap(int fd, t_env *env)
{
	char			*str;
	short			**map;
	t_token			*token;

	if (!(str = wolf_getfile(fd)))
		return (NULL);
	if (wolf_check_player(&str) != 1)
		return (NULL);
	token = wolf_get_tokenlst(str);
	ft_strdel(&str);
	if (!token)
		return (NULL);
	env->map.y = wolf_get_mapsize(token, 1);
	env->map.x = wolf_get_mapsize(token, 0);
	env->player.pos = wolf_get_player_pos(*env, token);
	if (!(map = wolf_alloc_map(env->map.x, env->map.y)))
		return (NULL);
	wolf_fillmap(token, &map);
	wolf_free_tokenlst(&token);
	return (map);
}

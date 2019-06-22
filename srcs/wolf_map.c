/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 03:35:31 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/22 06:10:42 by roliveir         ###   ########.fr       */
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
		if (!ft_isascii(buf[0]))
		{
			ft_strdel(&str);
			return (NULL);
		}
		if (!(str = ft_strjoinf(str, buf)))
		{
			ft_strdel(&str);
			return (NULL);
		}
	}
	if (ret == -1)
	{
		ft_strdel(&str);
		return (NULL);
	}
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
			wolf_alloc_token(&token, -1);
		else if (ft_atoic(&str[i]))
			wolf_alloc_token(&token, ft_atoi_p(&str[i], &i));
		else
		{
			wolf_free_tokenlst(&token);
			return (NULL);
		}
		i++;
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
	return (tmp);
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

short				**wolf_getmap(int fd, int *sx, int *sy)
{
	char			*str;
	short			**map;
	t_token			*token;

	if (!(str = wolf_getfile(fd)))
		return (NULL);
	token = wolf_get_tokenlst(str);
	ft_strdel(&str);
	if (!token)
		return (NULL);
	*sy = wolf_get_mapsize(token, 1);
	*sx = wolf_get_mapsize(token, 0);
	if (!(map = wolf_alloc_map(*sx, *sy)))
		return (NULL);
	wolf_fillmap(token, &map);
	wolf_free_tokenlst(&token);
	return (map);
}

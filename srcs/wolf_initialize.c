/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_initialize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 03:36:30 by roliveir          #+#    #+#             */
/*   Updated: 2019/11/16 12:46:07 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "wolf.h"

static int		wolf_usage(int argc)
{
	if (argc < 2)
	{
		ft_putendl_fd("usage: ./wolf3d file", 2);
		return (1);
	}
	return (0);
}

short			**wolf_init(int argc, char **argv, t_env *env)
{
	int			fd;
	short		**map;

	if (wolf_usage(argc))
		return (0);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putstr_fd("wolf3d: cannot open ", 2);
		ft_putendl_fd(argv[1], 2);
		return (0);
	}
	if (!(map = wolf_getmap(fd, env)))
	{
		ft_putendl_fd("wolf3d: map error", 2);
		close(fd);
		return (0);
	}
	close(fd);
	return (map);
}

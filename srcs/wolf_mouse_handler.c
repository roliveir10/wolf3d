/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_mouse_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 11:04:15 by roliveir          #+#    #+#             */
/*   Updated: 2019/10/31 17:21:54 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf.h"
#include <stdio.h>

int					wolf_mouse_move(int x, int y, void *param)
{
	static int		sx = 0;

	(void)y;
	if (sx < x)
		((t_env*)param)->prot += 3.0 * M_PI / 180.0;
	else if (sx > x)
	{
		((t_env*)param)->prot -= 3.0 * M_PI / 180.0;
		if (((t_env*)param)->prot > 2 * M_PI)
			((t_env*)param)->prot -= 2 * M_PI;
		if (((t_env*)param)->prot < 0)
			((t_env*)param)->prot += 2 * M_PI;
	}
	sx = x;
	wolf_loop((t_env*)param);
	return (0);
}

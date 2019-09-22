/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 01:50:50 by roliveir          #+#    #+#             */
/*   Updated: 2019/09/22 17:59:54 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WOLF_H
# define _WOLF_H

# include "libft.h"

# define SCREENX 2080
# define SCREENY 1170
# define ANGLE 30

# define NBR_KEY 5

/*
**	ENUM
*/

typedef enum			e_event
{
	KEYPRESS = 2,
	REDBUTTON = 17
}						t_event;

typedef enum			e_key
{
	KESCAP = 53,
	KLEFT = 123,
	KRIGHT = 124,
	KFOR = 126,
	KBACK = 125
}						t_key;

/*
**	STRUCT
*/

typedef	struct			s_vector2d
{
	double				x;
	double				y;
}						t_vector2d;

typedef struct			s_mlx
{
	void				*mlx;
	void				*image;
	void				*id;
	unsigned int		*mem_image;
	int					pix;
	int					size_line;
	int					endian;
}						t_mlx;

typedef struct			s_player
{
	t_vector2d			pos;
	double				angle;
}						t_player;

typedef struct			s_dist
{
	double				d;
	int					norm;
	double				rel;
}						t_dist;

typedef struct			s_token
{
	short				value;
	char				eol;
	struct s_token		*next;
}						t_token;

typedef struct			s_map
{
	short				**map;
	int					x;
	int					y;
}						t_map;

typedef struct			s_env
{
	t_mlx				mlx;
	t_map				map;
	t_player			player;
	double				prot;
}						t_env;

short					**wolf_init(int argc, char **argv, int *sx, int *sy);
void					wolf_delenv(t_env *env);

/*
**	keys
*/

int						wolf_keypress(int keycode, void *param);
int						wolf_close(void *param);

/*
**	parsing
*/

short					**wolf_getmap(int fd, int *sx, int *sy);

/*
**	alloc
*/

t_dist					ray_cast(t_player player, t_map map);
void					intersect(double x, double y, double angle);
int						wolf_alloc_token(t_token **token, int value);
t_token					*wolf_alloc_first_token(int value);
void					wolf_free_tokenlst(t_token **token);
short					**wolf_alloc_map(int x, int y);

/*
**	print
*/

void					wolf_create_line(double dist, t_env *env, int pix);
void					wolf_loop(t_env *env);

#endif

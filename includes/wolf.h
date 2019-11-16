/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 01:50:50 by roliveir          #+#    #+#             */
/*   Updated: 2019/11/02 09:55:43 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WOLF_H
# define _WOLF_H

# include "libft.h"
# include <mlx.h>

# define SCREENX 2080
# define SCREENY 1170
# define ANGLE 30
# define COEFF 0.2

# define NBR_KEY 5

/*
**	ENUM
*/

typedef enum			e_event
{
	KEYPRESS = 2,
	KEYRELEASE = 3,
	MOUSEMOVE = 6,
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
	t_vector2d			pos;
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

typedef struct			s_texture
{
	char				*buffer[4];
	char				*buffer_ptr[4];
	int					width[4];
	int					height[4];
	int					pix[4];
	int					size_line[4];
	int					endian[4];

}						t_texture;

typedef struct			s_env
{
	t_mlx				mlx;
	t_map				map;
	t_player			player;
	char				keypress[NBR_KEY];
	double				prot;
	t_texture			t;

}						t_env;

typedef struct			s_dda
{
	int					posx;
	int					posy;
	double				next_dx;
	double				next_dy;
	double				delta_x;
	double				delta_y;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	int					pwd;
}						t_dda;

short					**wolf_init(int argc, char **argv, t_env *env);
void					wolf_delenv(t_env *env);

/*
**	keys
*/

int						wolf_keypress(int keycode, void *param);
int						wolf_keyrelease(int keycode, void *param);
int						wolf_close(void *param);
int						wolf_mouse_move(int x, int y, void *param);
int						wall_block(t_env *env, t_vector2d tmp);

/*
**	parsing
*/

short					**wolf_getmap(int fd, int *sx, int *sy);
int						wolf_check_map(short **map, int x, int y);
int						wolf_check_player(char **str);

/*
**	texture
*/

int						wolf_load_texture(t_env *env);

/*
**	alloc
*/

t_dist					ray_cast(t_player player, t_map map);
void					intersect(double x, double y, double angle);
int						wolf_alloc_token(t_token **token, int value);
t_token					*wolf_alloc_first_token(int value);
t_token					*wolf_free_tokenlst(t_token **token);
short					**wolf_alloc_map(int x, int y);

/*
**	print
*/

void					wolf_create_line(t_dist dist, t_env *env, int pix);
void					wolf_loop(t_env *env);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:22:32 by mallaoui          #+#    #+#             */
/*   Updated: 2023/07/07 17:22:35 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H



# include <stdio.h>
# include <unistd.h>
# include "./libft/libft.h"
# include <mlx.h>
#include <math.h>

#define MOVE_SPEED 5
#define ROT_SPEED 0.05
#define LINE_LEN 30

#define LINE_COLOR 0xfff
#define PLAYER_COLOR 0xff0000
#define WALL_COLOR 0x943a5b
#define SPACE_COLOR 0x000000
#define GROUND_COLOR 0xffffff

#define RIGHT -1
#define LEFT  1

# define KEY_W 13
# define KEY_S 1 
# define KEY_A 0 
# define KEY_D 2 
# define KEY_LEFT 123 
# define KEY_RIGHT 124
# define TILE_LEN 64.0

#define NUM_RAYS 320
#define FOV_ANGLE 60 * (M_PI / 180)


typedef struct s_pars
{
	char    *no;
	char    *so;
	char    *we;
	char    *ea;
	int     *f_rgb;
	int     *c_rgb;
	char    **map;
}           t_pars;



typedef struct s_data
{
	void    *img;
	char    *addr;
	int     bits_per_M_PIxel;
	int     line_length;
	int     endian;
}           t_data;



typedef struct s_vars
{
	int     map_w;
	int     map_h;
}           t_vars;

typedef struct s_rays
{
	int	 ray_id;
	double ray_angle;
	double wall_hit_x;
	double wall_hit_y;
	double distance;
}			t_rays;

typedef struct s_player
{
	double  player_x;
	double  player_y;
	double  player_angle;
	double  offset;
	double  move_player_x;
	double  move_player_y;
	double  player_center_x;
	double  player_center_y;
	char    player_direction;
	int     key_w;
	int     key_s;
	int     key_a;
	int     key_d;
	int     key_left;
	int     key_right;
	int		direction_forward;
	int		direction_side;
	t_rays	*rays;
}               t_player;



typedef struct s_mlx
{
	void    *mlx;
	void    *win;
	int  width;
	int  height;
	t_data  img;
	t_pars  *pars;
	t_vars  *vars;
	t_player *player;
}           t_mlx;


void	texture_parsing(t_pars *pars, char **file);
void	error(char *str);
void	map_pars(t_pars *pars, char **file);
void	color_pars(t_pars *pars, char **file);
int		is_player(char c);
double normalize_angle(double angle);
#endif
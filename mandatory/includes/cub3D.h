/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:22:32 by mallaoui          #+#    #+#             */
/*   Updated: 2023/08/08 22:04:14 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include "../../libft/libft.h"
# include <mlx.h>
# include <math.h>
# define MOVE_SPEED 5
# define ROT_SPEED 0.04
# define LINE_LEN 30
# define PROJ_DIST 277 // the bigger the number the bigger the walls look
# define TILE_SIZE 64.0
# define FOV_ANGLE 1.0471975512 //(60 * (3.1415926535897 / 180))
# define SHADE_RANGE 800
# define LIMIT 5
# define LINE_COLOR 0xfff
# define PLAYER_COLOR 0xff0000
# define WALL_COLOR 0x943a5b
# define SPACE_COLOR 0x000000
# define GROUND_COLOR 0xC3CB6E
# define WIDTH 1000
# define WALL_MULIP 3
# define HEIGHT 700
# define RIGHT -1
# define LEFT  1
# define KEY_W 13
# define KEY_S 1 
# define KEY_A 0 
# define KEY_D 2 
# define KEY_LEFT 123 
# define KEY_RIGHT 124

typedef struct s_pars
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*f_rgb;
	int		*c_rgb;
	char	**map;
}		t_pars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
}		t_data;

typedef struct s_vars
{
	int	map_w;
	int	map_h;
}		t_vars;

typedef struct s_rays
{
	int		ray_id;
	double	ray_angle;
	double	hor_hit_x;
	double	hor_hit_y;
	double	vert_hit_x;
	double	vert_hit_y;
	int		facing_up;
	int		facing_down;
	int		facing_left;
	int		facing_right;
	int		found_horz;
	int		found_vert;
	double	dist;
	int		is_hor;
}			t_rays;

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_keys
{
	int	key_w;
	int	key_s;
	int	key_a;
	int	key_d;
	int	key_left;
	int	key_right;
}		t_keys;

typedef struct s_player
{
	t_point	pos;
	double	player_angle;
	double	offset;
	double	move_player_x;
	double	move_player_y;
	double	center_x;
	double	center_y;
	char	player_dir;
	t_keys	keys;
	int		dir_forw;
	int		dir_side;
	t_rays	*rays;
}		t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_data		img;
	t_data		textures[4];
	t_pars		*pars;
	t_vars		*vars;
	t_player	*player;
}		t_mlx;

void			texture_parsing(t_pars *pars, char **file);
void			error(char *str);
void			map_pars(t_pars *pars, char **file);
void			color_pars(t_pars *pars, char **file);
int				is_player(char c);
double			normalize_angle(double angle);
int				up_down(t_mlx *mlx);
int				left_right(t_mlx *mlx);
void			player_center(t_mlx *mlx);
void			parsing(t_pars *pars, int ac, char **av);
t_mlx			*init(double *arr, int ac, char *av[]);
int				close_window(t_mlx *mlx);
int				control_key(int keycode, t_mlx *mlx);
int				key_released(int keycode, t_mlx *mlx);
int				magic(t_mlx *mlx);
void			init_ray(t_rays *ray, double rayAngle);
void			get_ver(t_mlx *mlx, int id);
void			get_hor(t_mlx *mlx, int id);
t_point			get_wall_hit(t_mlx *mlx, int id);
double			dist_(t_point p1, t_point p2);
void			project_wall(t_mlx *mlx, int id);
t_data			*get_texture(t_mlx *mlx, int id);
void			map_w_h(t_vars *vars, t_pars *pars);
double			*player_pos(char **map);
void			set_player_dir(t_mlx *mlx);
void			player_angle(t_mlx *mlx);
void			texture_init(t_mlx *mlx);
void			handle_events(t_mlx *mlx);
void			castrays(t_mlx *mlx);
double			init_vars(t_mlx *mlx, int id, int *p_wall_h, double *count);
void			init_ray(t_rays *ray, double rayAngle);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
unsigned int	shading(int color, double dist);
int				int_color(int rgb[3]);
int				get_pixel_color(t_data *img, int x, int y);
int				check_char(char **file, int i, int j);
void			check_around(char **map, int i, int j);
char			**get_map(char **file);
void			check_map(char **map);
void			validate_map(char **map);
void			check_double(char **map);
void			remove_spaces(char **p);
int				is_map(char *file);
#endif
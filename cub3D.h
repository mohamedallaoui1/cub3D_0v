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


# define KEY_W 13
# define KEY_S 1 
# define KEY_A 0 
# define KEY_D 2 
# define KEY_LEFT 123 
# define KEY_RIGHT 124
# define MIN (a, b) (((a) < (b)) ? (a) : (b))
# define MAX (a, b) ((a) > (b) ? (a) : (b))


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
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}           t_data;



typedef struct s_vars
{
    int     map_w;
    int     map_h;
}           t_vars;



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


void    texture_parsing(t_pars *pars, char **file);
void    error(char *str);
void    map_pars(t_pars *pars, char **file);
void    color_pars(t_pars *pars, char **file);

#endif
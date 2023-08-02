/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:47:59 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/02 15:34:12 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	draw_player(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	while (x < PLAYER_SIZE)
	{
		y = 0;
		while (y < PLAYER_SIZE)
		{
			my_mlx_pixel_put(mlx, x  + (WIDTH / 10) / 2, y + (HEIGHT / 10) / 2,
				reverse_color((unsigned int)get_pixel_color(&mlx->img, x  + (WIDTH / 10) / 2, y + (HEIGHT / 10) / 2)));
			y++;
		}
		x++;
	}
}
void	draw_square(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_mlx_pixel_put(mlx, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void draw_minimap(t_mlx *mlx)
{
    int player_x = mlx->player->center_x;
    int player_y = mlx->player->center_y;
    int map_start_x = player_x - 100;
    int map_start_y = player_y - 100;
    int x = map_start_x / TILE_SIZE;
    int y = map_start_y / TILE_SIZE;

    if (x < 0)
        x = 0;
    else if (x >= mlx->vars->map_w)
        x = mlx->vars->map_w - 1;

    if (y < 0)
        y = 0;
    else if (y >= mlx->vars->map_h)
        y = mlx->vars->map_h - 1;

    while (y < mlx->vars->map_h && y < (player_y + 100) / TILE_SIZE)
    {
        x = map_start_x / TILE_SIZE;
        while (x < mlx->vars->map_w && x < (player_x + 100) / TILE_SIZE)
        {
            if (x >= 0 && y >= 0 && (mlx->pars->map[y][x] == '1' || mlx->pars->map[y][x] == ' '))
                draw_square(mlx, x * 10, y * 10, WALL_COLOR);
            x++;
        }
        y++;
    }

}


void	minimap(t_mlx *mlx)
{
	draw_player(mlx);
	draw_minimap(mlx);
}

int	magic(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	handle_events(mlx);
	castrays(mlx);
	minimap(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}

t_data	*get_texture(t_mlx *mlx, int id)
{
	if (mlx->player->rays[id].is_hor)
	{
		if (mlx->player->rays[id].facing_up)
			return (&mlx->textures[1]);
		else
			return (&mlx->textures[0]);
	}
	else
	{
		if (mlx->player->rays[id].facing_left)
			return (&mlx->textures[2]);
		else
			return (&mlx->textures[3]);
	}
}

void	project_wall(t_mlx *mlx, int id)
{
	double	val;
	int		p_wall_h;
	int		i;
	double	count;

	i = -1;
	val = init_vars(mlx, id, &p_wall_h, &count);
	while (++i < HEIGHT)
	{
		if (i < HEIGHT / 2 - p_wall_h / 2)
			my_mlx_pixel_put(mlx, id, i, shading(
					int_color(mlx->pars->c_rgb),
					(double)i / (double)(HEIGHT / 2)));
		else if (i >= HEIGHT / 2 - p_wall_h / 2
			&& i < HEIGHT / 2 + p_wall_h / 2)
			my_mlx_pixel_put(mlx, id, i,
				shading(get_pixel_color(
						get_texture(mlx, id), val, (count++ / p_wall_h)
						* mlx->textures[0].img_height),
					mlx->player->rays[id].dist / SHADE_RANGE));
		else
			my_mlx_pixel_put(mlx, id, i, shading(
					int_color(mlx->pars->f_rgb),
					(double)(HEIGHT / 2) / (double)i));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:47:59 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/04 10:18:55 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	draw_player(t_mlx *mlx, int i, int j)
{
	int	x;
	int	y;

	x = i;
	while (x < PLAYER_SIZE + i)
	{
		y = j;
		while (y < PLAYER_SIZE + j)
		{
			my_mlx_pixel_put(mlx, x, y,
				reverse_color(get_pixel_color(&mlx->img,
					x, y)));
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
	while (i < MAP_INCR)
	{
		j = 0;
		while (j < MAP_INCR)
		{
			my_mlx_pixel_put(mlx, (x + i), (y + j), color);
			j++;
		}
		i++;
	}
}
void draw_minimap(t_mlx *mlx)
{
	int	x;
	int	y;
    int map_start_x;
    int map_start_y;

	y = -1;
    map_start_y = mlx->player->center_y - MAP_SIZE / 2;
	map_start_x = mlx->player->center_x - MAP_SIZE / 2;
	while (++y < MAP_SIZE)
	{
		x = -1;
		while (++x < MAP_SIZE)
		{
    		if ((int)((map_start_x + x) / TILE_SIZE) >= 0
				&& (int)((map_start_x + x) / TILE_SIZE) < mlx->vars->map_w &&
    		    (int)((map_start_y + y) / TILE_SIZE) >= 0
				&& (int)(((map_start_y + y) / TILE_SIZE)) < mlx->vars->map_h)
    		{
    		    if (mlx->pars->map[(int)((map_start_y + y) / TILE_SIZE)][(int)((map_start_x + x) / TILE_SIZE)] == '1')
    		        draw_square(mlx, x, y, WALL_COLOR);
				else if (mlx->pars->map[(int)((map_start_y + y) / TILE_SIZE)][(int)((map_start_x + x) / TILE_SIZE)] == '2')
    		        draw_square(mlx, x, y, DOOR_COLOR);
				else
    		        draw_square(mlx, x, y, GROUND_COLOR);
    		}
		}
	}
}

void minimap(t_mlx *mlx)
{
    draw_minimap(mlx);
    draw_player(mlx, MAP_SIZE / 2, MAP_SIZE / 2);
	draw_line(mlx, (t_point){(MAP_SIZE / 2) + 2, (MAP_SIZE / 2) + 2},
		(t_point){(MAP_SIZE / 2) + 2 + (MAP_SIZE / 10) * cos(mlx->player->player_angle),
		(MAP_SIZE / 2) + 2 + (MAP_SIZE / 10) * sin(mlx->player->player_angle)});
}

int magic(t_mlx *mlx)
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
						* get_texture(mlx, id)->img_height),
					mlx->player->rays[id].dist / SHADE_RANGE));
		else
			my_mlx_pixel_put(mlx, id, i, shading(
					int_color(mlx->pars->f_rgb),
					(double)(HEIGHT / 2) / (double)i));
	}
}

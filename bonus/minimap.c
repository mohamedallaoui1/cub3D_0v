/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:15:59 by mallaoui          #+#    #+#             */
/*   Updated: 2023/08/05 23:18:53 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

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

void	draw(t_mlx *mlx, int x, int y)
{
	int	map_start_x;
	int	map_start_y;

	map_start_y = mlx->player->center_y - MAP_SIZE / 2;
	map_start_x = mlx->player->center_x - MAP_SIZE / 2;
	if ((int)((map_start_x + x) / TILE_SIZE) >= 0 \
	&& (int)((map_start_x + x) / TILE_SIZE) < \
	mlx->vars->map_w && \
	(int)((map_start_y + y) / TILE_SIZE) >= 0 \
	&& (int)(((map_start_y + y) / TILE_SIZE)) < \
	mlx->vars->map_h)
	{
		if (mlx->pars->map[(int)((map_start_y + y) / TILE_SIZE)] \
		[(int)((map_start_x + x) / TILE_SIZE)] == '1')
			draw_square(mlx, x, y, WALL_COLOR);
		else if (mlx->pars->map[(int)((map_start_y + y) / TILE_SIZE)] \
		[(int)((map_start_x + x) / TILE_SIZE)] == '2')
			draw_square(mlx, x, y, DOOR_COLOR);
		else
			draw_square(mlx, x, y, GROUND_COLOR);
	}
}

void	draw_minimap(t_mlx *mlx)
{
	int	x;
	int	y;

	y = -1;
	while (++y < MAP_SIZE)
	{
		x = -1;
		while (++x < MAP_SIZE)
			draw(mlx, x, y);
	}
}

void	draw_line(t_mlx *mlx, t_point point1, t_point point2)
{
	double	x;
	double	y;
	double	step;
	double	i;
	double	j;

	x = point1.x;
	y = point1.y;
	step = 1;
	if (fabs(point2.x - point1.x) >= fabs(point2.y - point1.y))
		step = fabs(point2.x - point1.x);
	else
		step = fabs(point2.y - point1.y);
	i = (point2.x - point1.x) / step;
	j = (point2.y - point1.y) / step;
	while (step > 0)
	{
		my_mlx_pixel_put(mlx, x, y, \
		reverse_color(get_pixel_color(mlx->img.img, x, y)));
		x += i;
		y += j;
		step--;
	}
}

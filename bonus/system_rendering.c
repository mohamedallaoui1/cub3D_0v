/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:47:59 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/03 22:49:07 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	draw_player(t_mlx *mlx, int i, int j)
{
	int	x;
	int	y;

	x = i;
	while (x < PLAYER_SIZE)
	{
		y = j;
		while (y < PLAYER_SIZE)
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
	while (i < 5)
	{
		j = 0;
		while (j < 5)
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
	int start_x;
	int start_y;

	start_x = (mlx->player->center_x - MAP_SIZE / 2) * 0.1;
	start_y = (mlx->player->center_y - MAP_SIZE / 2) * 0.1;
	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	x = 0;
	while (x < WIDTH * 0.1)
	{
		y = 0;
		while (y < HEIGHT * 0.1)
		{
			if (mlx->pars->map[(int)((start_y + y) / TILE_SIZE)][(int)((start_x + x) / TILE_SIZE)] == '1')
				draw_square(mlx, x, y, WALL_COLOR);
			y++;
		}
		x++;
	}
	
}

void	minimap(t_mlx *mlx)
{
	(void)mlx;
	draw_minimap(mlx);
	draw_player(mlx, mlx->player->center_x  * 0.1, mlx->player->center_y * 0.1);
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
						* get_texture(mlx, id)->img_height),
					mlx->player->rays[id].dist / SHADE_RANGE));
		else
			my_mlx_pixel_put(mlx, id, i, shading(
					int_color(mlx->pars->f_rgb),
					(double)(HEIGHT / 2) / (double)i));
	}
}

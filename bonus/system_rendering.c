/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:47:59 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/05 23:16:16 by mallaoui         ###   ########.fr       */
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
			my_mlx_pixel_put(mlx, x, y, \
			reverse_color(get_pixel_color(&mlx->img, \
			x, y)));
			y++;
		}
		x++;
	}
}

void	minimap(t_mlx *mlx)
{
	draw_minimap(mlx);
	draw_player(mlx, MAP_SIZE / 2, MAP_SIZE / 2);
	draw_line(mlx, (t_point){(MAP_SIZE / 2) + 2, (MAP_SIZE / 2) + 2}, \
	(t_point){(MAP_SIZE / 2) + 2 + (MAP_SIZE / 10) * \
	cos(mlx->player->player_angle), \
	(MAP_SIZE / 2) + 2 + (MAP_SIZE / 10) * sin(mlx->player->player_angle)});
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

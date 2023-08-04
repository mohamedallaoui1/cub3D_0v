/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RayCasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:08:39 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/04 22:17:27 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	castrays(t_mlx *mlx)
{
	double	rayangle;
	int		i;
	t_point	wall_hit;

	i = -1;
	player_center(mlx);
	rayangle = normalize_angle(mlx->player->player_angle - (FOV_ANGLE / 2));
	while (++i < WIDTH)
	{
		mlx->player->rays[i].ray_id = i;
		init_ray(&mlx->player->rays[i], rayangle);
		get_ver(mlx, i);
		get_hor(mlx, i);
		wall_hit = get_wall_hit(mlx, i);
		mlx->player->rays[i].dist = \
		dist_((t_point){mlx->player->center_x, mlx->player->center_y} \
		, wall_hit) * cos(rayangle - mlx->player->player_angle);
		project_wall(mlx, i);
		rayangle = normalize_angle(rayangle + FOV_ANGLE / (double)WIDTH);
	}
}

void	save_rest(t_mlx *mlx, int id, t_point intercept)
{
	t_sprite	*sprite;

	if (mlx->pars->map[(int)(intercept.y / TILE_SIZE)][(int)((intercept.x - \
		0.001 * mlx->player->rays[id].facing_left) / TILE_SIZE)] == 'c')
	{
		sprite = malloc(sizeof(t_sprite));
		sprite->x = intercept.x + TILE_SIZE / 2;
		sprite->y = intercept.y + TILE_SIZE / 2;
		add_listfront(mlx, sprite);
	}
}

void	get_ver(t_mlx *mlx, int id)
{
	t_point	intercept;
	t_point	delta;

	intercept.x = floor(mlx->player->center_x / TILE_SIZE) * \
	TILE_SIZE + TILE_SIZE * mlx->player->rays[id].facing_right;
	intercept.y = mlx->player->center_y + (intercept.x - \
	mlx->player->center_x) * tan(mlx->player->rays[id].ray_angle);
	delta.x = TILE_SIZE * (1 - 2 * (mlx->player->rays[id].facing_left));
	delta.y = (TILE_SIZE * fabs(tan(mlx->player->rays[id].ray_angle)))
		* (1 - 2 * mlx->player->rays[id].facing_up);
	while (intercept.x >= 0 && intercept.x < mlx->width && \
	intercept.y >= 0 && intercept.y < mlx->height)
	{
		if (is_collusion(mlx, (int)(intercept.y / TILE_SIZE), (int)((intercept.x - \
		0.001 * mlx->player->rays[id].facing_left) / TILE_SIZE)))
		{
			mlx->player->rays[id].vert_hit_x = intercept.x;
			mlx->player->rays[id].vert_hit_y = intercept.y;
			mlx->player->rays[id].found_vert = 1;
			return ;
		}
		// else
		// 	save_rest()
		intercept.x += delta.x;
		intercept.y += delta.y;
	}
}

int	is_collusion(t_mlx *mlx, int i, int j)
{
	if (mlx->pars->map[i][j] == '1' || mlx->pars->map[i][j] == '2')
		return (1);
	return (0);
}

void	get_hor(t_mlx *mlx, int id)
{
	t_point	intercept;
	t_point	delta;

	intercept.y = floor(mlx->player->center_y / TILE_SIZE) * \
	TILE_SIZE + TILE_SIZE * mlx->player->rays[id].facing_down;
	intercept.x = mlx->player->center_x + (intercept.y - \
	mlx->player->center_y) / tan(mlx->player->rays[id].ray_angle);
	delta.y = TILE_SIZE * (1 - 2 * (mlx->player->rays[id].facing_up));
	delta.x = (TILE_SIZE / fabs(tan(mlx->player->rays[id].ray_angle)))
		* (1 - 2 * (mlx->player->rays[id].facing_left));
	while (intercept.x >= 0 && intercept.x < mlx->width && intercept.y >= \
	0 && intercept.y < mlx->height)
	{
		if (is_collusion(mlx, (int)((intercept.y - 0.001 * \
		mlx->player->rays[id].facing_up) \
		/ TILE_SIZE), (int)((intercept.x) / TILE_SIZE)))
		{
			mlx->player->rays[id].hor_hit_x = intercept.x;
			mlx->player->rays[id].hor_hit_y = intercept.y;
			mlx->player->rays[id].found_horz = 1;
			return ;
		}
		intercept.x += delta.x;
		intercept.y += delta.y;
	}
}

t_point	get_wall_hit(t_mlx *mlx, int id)
{
	t_point	hor_hit;
	t_point	vert_hit;
	t_point	player_center;

	player_center = (t_point){mlx->player->center_x, mlx->player->center_y};
	hor_hit = (t_point){mlx->player->rays[id].hor_hit_x, \
	mlx->player->rays[id].hor_hit_y};
	vert_hit = (t_point){mlx->player->rays[id].vert_hit_x, \
	mlx->player->rays[id].vert_hit_y};
	if (mlx->player->rays[id].found_horz && \
	mlx->player->rays[id].found_vert == 0)
		return (mlx->player->rays[id].is_hor = 1, hor_hit);
	else if (mlx->player->rays[id].found_horz == 0 && \
	mlx->player->rays[id].found_vert)
		return (mlx->player->rays[id].is_hor = 0, vert_hit);
	if (dist_(player_center, hor_hit) < dist_(player_center, vert_hit)
		&& mlx->player->rays[id].found_horz && mlx->player->rays[id].found_vert)
		return (mlx->player->rays[id].is_hor = 1, hor_hit);
	else if (mlx->player->rays[id].found_horz && \
	mlx->player->rays[id].found_vert)
		return (mlx->player->rays[id].is_hor = 0, vert_hit);
	else
		return (mlx->player->rays[id].is_hor = 0, player_center);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:44:00 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/06 14:05:42 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	up_down_condition(t_mlx *mlx, t_point *old)
{
	t_point	x_y;

	x_y = (t_point){0, 0};
	if (mlx->pars->map[(int)((mlx->player->center_y
				+ LIMIT * sin(mlx->player->player_angle)
				* mlx->player->dir_forw) / TILE_SIZE)]
			[(int)((old->x + TILE_SIZE / 2) / TILE_SIZE)] == '1' || \
			mlx->pars->map[(int)((mlx->player->center_y
				+ LIMIT * sin(mlx->player->player_angle)
				* mlx->player->dir_forw) / TILE_SIZE)]
			[(int)((old->x + TILE_SIZE / 2) / TILE_SIZE)] == '2')
	{
		mlx->player->pos.y = old->y;
		x_y.y = 1;
	}
	up_down_condition_norm(mlx, old, x_y);
	return (0);
}

void	check_and_slide(t_mlx *mlx, t_point	x_y, t_point *old)
{
	if (mlx->pars->map[(int)((mlx->player->center_y - \
	LIMIT * cos(mlx->player->player_angle) * \
	mlx->player->dir_side) / TILE_SIZE)]
	[(int)((mlx->player->center_x + LIMIT * sin(mlx->player->player_angle)
	* mlx->player->dir_side) / TILE_SIZE)] == '1' && !x_y.x && !x_y.y)
		mlx->player->pos = *old;
}

int	left_right_condition(t_mlx *mlx, t_point *old)
{
	t_point	x_y;
	t_point	i_j;

	x_y = (t_point){0, 0};
	i_j.y = ((mlx->player->center_y - LIMIT * cos(mlx->player->player_angle) * \
	mlx->player->dir_side) / TILE_SIZE);
	i_j.x = ((old->x + TILE_SIZE / 2) / TILE_SIZE);
	if (mlx->pars->map[(int)i_j.y][(int)i_j.x] == '1' || \
	mlx->pars->map[(int)i_j.y][(int)i_j.x] == '2')
	{
		mlx->player->pos.y = old->y;
		x_y.y = 1;
	}
	if (mlx->pars->map[(int)((old->y + TILE_SIZE / 2) / \
	TILE_SIZE)][(int)((mlx->player->center_x + LIMIT * \
	sin(mlx->player->player_angle) * mlx->player->dir_side) \
	/ TILE_SIZE)] == '1' || mlx->pars->map[(int)((old->y + TILE_SIZE / 2) / \
	TILE_SIZE)][(int)((mlx->player->center_x + LIMIT * \
	sin(mlx->player->player_angle) * mlx->player->dir_side) \
	/ TILE_SIZE)] == '2')
	{
		mlx->player->pos.x = old->x;
		x_y.x = 1;
	}
	return (check_and_slide(mlx, x_y, old), 0);
}

int	up_down(t_mlx *mlx)
{
	t_point	old;
	t_point	x_y;

	x_y = (t_point){0, 0};
	old.x = mlx->player->pos.x;
	old.y = mlx->player->pos.y;
	mlx->player->pos.x += MOVE_SPEED * cos(mlx->player->player_angle)
		* mlx->player->dir_forw;
	mlx->player->pos.y += MOVE_SPEED * sin(mlx->player->player_angle)
		* mlx->player->dir_forw;
	player_center(mlx);
	up_down_condition(mlx, &old);
	return (player_center(mlx), 0);
}

int	left_right(t_mlx *mlx)
{
	t_point	old;

	old.x = mlx->player->pos.x;
	old.y = mlx->player->pos.y;
	mlx->player->pos.x += MOVE_SPEED * sin(mlx->player->player_angle)
		* mlx->player->dir_side;
	mlx->player->pos.y -= MOVE_SPEED * cos(mlx->player->player_angle)
		* mlx->player->dir_side;
	player_center(mlx);
	left_right_condition(mlx, &old);
	player_center(mlx);
	return (0);
}

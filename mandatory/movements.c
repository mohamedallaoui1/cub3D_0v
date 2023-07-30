/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:44:00 by oidboufk          #+#    #+#             */
/*   Updated: 2023/07/30 18:04:03 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	move_condition(t_mlx *mlx, t_point *old)
{
	t_point	x_y;

	x_y = (t_point){0, 0};
	// until the bonus part
	if (mlx->pars->map[(int)(mlx->player->player_center_y / TILE_SIZE)]\
	[(int)((old->x + TILE_SIZE / 2) / TILE_SIZE)] == '1')
	{
		mlx->player->player_y = old->y;
		x_y.y = 1;
	}
	if (mlx->pars->map[(int)((old->y + TILE_SIZE / 2) / TILE_SIZE)]\
	[(int)((mlx->player->player_center_x) / TILE_SIZE)] == '1')
	{
		mlx->player->player_x = old->x;
		x_y.x = 1;
	}
	if (mlx->pars->map[(int)((mlx->player->player_center_y) / TILE_SIZE)]
	[(int)((mlx->player->player_center_x) / TILE_SIZE)] == '1' && !x_y.x && !x_y.y)
	{
		mlx->player->player_x = old->x;
		mlx->player->player_y = old->y;
	}
	return (0);
}

int up_down(t_mlx *mlx)
{
	t_point	old;
	t_point	x_y;

	x_y = (t_point){0, 0};
	old.x = mlx->player->player_x;
	old.y = mlx->player->player_y;
    mlx->player->player_x += MOVE_SPEED * cos(mlx->player->player_angle) * mlx->player->direction_forward;
    mlx->player->player_y += MOVE_SPEED * sin(mlx->player->player_angle) * mlx->player->direction_forward;
	get_player_center(mlx);
	move_condition(mlx, &old);
    return (get_player_center(mlx), 0);
}

int left_right(t_mlx *mlx)
{
	t_point	old;

	old.x = mlx->player->player_x;
	old.y = mlx->player->player_y;
    mlx->player->player_x += MOVE_SPEED * sin(mlx->player->player_angle) * mlx->player->direction_side;
    mlx->player->player_y -= MOVE_SPEED * cos(mlx->player->player_angle) * mlx->player->direction_side;
    get_player_center(mlx);
	move_condition(mlx, &old);
	get_player_center(mlx);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:07:34 by mallaoui          #+#    #+#             */
/*   Updated: 2023/08/05 23:09:04 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	up_down_condition_norm(t_mlx *mlx, t_point *old, t_point x_y)
{
	if (mlx->pars->map[(int)((old->y + TILE_SIZE / 2) / TILE_SIZE)] \
	[(int)((mlx->player->center_x + LIMIT \
	* cos(mlx->player->player_angle) \
	* mlx->player->dir_forw) / TILE_SIZE)] == '1' || \
	mlx->pars->map[(int)((old->y + TILE_SIZE / 2) / TILE_SIZE)] \
	[(int)((mlx->player->center_x + LIMIT \
	* cos(mlx->player->player_angle) \
	* mlx->player->dir_forw) / TILE_SIZE)] == '2')
	{
		mlx->player->pos.x = old->x;
		x_y.x = 1;
	}
	if ((mlx->pars->map[(int)((mlx->player->center_y + LIMIT \
	* sin(mlx->player->player_angle) * mlx->player->dir_forw) / TILE_SIZE)] \
	[(int)((mlx->player->center_x + LIMIT * cos(mlx->player->player_angle) \
	* mlx->player->dir_forw) / TILE_SIZE)] == '1' || \
	mlx->pars->map[(int)((mlx->player->center_y + LIMIT \
	* sin(mlx->player->player_angle) * mlx->player->dir_forw) / TILE_SIZE)] \
	[(int)((mlx->player->center_x + LIMIT * cos(mlx->player->player_angle) \
	* mlx->player->dir_forw) / TILE_SIZE)] == '2') && !x_y.x && !x_y.y)
		mlx->player->pos = *old;
}

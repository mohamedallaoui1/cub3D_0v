/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialzev2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:00:16 by mallaoui          #+#    #+#             */
/*   Updated: 2023/08/05 23:01:35 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	keys_init(t_mlx *mlx)
{
	mlx->player->keys.key_a = 0;
	mlx->player->keys.key_s = 0;
	mlx->player->keys.key_d = 0;
	mlx->player->keys.key_w = 0;
	mlx->player->keys.key_space = 0;
	mlx->player->dir_forw = 0;
	mlx->player->dir_side = 0;
	mlx->player->keys.key_left = 0;
	mlx->player->keys.key_right = 0;
	mlx->mouse.x = 0;
	mlx->mouse.y = 0;
	mlx->mouse.which_side = 0;
}

int	count_doors(t_mlx *mlx)
{
	int	x;
	int	y;
	int	count;

	y = -1;
	count = 0;
	while (mlx->pars->map[++y])
	{
		x = -1;
		while (mlx->pars->map[y][++x])
			if (mlx->pars->map[y][x] == '2')
				count++;
	}
	return (count);
}

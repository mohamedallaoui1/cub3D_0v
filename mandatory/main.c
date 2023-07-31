/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:15:18 by mallaoui          #+#    #+#             */
/*   Updated: 2023/07/31 12:01:06 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

double	dist_(t_point p1, t_point p2)
{
	return (sqrt((p2.x - p1.x) * (p2.x - p1.x)
			+ (p2.y - p1.y) * (p2.y - p1.y)));
}

void	set_player_dir(t_mlx *mlx)
{
	int		i;
	int		j;

	i = 0;
	while (i < mlx->vars->map_h)
	{
		j = 0;
		while (j < mlx->vars->map_w)
		{
			if (mlx->pars->map[i][j] == 'N' || mlx->pars->map[i][j] == 'S'
				|| mlx->pars->map[i][j] == 'W' || mlx->pars->map[i][j] == 'E')
			{
				mlx->player->player_dir = mlx->pars->map[i][j];
				break ;
			}
			j++;
		}
		i++;
	}
}

void	player_angle(t_mlx *mlx)
{
	if (mlx->player->player_dir == 'N')
		mlx->player->player_angle = 3 * M_PI / 2;
	else if (mlx->player->player_dir == 'S')
		mlx->player->player_angle = M_PI / 2;
	else if (mlx->player->player_dir == 'E')
		mlx->player->player_angle = 0;
	else if (mlx->player->player_dir == 'W')
		mlx->player->player_angle = M_PI;
}

int	main(int ac, char **av)
{
	t_mlx		*mlx;
	double		*arr;

	arr = NULL;
	mlx = init(arr, ac, av);
	mlx->player->rays = malloc(WIDTH * sizeof(t_rays));
	mlx_hook(mlx->win, 17, 0L, close_window, mlx);
	mlx_hook(mlx->win, 2, 1L << 2, control_key, mlx);
	mlx_hook(mlx->win, 3, 1L << 2, key_released, mlx);
	mlx_loop_hook(mlx->mlx, magic, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}

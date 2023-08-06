/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:15:18 by mallaoui          #+#    #+#             */
/*   Updated: 2023/08/05 23:01:55 by mallaoui         ###   ########.fr       */
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

int	mouse_control(int x, int y, t_mlx *mlx)
{
	mlx->mouse.x = x;
	if (x < WIDTH / 2 - SAFE_AREA)
		mlx->mouse.which_side = -1;
	else
		mlx->mouse.which_side = 1;
	if ((x < 0 || x > WIDTH || (x >= WIDTH / 2 - SAFE_AREA \
	&& x <= WIDTH / 2 + SAFE_AREA) || y < 0 || y > HEIGHT))
		mlx->mouse.which_side = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx		*mlx;
	double		*arr;

	arr = NULL;
	mlx = init(arr, ac, av);
	mlx->player->rays = malloc(WIDTH * sizeof(t_rays));
	mlx_hook(mlx->win, 17, 0L, close_window, mlx);
	mlx_hook(mlx->win, 6, 0L, mouse_control, mlx);
	mlx_hook(mlx->win, 2, 1L << 2, control_key, mlx);
	mlx_hook(mlx->win, 3, 1L << 2, key_released, mlx);
	mlx_hook(mlx->win, 6, 1L << 2, mouse_control, mlx);
	mlx_loop_hook(mlx->mlx, magic, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:27:16 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/02 15:30:45 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

double	*player_pos(char **map)
{
	int		i;
	int		j;
	double	*arr;

	i = 0;
	arr = malloc (sizeof(double) * 2);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
			{
				arr[0] = (double)i;
				arr[1] = (double)j;
				return (arr);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

void	player_center(t_mlx *mlx)
{
	mlx->player->center_x = mlx->player->pos.x + TILE_SIZE / 2;
	mlx->player->center_y = mlx->player->pos.y + TILE_SIZE / 2;
}

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

unsigned int	reverse_color(unsigned int color)
{
	unsigned char red;
	unsigned char blue;
	unsigned char green;

	red = (unsigned char)(255 - (color >> 16));
	green = (unsigned char)(255 - (color >> 8));
	blue = (unsigned char)(255 - color);
	return (red << 16 | green << 8 | blue);
}
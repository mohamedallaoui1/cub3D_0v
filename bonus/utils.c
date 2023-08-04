/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:27:16 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/04 10:18:14 by oidboufk         ###   ########.fr       */
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

void draw_line(t_mlx *mlx, t_point point1, t_point point2)
{
	double	x;
	double	y;
	double	step;
	double	i;
	double	j;

	x = point1.x;
	y = point1.y;
	step = 1;
	if (fabs(point2.x - point1.x) >= fabs(point2.y - point1.y))
		step = fabs(point2.x - point1.x);
	else
		step = fabs(point2.y - point1.y);
	i = (point2.x - point1.x) / step;
	j = (point2.y - point1.y) / step;
	while (step > 0)
	{
		my_mlx_pixel_put(mlx, x, y, reverse_color(get_pixel_color(mlx->img.img, x, y)));
		x += i;
		y += j;
		step--;
	}
}
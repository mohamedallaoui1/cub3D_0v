/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:39:28 by oidboufk          #+#    #+#             */
/*   Updated: 2023/07/31 19:56:59 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	int_color(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

int	get_pixel_color(t_data *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img.addr + (y * mlx->img.line_length
			+ x * (mlx->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	shading(int color, double dist)
{
	unsigned int	red;
	unsigned int	alpha;
	unsigned int	green;
	unsigned int	blue;

	red = (color >> 16) & 0xFF;
	alpha = (color >> 24) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	if (dist > 1)
		dist = 1;
	alpha = (unsigned int)(255 * dist);
	return (alpha << 24 | red << 16 | green << 8 | blue);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:39:28 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/04 16:18:59 by oidboufk         ###   ########.fr       */
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

unsigned int	shading(int color, double percent)
{
	unsigned char	red;
	unsigned char	alpha;
	unsigned char	green;
	unsigned char	blue;

	red = (color >> 16);
	alpha = (color >> 24);
	green = (color >> 8);
	blue = color;
	if (percent > 1)
		percent = 1;
	alpha = (unsigned int)(255 * percent);
	return (alpha << 24 | red << 16 | green << 8 | blue);
}

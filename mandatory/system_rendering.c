/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:47:59 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/08 21:58:56 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	magic(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	handle_events(mlx);
	castrays(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}

t_data	*get_texture(t_mlx *mlx, int id)
{
	if (mlx->player->rays[id].is_hor)
	{
		if (mlx->player->rays[id].facing_up)
			return (&mlx->textures[1]);
		else
			return (&mlx->textures[0]);
	}
	else
	{
		if (mlx->player->rays[id].facing_left)
			return (&mlx->textures[2]);
		else
			return (&mlx->textures[3]);
	}
}

void	project_wall(t_mlx *mlx, int id)
{
	double	val;
	int		p_wall_h;
	int		i;
	double	count;

	i = -1;
	val = init_vars(mlx, id, &p_wall_h, &count);
	while (++i < HEIGHT)
	{
		if (i < HEIGHT / 2 - p_wall_h / 2)
			my_mlx_pixel_put(mlx, id, i, shading(
					int_color(mlx->pars->c_rgb),
					(double)i / (double)(HEIGHT / 2)));
		else if (i >= HEIGHT / 2 - p_wall_h / 2
			&& i < HEIGHT / 2 + p_wall_h / 2)
			my_mlx_pixel_put(mlx, id, i,
				shading(get_pixel_color(
						get_texture(mlx, id), val, (count++ / p_wall_h)
						* get_texture(mlx, id)->img_height),
					mlx->player->rays[id].dist / SHADE_RANGE));
		else
			my_mlx_pixel_put(mlx, id, i, shading(
					int_color(mlx->pars->f_rgb),
					(double)(HEIGHT / 2) / (double)i));
	}
}

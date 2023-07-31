/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:55:20 by oidboufk          #+#    #+#             */
/*   Updated: 2023/07/31 12:59:18 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	keys_init(t_mlx *mlx)
{
	mlx->player->keys.key_a = 0;
	mlx->player->keys.key_s = 0;
	mlx->player->keys.key_d = 0;
	mlx->player->keys.key_w = 0;
	mlx->player->dir_forw = 0;
	mlx->player->dir_side = 0;
	mlx->player->keys.key_left = 0;
	mlx->player->keys.key_right = 0;
}

t_mlx	*init(double *arr, int ac, char *av[])
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->pars = malloc(sizeof(t_pars));
	mlx->vars = malloc(sizeof(t_vars));
	mlx->player = malloc(sizeof(t_player));
	(parsing(mlx->pars, ac, av), map_w_h(mlx->vars, mlx->pars));
	arr = player_pos(mlx->pars->map);
	mlx->player->pos.y = arr[0] * TILE_SIZE;
	mlx->player->pos.x = arr[1] * TILE_SIZE;
	(free(arr), set_player_dir(mlx), player_angle(mlx));
	mlx->height = mlx->vars->map_h * TILE_SIZE;
	mlx->width = mlx->vars->map_w * TILE_SIZE;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	texture_init(mlx);
	keys_init(mlx);
	return (mlx);
}

void	texture_init(t_mlx *mlx)
{
	int		i;
	char	**strs;

	i = -1;
	strs = (char *[4]){mlx->pars->no, mlx->pars->so,
		mlx->pars->ea, mlx->pars->we};
	while (++i < 4)
	{
		mlx->textures[i].img = mlx_xpm_file_to_image(mlx->mlx,
				strs[i], &mlx->textures[i].img_width,
				&mlx->textures[i].img_height);
		if (!mlx->textures[i].img)
			(write(1, "Error\nImage Does not exist!", 28), exit(i));
		mlx->textures[i].addr = mlx_get_data_addr(mlx->textures[i].img,
				&mlx->textures[i].bits_per_pixel,
				&mlx->textures[i].line_length, &mlx->textures[i].endian);
		if (!mlx->textures[i].addr)
			(write(1, "Error\nImage Problem!", 28), exit(i));
	}
}

void	init_ray(t_rays *ray, double rayAngle)
{
	ray->ray_angle = rayAngle;
	ray->found_horz = 0;
	ray->found_vert = 0;
	ray->facing_down = (rayAngle > 0 && rayAngle < M_PI);
	ray->facing_up = !ray->facing_down;
	ray->facing_left = (rayAngle > M_PI / 2 && rayAngle < 1.5 * M_PI);
	ray->facing_right = !ray->facing_left;
}

double	init_vars(t_mlx *mlx, int id, int *p_wall_h, double *count)
{
	double	val;

	if (mlx->player->rays[id].is_hor)
		val = get_wall_hit(mlx, id).x / TILE_SIZE;
	else
		val = get_wall_hit(mlx, id).y / TILE_SIZE;
	val = (val - (int)val) * get_texture(mlx, id)->img_width;
	*count = 0;
	*p_wall_h = round((TILE_SIZE / mlx->player->rays[id].dist) * PROJ_DIST);
	if (*p_wall_h > HEIGHT)
		*count = (*p_wall_h - HEIGHT) / 2;
	return (val);
}

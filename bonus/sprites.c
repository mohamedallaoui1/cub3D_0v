/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:10:06 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/08 22:07:56 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	init_sprites(t_mlx *mlx)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < FRAME_NUM)
	{
		tmp = ft_itoa(i);
		mlx->sprites[i].sprite_path = ft_strjoin("./bonus/sprites/", tmp);
		tmp = (free(tmp), ft_strjoin(mlx->sprites[i].sprite_path, ".xpm"));
		mlx->sprites[i].sprite_path = (free(mlx->sprites[i].sprite_path), tmp);
		printf("frame(%s) is Loading ...\n", mlx->sprites[i].sprite_path);
		mlx->sprites[i].sprite.img = \
		mlx_xpm_file_to_image(mlx->mlx, mlx->sprites[i].sprite_path, \
		&mlx->sprites[i].sprite.img_width, &mlx->sprites[i].sprite.img_height);
		if (!mlx->sprites[i].sprite.img)
			(printf("Error\nImage Does not exist!"), exit(i));
		mlx->sprites[i].sprite.addr = \
		mlx_get_data_addr(mlx->sprites[i].sprite.img, \
		&mlx->sprites[i].sprite.bits_per_pixel, \
		&mlx->sprites[i].sprite.line_length, &mlx->sprites[i].sprite.endian);
		if (!mlx->sprites[i].sprite.addr)
			(printf("Error\nImage Does not exist!"), exit(i));
		printf("frame(%s) is Loaded\n", mlx->sprites[i].sprite_path);
	}
}

void	*animate(void *mlx)
{
	t_mlx	*ml;
	int		i;

	ml = (t_mlx *)mlx;
	while (1)
	{
		pthread_mutex_lock(ml->mutex);
		i = ml->animation_frame;
		pthread_mutex_unlock(ml->mutex);
		while (i < FRAME_NUM && ml->start)
		{
			pthread_mutex_lock(ml->mutex);
			ml->animation_frame++;
			if (ml->animation_frame == FRAME_NUM)
			{
				ml->animation_frame = 0;
				ml->start = 0;
			}
			pthread_mutex_unlock(ml->mutex);
			usleep(40000);
		}
	}
}

int	animation_control(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	pthread_mutex_lock(mlx->mutex);
	if (button == 1 && mlx->start == 0)
		mlx->start = 1;
	pthread_mutex_unlock(mlx->mutex);
	return (0);
}

void	draw_gun(t_mlx *mlx)
{
	int	id;
	int	w;
	int	h;

	pthread_mutex_lock(mlx->mutex);
	id = mlx->animation_frame;
	w = WIDTH - mlx->sprites[id % FRAME_NUM].sprite.img_width;
	h = HEIGHT - mlx->sprites[id % FRAME_NUM].sprite.img_height;
	if (w <= 0 || h <= 0)
		(printf("the WIDTH or HEIGHT are smaller\
		 than possible recommended (1000/700)\n"), exit(2));
	mlx_put_image_to_window(mlx->mlx, \
	mlx->win, mlx->sprites[id % FRAME_NUM].sprite.img,
		WIDTH - mlx->sprites[id % FRAME_NUM].sprite.img_width, h);
	pthread_mutex_unlock(mlx->mutex);
}

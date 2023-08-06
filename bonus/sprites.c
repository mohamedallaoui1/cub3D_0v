/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:10:06 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/06 13:49:29 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void    init_sprites(t_mlx *mlx)
{
    int		i;
	char	*tmp;

    i = -1;
    while (++i < FRAME_NUM)
    {
		tmp = ft_itoa(i);
		mlx->sprites[i].sprite_path = ft_strjoin("./sprites/", tmp);
		free(tmp);
		tmp = ft_strjoin(mlx->sprites[i].sprite_path, ".xpm");
		free(mlx->sprites[i].sprite_path);
		mlx->sprites[i].sprite_path = tmp;
		printf("frame(%s) is Loading ...\n", mlx->sprites[i].sprite_path);
        mlx->sprites[i].sprite.img = mlx_xpm_file_to_image(mlx->mlx, mlx->sprites[i].sprite_path, &mlx->sprites[i].sprite.img_width, &mlx->sprites[i].sprite.img_height);
        if (!mlx->sprites[i].sprite.img)
            (printf("Error\nImage Does not exist!"), exit(i));
		mlx->sprites[i].sprite.addr = mlx_get_data_addr(mlx->sprites[i].sprite.img, &mlx->sprites[i].sprite.bits_per_pixel,
			&mlx->sprites[i].sprite.line_length, &mlx->sprites[i].sprite.endian);
		if (!mlx->sprites[i].sprite.addr)
            (printf("Error\nImage Does not exist!"), exit(i));
		printf("frame(%s) is Loaded\n", mlx->sprites[i].sprite_path);
    }
}


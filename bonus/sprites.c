/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:10:06 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/04 21:58:16 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void    init_sprites(t_mlx *mlx)
{
    int i;

    i = 0;
    while (i < 1)
    {
        mlx->sprite_list.img.img = mlx_xpm_file_to_image(mlx->mlx, mlx->sprite_list.data.sprite_path, &mlx->width, &mlx->height);
        if (!mlx->sprite_list.img.img)
            (printf("Error\nImage Does not exist!"), exit(i));
		mlx->sprite_list.img.addr = mlx_get_data_addr(mlx->sprite_list.img.img, &mlx->sprite_list.img.bits_per_pixel,
			&mlx->sprite_list.img.line_length, &mlx->sprite_list.img.endian);
		if (!mlx->sprite_list.img.addr)
            (printf("Error\nImage Does not exist!"), exit(i));
    }
}

void	add_listfront(t_mlx *mlx, t_sprite *new)
{
	t_sprite	*tmp;

	if (!mlx)
	{
		mlx = new;
		return ;
	}
	tmp = mlx;
	mlx = new;
	mlx->sprite_list.next = tmp;
}
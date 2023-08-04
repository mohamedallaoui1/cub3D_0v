/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:22:23 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/04 16:50:51 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	handle_events(t_mlx *mlx)
{
	double	rotate;
	double	percent;
	double	m_dist;

	m_dist = abs(mlx->mouse.x  - (WIDTH/2 + SAFE_AREA * mlx->mouse.which_side));
	percent = m_dist / (WIDTH / 2);
	if (mlx->player->keys.key_left || mlx->player->keys.key_right || percent > 1)
		percent = 1;
	rotate = ROT_SPEED;
	if (mlx->player->keys.key_w || mlx->player->keys.key_s)
		up_down(mlx);
	if (mlx->player->keys.key_a || mlx->player->keys.key_d)
		left_right(mlx);
	if (mlx->player->keys.key_left ||
		(mlx->mouse.which_side == -1 && !mlx->player->keys.key_right))
		mlx->player->player_angle
			= normalize_angle(mlx->player->player_angle  - rotate * percent);
	if (mlx->player->keys.key_space)
		;
		// check the line of the player if its in the door cell and change it to 0 (bye transport gha ymchi)
	else if (mlx->player->keys.key_right ||  mlx->mouse.which_side)
		mlx->player->player_angle
			= normalize_angle(mlx->player->player_angle + rotate * percent);
}

void	wsa(t_mlx *mlx, int keycode)
{
	if (keycode == KEY_W)
	{
		mlx->player->keys.key_w = 1;
		if (!mlx->player->dir_forw)
			mlx->player->dir_forw = 1;
	}
	if (keycode == KEY_S)
	{
		mlx->player->keys.key_s = 1;
		if (!mlx->player->dir_forw)
			mlx->player->dir_forw = -1;
	}
	if (keycode == KEY_A)
	{
		mlx->player->keys.key_a = 1;
		if (!mlx->player->dir_side)
			mlx->player->dir_side = LEFT;
	}
}

int	control_key(int keycode, t_mlx *mlx)
{
	printf ("%d\n", keycode);
	wsa(mlx, keycode);
	if (keycode == KEY_D)
	{
		mlx->player->keys.key_d = 1;
		if (!mlx->player->dir_side)
			mlx->player->dir_side = RIGHT;
	}
	if (keycode == KEY_LEFT)
		mlx->player->keys.key_left = 1;
	if (keycode == KEY_RIGHT)
		mlx->player->keys.key_right = 1;
	if (keycode == SPACE_KEY)
		mlx->player->keys.key_space = 1;
	(keycode == 53) && (exit(0), 0);
	return (0);
}

int	key_released(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
	{
		mlx->player->keys.key_w = 0;
		mlx->player->dir_forw = 0;
	}
	if (keycode == KEY_S)
	{
		mlx->player->keys.key_s = 0;
		mlx->player->dir_forw = 0;
	}
	if (keycode == KEY_A)
	{
		mlx->player->keys.key_a = 0;
		mlx->player->dir_side = 0;
	}
	if (keycode == KEY_D)
	{
		mlx->player->keys.key_d = 0;
		mlx->player->dir_side = 0;
	}
	if (keycode == KEY_LEFT)
		mlx->player->keys.key_left = 0;
	if (keycode == KEY_RIGHT)
		mlx->player->keys.key_right = 0;
	return (0);
}
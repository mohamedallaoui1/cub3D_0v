/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:21:42 by mallaoui          #+#    #+#             */
/*   Updated: 2023/08/08 16:28:48 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	check_player_around(char **map, int i, int j)
{
	if ((i <= 0 || j <= 0) || ((i > 0 && j > 0) && \
	(map[i][j + 1] == '\0' || !map[i + 1] || \
	map[i + 1][j] == '\0' || !map[i - 1] || \
	map[i - 1][j] == '\0')))
		error("Error\nWrong map format\n");
}

void	check_door_around(char **map, int i, int j)
{
	if ((i <= 0 || j <= 0) || ((i > 0 && j > 0) && \
	(map[i][j + 1] == '\0' || !map[i + 1] || \
	map[i + 1][j] == '\0' || !map[i - 1] || \
	map[i - 1][j] == '\0')))
		error("Error\nWrong map format\n");
	if (map[i + 1][j] == '1' && map[i - 1][j] == '1' && \
	(map[i][j + 1] == '0' || \
	map[i][j - 1] == '0'))
		return ;
	if (map[i][j + 1] == '1' && map[i][j - 1] == '1' && \
	(map[i + 1][j] == '0' || \
	map[i - 1][j] == '0'))
		return ;
	error("Error\nWrong map format\n");
}

void	validate_map_norm(char **map, int i, int j)
{
	if (map[i][j] == '0')
		check_around(map, i, j);
	if (map[i][j] == 'N' | map[i][j] == 'W' | \
	map[i][j] == 'S' | map[i][j] == 'E')
		check_player_around(map, i, j);
	if (map[i][j] == '2')
		check_door_around(map, i, j);
}

void	remove_spaces(char **p)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (p[i])
	{
		j = 0;
		if (p[i][0] == ' ')
			while (p[i][j] == ' ')
				j++;
		if (p[i][j] != '1' && p[i][j] != '\0')
		{
			tmp = p[i];
			p[i] = ft_strdup(tmp + j);
			free(tmp);
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:19:00 by mallaoui          #+#    #+#             */
/*   Updated: 2023/08/08 16:27:15 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**get_recalloced_map(char **file, int size, int len)
{
	int		i;
	char	**map;
	int		j;

	i = 0;
	map = malloc(sizeof(char *) * (size + 1));
	while (file[i])
	{
		j = 0;
		map[i] = ft_calloc(len + 1, sizeof(char));
		while (file[i][j])
		{
			map[i][j] = file[i][j];
			j++;
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}

char	**get_map(char **file)
{
	int		i;
	int		size;
	size_t	len;
	char	**tmp;

	i = 0;
	size = 0;
	len = ft_strlen(file[0]);
	while (file[i])
	{
		if (ft_strlen(file[i]) > len)
			len = ft_strlen(file[i]);
		i++;
		size++;
	}
	i = 0;
	tmp = get_recalloced_map(file, size, len);
	return (tmp);
}

void	check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' && \
			map[i][j] != 'N' && map[i][j] != 'S' && \
			map[i][j] != 'E' && map[i][j] != 'W' && \
			map[i][j] != '2')
				error("Error\nWrong map format\n");
			j++;
		}
		i++;
	}
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	check_around(char **map, int i, int j)
{
	if ((map[i][j] == '0' || is_player(map[i][j])) && \
	((i <= 0 || j <= 0) || ((i > 0 && j > 0) && \
	((map[i][j + 1] == ' ' || map[i][j + 1] == '\0') || \
	(!map[i + 1] || map[i + 1][j] == ' ' || map[i + 1][j] == '\0') || \
	(!map[i - 1] || map[i - 1][j] == ' ' || map[i - 1][j] == '\0')))))
		error("Error\nWrong map format\n");
}

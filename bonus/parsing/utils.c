/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:32:53 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/05 23:21:20 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

int	check_char(char **file, int i, int j)
{
	if (file[i][j] == 'N' && file[i][j + 1] == 'O')
		return (1);
	if (file[i][j] == 'S' && file[i][j + 1] == 'O')
		return (1);
	if (file[i][j] == 'W' && file[i][j + 1] == 'E')
		return (1);
	if (file[i][j] == 'E' && file[i][j + 1] == 'A')
		return (1);
	if (file[i][j] == 'F' && file[i][j + 1] == ' ')
		return (1);
	if (file[i][j] == 'C' && file[i][j + 1] == ' ')
		return (1);
	if (file[i][j] == '1' && (file[i][j + 1] == '1' || file[i][j + 1] == '0' ||
	file[i][j + 1] == ' ' || file[i][j + 1] == '\0' \
	|| file[i][j + 1] == 'N' || \
	file[i][j + 1] == 'S' || file[i][j + 1] == 'W' \
	|| file[i][j + 1] == 'E' || file[i][j + 1] == '2' || \
	file[i][j + 1] == 'c'))
		return (1);
	return (0);
}

void	map_w_h(t_vars *vars, t_pars *pars)
{
	int		i;
	size_t	len;

	i = 0;
	while (pars->map[i])
		i++;
	vars->map_h = i;
	i = 0;
	len = ft_strlen(pars->map[0]);
	while (pars->map[i])
	{
		if (len < ft_strlen(pars->map[i]))
			len = ft_strlen(pars->map[i]);
		i++;
	}
	vars->map_w = len;
}

void	check_map_order(char **file)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (file[++i])
	{
		if (ft_strncmp(file[i], "NO", 2) == 0)
			count++;
		if (ft_strncmp(file[i], "SO", 2) == 0)
			count++;
		if (ft_strncmp(file[i], "WE", 2) == 0)
			count++;
		if (ft_strncmp(file[i], "EA", 2) == 0)
			count++;
		if (ft_strncmp(file[i], "F", 1) == 0)
			count++;
		if (ft_strncmp(file[i], "C", 1) == 0)
			count++;
		if (ft_strncmp(file[i], "1", 1) == 0)
			break ;
	}
	if (ft_strncmp(file[i], "1", 1) == 0 && count != 6)
		error("Error\nWrong map format\n");
}

void	map_pars(t_pars *pars, char **file)
{
	int		i;
	char	**map;

	i = 0;
	map = NULL;
	while (file[i])
	{
		if (ft_strncmp(file[i], "1", 1) == 0)
		{
			map = get_map(file + i);
			break ;
		}
		i++;
	}
	check_map(map);
	check_double(map);
	validate_map(map);
	pars->map = map;
}

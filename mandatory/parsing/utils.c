/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:32:53 by oidboufk          #+#    #+#             */
/*   Updated: 2023/07/31 11:37:40 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void    error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

int check_char(char **file, int i, int j)
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
    if (file[i][j] == '1' && (file[i][j + 1] == '1' || file[i][j + 1] == '0' ||\
    file[i][j + 1] == ' ' || file[i][j + 1] == '\0' || file[i][j + 1] == 'N' ||\
    file[i][j + 1] == 'S' || file[i][j + 1] == 'W' || file[i][j + 1] == 'E'))
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
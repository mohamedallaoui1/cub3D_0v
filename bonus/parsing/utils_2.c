/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:29:49 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/08 16:30:07 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_map(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		while (file[i] && file[i] == ' ')
			i++;
		if (file[i] && file[i] == '1')
			return (1);
		else
			return (0);
		i++;
	}
	return (0);
}

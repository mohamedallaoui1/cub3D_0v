/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:29:24 by oidboufk          #+#    #+#             */
/*   Updated: 2023/08/08 16:33:57 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	count_lines(char *name)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(name, O_RDONLY);
	if (fd < 0)
		error("Error\nCan't open file\n");
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	return (i);
}

char	**get_content(char *name)
{
	int		fd;
	char	*line;
	char	**file;
	int		size;
	int		i;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		error("Error\nCan't open file\n");
	size = count_lines(name);
	file = malloc(sizeof(char *) * (size + 1));
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		file[i] = ft_strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	file[i] = NULL;
	return (file);
}

void	check_file_general_errors(char **file)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			while (file[i][j] == ' ')
				j++;
			if (check_char(file, i, j))
				break ;
			else
				error("Error\nWrong file\n");
			j++;
		}
		i++;
	}
}

void	remove_newline(char **file)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] && file[i][j] != '\n')
			j++;
		tmp = malloc(sizeof(char) * (j + 1));
		j = 0;
		while (file[i][j] && file[i][j] != '\n')
		{
			tmp[j] = file[i][j];
			j++;
		}
		tmp[j] = '\0';
		free(file[i]);
		file[i] = tmp;
		i++;
	}
}

void	parsing(t_pars *pars, int ac, char **av)
{
	char	**file;
	int		i;

	i = 0;
	if (ac < 2)
		error("Error\nNo input file\n");
	if (ac > 2)
		error("Error\nToo many arguments\n");
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		error("Error\nWrong file extension\n");
	file = get_content(av[1]);
	remove_newline(file);
	remove_spaces(file);
	check_file_general_errors(file);
	texture_parsing(pars, file);
	color_pars(pars, file);
	map_pars(pars, file);
	while (file && file[i])
		free(file[i++]);
	if (file)
		free(file);
}

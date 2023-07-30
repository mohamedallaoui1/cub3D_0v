/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_pars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:28:15 by mallaoui          #+#    #+#             */
/*   Updated: 2023/07/09 17:28:17 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char    *get_path(char *line, char c)
{
    int     i;
    int     count;
    char    *tmp;

    i = 0;
    count = 0;
    while (line[i])
        if (line[i++] == c)
            count++;
    if (count > 1)
        error("Error\nWrong texture format\n");
    i = 0;
    while (line[i] && (line[i] == c || line[i] == ' '))
    {
        if (line[i] == c)
            i += 2;
        else
            i++;
    }
    tmp = ft_strdup(ft_substr(line, i, ft_strlen(line + i)));
    if (ft_strchr(tmp, '.') == NULL || ft_strchr(tmp, '/') == NULL || ft_strchr(tmp, ' '))
        error("Error\nWrong texture path\n");
    return (tmp);
}

void    check_if_exists(char **file)
{
    int     i;
    int     no;
    int     so;
    int     we;
    int     ea;

    i = 0;
    no = 0;
    so = 0;
    we = 0;
    ea = 0;
    while (file[i])
    {
        if (ft_strncmp(file[i], "NO", 2) == 0)
            no++;
        else if (ft_strncmp(file[i], "SO", 2) == 0)
            so++;
        else if (ft_strncmp(file[i], "WE", 2) == 0)
            we++;
        else if (ft_strncmp(file[i], "EA", 2) == 0)
            ea++;
        i++;
    }
    if (no != 1 || so != 1 || we != 1 || ea != 1)
        error("Error\nWrong texture format\n");
}

void    texture_parsing(t_pars *pars, char **file)
{
    int     i;

    i = 0;
    check_if_exists(file);
    while (file[i])
    {
        if (ft_strncmp(file[i], "NO", 2) == 0)
            pars->no = ft_strdup(get_path(file[i], 'N'));
        else if (ft_strncmp(file[i], "SO", 2) == 0)
            pars->so = ft_strdup(get_path(file[i], 'S'));
        else if (ft_strncmp(file[i], "WE", 2) == 0)
            pars->we = ft_strdup(get_path(file[i], 'W'));
        else if (ft_strncmp(file[i], "EA", 2) == 0)
            pars->ea = ft_strdup(get_path(file[i], 'E'));
        i++;
    }
    printf("NO: %s\n", pars->no);
    printf("SO: %s\n", pars->so);
    printf("WE: %s\n", pars->we);
    printf("EA: %s\n", pars->ea);
}

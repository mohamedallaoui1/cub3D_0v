/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:19:00 by mallaoui          #+#    #+#             */
/*   Updated: 2023/07/31 11:37:40 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3D.h"

char    **get_recalloced_map(char **file, int size, int len)
{
    int    i;
    char    **map;
    int     j;

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

char    **get_map(char **file)
{
    int     i;
    int     size;
    size_t     len;
    char    **tmp;

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

void    check_map(char **map)
{
    int     i;
    int     j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' &&\
            map[i][j] != 'N' && map[i][j] != 'S' &&\
            map[i][j] != 'E' && map[i][j] != 'W')
                error("Error\nWrong map format\n");
            j++;
        }
        i++;
    }
}

int is_player(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (1);
    return (0);
}

void validate_map(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == ' ')
            {
                if (((i > 0 && j > 0) && map[i][j + 1] &&\
                map[i][j - 1] && map[i + 1] && map[i - 1]) &&\
                ((map[i][j + 1] == '0' || is_player(map[i][j + 1])) ||\
                (map[i][j - 1] == '0' || is_player(map[i][j - 1])) ||\
                (map[i + 1][j] == '0' || is_player(map[i + 1][j])) ||\
                (map[i - 1][j] == '0' || is_player(map[i - 1][j]))))
                    error("Error\nWrong map format\n");
            }
            if (map[i][j] == '0')
            {
                if ((i > 0 && j > 0) && (map[i][j + 1] == ' ' || map[i][j + 1] == '\0') &&\
                (map[i + 1][j] == ' ' || map[i + 1][j] == '\0') &&\
                (map[i][j - 1] == ' ' || map[i][j - 1] == '\0'))
                    error("Error\nWrong map format\n");
            }
            j++;
        }
        i++;
    }
}

void    check_double(char **map)
{
    int     i;
    int     j;
    int     count;

    i = 0;
    count = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
                count++;
            j++;
        }
        i++;
    }
    if (count != 1)
        error("Error\nWrong map format\n");
}

void    check_map_order(char **file)
{
    int     i;
    int     count;

    i = 0;
    count = 0;
    while (file[i])
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
        i++;
    }
    if (ft_strncmp(file[i], "1", 1) == 0 && count != 6)
            error("Error\nWrong map format\n");
    
}

void    map_pars(t_pars *pars, char **file)
{
    int     i;
    char    **map;

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
    i = 0;
    while (pars->map[i])
    {
        printf("%s\n", pars->map[i]);
        i++;
    }
}
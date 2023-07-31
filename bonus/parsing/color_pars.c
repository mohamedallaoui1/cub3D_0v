/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 07:22:03 by mallaoui          #+#    #+#             */
/*   Updated: 2023/07/31 11:37:40 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3D.h"

void    check_rgb(char **rgb)
{
    int     i;
    int     j;

    i = 0;
    while (rgb[i])
    {
        j = 0;
        while (rgb[i][j])
        {
            if (rgb[i][j] < '0' || rgb[i][j] > '9')
                error("Error\nWrong color format\n");
            j++;
        }
        i++;
    }
}

char    *remove_spaces_between_comma(char *str)
{
    int     i;
    int     j;
    char    *tmp;

    i = 0;
    j = 0;
    tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
    while (str[i])
    {
        if (str[i] == ' ' && (str[i + 1] == ',' || str[i - 1] == ','))
            i++;
        tmp[j] = str[i];
        i++;
        j++;
    }
    tmp[j] = '\0';
    free(str);
    return (tmp);
}

int     *get_color(char *line, char c)
{
    char    **rgb;
    int     *color;
    int     i;
    char    *tmp;
    int     count;

    i = 0;
    count = 0;
    while (line[i])
        if (line[i++] == c)
            count++;
    if (count > 1)
        error("Error\nWrong color format\n");
    i = 0;
    while (line[i] && (line[i] == c || line[i] == ' '))
        i++;
    rgb = NULL;
    tmp = NULL;
    tmp = ft_strdup(ft_substr(line, i, ft_strlen(line + i)));
    tmp = remove_spaces_between_comma(tmp);
    count = 0;
    i = 0;
    while (tmp[i])
        if (tmp[i++] == ',')
            count++;
    if (count != 2)
        error("Error\nWrong color format\n");
    rgb = ft_split(tmp, ',');
    free(tmp);
    check_rgb(rgb);
    if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL)
        error("Error\nWrong color format\n");
    color = malloc(sizeof(int) * 3);
    color[0] = ft_atoi(rgb[0]);
    color[1] = ft_atoi(rgb[1]);
    color[2] = ft_atoi(rgb[2]);
    if (color[0] < 0 || color[0] > 255 || color[1] < 0 ||\
    color[1] > 255 || color[2] < 0 || color[2] > 255)
        error("Error\nWrong color format\n");
    return (color);
}

void    color_pars(t_pars *pars, char **file)
{
    int     i;
    int     f;
    int     c;

    i = 0;
    f = 0;
    c = 0;
    while (file[i])
    {
        if (ft_strncmp(file[i], "F", 1) == 0)
            f++;
        else if (ft_strncmp(file[i], "C", 1) == 0)
            c++;
        i++;
    }
    if (f != 1 || c != 1)
        error("Error\nWrong color format\n");
    i = 0;
    while (file[i])
    {
        if (ft_strncmp(file[i], "F", 1) == 0)
            pars->f_rgb = get_color(file[i], 'F');
        else if (ft_strncmp(file[i], "C", 1) == 0)
            pars->c_rgb = get_color(file[i], 'C');
        i++;
    }
    printf("F: %d,%d,%d\n", pars->f_rgb[0], pars->f_rgb[1], pars->f_rgb[2]);
    printf("C: %d,%d,%d\n", pars->c_rgb[0], pars->c_rgb[1], pars->c_rgb[2]);
}

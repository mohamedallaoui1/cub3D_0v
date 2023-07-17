/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:15:18 by mallaoui          #+#    #+#             */
/*   Updated: 2023/07/07 17:15:18 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void    error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

int     count_lines(char *name)
{
	int     i;
	int     fd;
	char    *line;

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

char    **get_content(char *name)
{
	int     fd;
	char    *line;
	char    **file;
	int     size;
	int     i;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		error("Error\nCan't open file\n");
	size = count_lines(name);
	file = malloc(sizeof(char *) * (size + 1));
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		file[i] = ft_strdup(line); // new line is included in linne variable :>
		free(line);
		i++;
		line = get_next_line(fd);
	}
	file[i] = NULL;
	return (file);
}


void    check_file_general_errors(char **file)
{
	int     i;
	int     j;

	i = 0;
	j = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			while (file[i][j] == ' ')
				j++;
			if (file[i][j] == 'N' && file[i][j + 1] == 'O')
				break;
			if (file[i][j] == 'S' && file[i][j + 1] == 'O')
				break;
			if (file[i][j] == 'W' && file[i][j + 1] == 'E')
				break;
			if (file[i][j] == 'E' && file[i][j + 1] == 'A')
				break;
			if (file[i][j] == 'F' && file[i][j + 1] == ' ')
				break;
			if (file[i][j] == 'C' && file[i][j + 1] == ' ')
				break;
			if (file[i][j] == '1' && (file[i][j + 1] == '1' || file[i][j + 1] == '0' ||\
			file[i][j + 1] == ' ' || file[i][j + 1] == '\0' || file[i][j + 1] == 'N' ||\
			file[i][j + 1] == 'S' || file[i][j + 1] == 'W' || file[i][j + 1] == 'E'))
				break;
			else
				error("Error\nWrong file\n");
			j++;
		}
		i++;
	}
}

void    remove_newline(char **file)
{
	int     i;
	int     j;
	char    *tmp;

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

void    parsing(t_pars *pars, int ac, char **av)
{
	char    **file;

	// check input file:
	if (ac < 2)
		error("Error\nNo input file\n");
	if (ac > 2)
		error("Error\nToo many arguments\n");
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		error("Error\nWrong file extension\n");
	// check file:
	file = get_content(av[1]);
	remove_newline(file);
	check_file_general_errors(file);
	texture_parsing(pars, file);
	color_pars(pars, file);
	map_pars(pars, file);
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_mlx *mlx, int x, int y, int color)
{
	int		i;
	int		j;
	int		square_size;

	i = 0;
	square_size = 64;
	while (i < square_size - 1)
	{
		j = 0;
		while (j < square_size - 1)
		{
			my_mlx_pixel_put(&mlx->img, (x * square_size) + i + 1, (y * square_size) + j + 1, color);
			j++;
		}
		i++;
	}
}

void	get_map_w_h(t_vars *vars, t_pars *pars)
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

double		*get_player_position(char **map)
{
	int	i;
	int	j;
	double	*arr;

	i = 0;
	arr = malloc (sizeof(double) * 2);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				arr[0] = (double)i;
				arr[1] = (double)j;
				return (arr);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

void	get_player_center(t_mlx *mlx)
{
	mlx->player->player_center_x = (mlx->player->player_x * 64) + 32 + mlx->player->move_player_x;
	mlx->player->player_center_y = (mlx->player->player_y * 64) + 32 + mlx->player->move_player_y;
}

void draw_line(t_mlx *mlx, int x1, int y1, int x2, int y2, int color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = (float)dx / (float)steps;
    float yIncrement = (float)dy / (float)steps;
    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++)
    {
        my_mlx_pixel_put(&mlx->img, (int)x, (int)y, color);
        x += xIncrement;
        y += yIncrement;
    }
}


void	draw_player(t_mlx *mlx, int color)
{
	int			player_square_size;
	int			i;
	int			j;

	player_square_size = 8;
	mlx->player->offset = (64 - player_square_size) / 2;
	i = 0;
	while (i < player_square_size)
	{
		j = 0;
		while (j < player_square_size)
		{
			my_mlx_pixel_put(&mlx->img, (mlx->player->player_x * 64) + i + mlx->player->offset + mlx->player->move_player_x, \
			(mlx->player->player_y * 64) + j + mlx->player->offset + mlx->player->move_player_y, color);
			j++;
		}
		i++;		
	}
	int line_length = 30; // Adjust the line length as needed
    int line_end_x = (mlx->player->player_x * 64) + 32 + line_length * cos(mlx->player->player_angle) + mlx->player->move_player_x;
    int line_end_y = (mlx->player->player_y * 64) + 32 + line_length * sin(mlx->player->player_angle) + mlx->player->move_player_y;
    draw_line(mlx, (mlx->player->player_x * 64) + 32 + mlx->player->move_player_x, (mlx->player->player_y * 64) + 32 + mlx->player->move_player_y, line_end_x, line_end_y, 0x00FF00);
}

void	draw_black_screen(t_mlx *mlx)
{
	int		x;
	int		y;

	y = 0;
	while (y < mlx->vars->map_h * 64)
	{
		x = 0;
		while (x < mlx->vars->map_w * 64)
		{
			my_mlx_pixel_put(&mlx->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

int	 magic(t_mlx *mlx)
{
	int		x;
	int		y;
	int		color;
	t_vars	*vars;

	y = 0;
	vars = mlx->vars;
	draw_black_screen(mlx);
	while (y < mlx->vars->map_h)
	{
		x = 0;
		while (x < mlx->vars->map_w)
		{
			if (mlx->pars->map[y][x] == '1')
				color = 0xFF8066;
			else if (mlx->pars->map[y][x] == ' ')
				color = 0x000000;
			else if (mlx->pars->map[y][x] == '0')
				color = 0xFFFFFF;
			else if (mlx->pars->map[y][x] == '\0')
				color = 0x000000;
			else
				color = 0xFFFFFF;
			draw_square(mlx, x, y, color);
			x++;
		}
		y++;
	}
	draw_player(mlx, 7845562);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}

int control_key(int keycode, t_mlx *mlx)
{
    double moveSpeed = 5;
    double rotateSpeed = 0.05;

    if (keycode == KEY_W)
    {
        mlx->player->move_player_x += moveSpeed * cos(mlx->player->player_angle);
        mlx->player->move_player_y += moveSpeed * sin(mlx->player->player_angle);
    }
    else if (keycode == KEY_S)
    {
        mlx->player->move_player_x -= moveSpeed * cos(mlx->player->player_angle);
        mlx->player->move_player_y -= moveSpeed * sin(mlx->player->player_angle);
    }
    else if (keycode == KEY_A)
    {
        mlx->player->move_player_x += moveSpeed * sin(mlx->player->player_angle);
        mlx->player->move_player_y -= moveSpeed * cos(mlx->player->player_angle);
    }
    else if (keycode == KEY_D)
    {
        mlx->player->move_player_x -= moveSpeed * sin(mlx->player->player_angle);
        mlx->player->move_player_y += moveSpeed * cos(mlx->player->player_angle);
    }
    else if (keycode == KEY_LEFT)
    {
        mlx->player->player_angle -= rotateSpeed;
        if (mlx->player->player_angle < 0)
            mlx->player->player_angle += 2 * M_PI;
    }
    else if (keycode == KEY_RIGHT)
    {
        mlx->player->player_angle += rotateSpeed;
        if (mlx->player->player_angle >= 2 * M_PI)
            mlx->player->player_angle -= 2 * M_PI;
    }
    if (keycode == 53)
        exit(0);
    return 0;
}

void	get_player_direction(t_mlx *mlx)
{
	int		i;
	int		j;

	i = 0;
	while (i < mlx->vars->map_h)
	{
		j = 0;
		while (j < mlx->vars->map_w)
		{
			if (mlx->pars->map[i][j] == 'N' || mlx->pars->map[i][j] == 'S' || mlx->pars->map[i][j] == 'W' || mlx->pars->map[i][j] == 'E')
			{
				mlx->player->player_direction = mlx->pars->map[i][j];
				break ;
			}
			j++;
		}
		i++;
	}
}

void	get_player_angle(t_mlx *mlx)
{
    if (mlx->player->player_direction == 'N')
        mlx->player->player_angle = 3 * M_PI / 2;
    else if (mlx->player->player_direction == 'E')
        mlx->player->player_angle = M_PI / 2;
    else if (mlx->player->player_direction == 'S')
        mlx->player->player_angle = 0;
    else if (mlx->player->player_direction == 'W')
        mlx->player->player_angle = M_PI;
}

int main(int ac, char **av)
{
	t_pars  *pars;
	t_mlx   *mlx;
	t_vars	*vars;
	double		*arr;

	pars = malloc (sizeof(t_pars));
	mlx = malloc (sizeof(t_mlx));
	vars = malloc (sizeof(t_vars));
	mlx->player = malloc (sizeof(t_player));
	parsing(pars, ac, av);
	mlx->pars = pars;
	get_map_w_h(vars, mlx->pars);
	mlx->vars = vars;
	arr = get_player_position(mlx->pars->map);
	mlx->player->player_y = arr[0];
	mlx->player->player_x = arr[1];
	free(arr);
	get_player_direction(mlx);
	get_player_angle(mlx);
	mlx->height = mlx->vars->map_h * 64;
	mlx->width = mlx->vars->map_w * 64;
	mlx->player->move_player_x = 0.0;
	mlx->player->move_player_y = 0.0;
/***********************                         ***************************/
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	mlx_hook(mlx->win, 17, 0L, close_window, mlx);
	mlx_hook(mlx->win, 2, 1L << 2, control_key, mlx);
	mlx_loop_hook(mlx->mlx, magic, mlx);
	mlx_loop(mlx->mlx);
}
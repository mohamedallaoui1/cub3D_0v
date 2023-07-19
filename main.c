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

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x > (mlx->vars->map_w * TILE_LEN)|| y <= 0 || y > (mlx->vars->map_h * TILE_LEN))
		return ;
	dst = mlx->img.addr + (y * mlx->img.line_length + x * (mlx->img.bits_per_M_PIxel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_mlx *mlx, int x, int y, int color)
{
	int		i;
	int		j;
	int		square_size;

	i = 0;
	square_size = TILE_LEN;
	while (i < square_size - 1)
	{
		j = 0;
		while (j < square_size - 1)
		{
			my_mlx_pixel_put(mlx, (x * square_size) + i + 1, (y * square_size) + j + 1, color);
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
	mlx->player->player_center_x = mlx->player->player_x + TILE_LEN /2;
	mlx->player->player_center_y = mlx->player->player_y + TILE_LEN /2;
}

void draw_line(t_mlx *mlx, int x1, int y1, int x2, int y2, int index)
{
    int dx;
    int dy;
    int steps;
    float xIncrement;
    float yIncrement;
    float x;
	int	i;
    float y;
    
	dx = x2 - x1;
    dy = y2 - y1;
    if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
    xIncrement = (float)dx / (float)steps;
    yIncrement = (float)dy / (float)steps;
    x = x1;
    y = y1;
	i = -1;
	// steps is the highest value between dx and dy (the number of steps to draw the line)
	// while (++i <= steps)
	while (mlx->pars->map[(int)(y / TILE_LEN)][(int)(x / TILE_LEN)] != '1')
    {
        my_mlx_pixel_put(mlx, (int)x, (int)y, LINE_COLOR);
        x += xIncrement;
        y += yIncrement;
    }
	mlx->player->rays[index].wall_hit_x = x;
	mlx->player->rays[index].wall_hit_y = y;
	mlx->player->rays[index].distance = sqrt(fabs((mlx->player->player_center_x - x))
			* fabs(mlx->player->player_center_x - x) 
			+ fabs(mlx->player->player_center_y - y) * fabs(mlx->player->player_center_y - y)
		);
}

double normalize_angle(double angle)
{
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void CastRays(t_mlx *mlx)
{
	double	rayAngle;
	int		i;
	// double	horizon_x;
	// double	horizon_y;

	rayAngle = mlx->player->player_angle - (FOV_ANGLE / 2);
	// find_horizon(mlx, &horizon_x, &horizon_y);
	// rayAngle = mlx->player->player_angle;
	i = -1;
	// while (++i < 1)
	while (++i < mlx->vars->map_w * TILE_LEN)
	{
		rayAngle = normalize_angle(rayAngle);
		draw_line(mlx, mlx->player->player_center_x, mlx->player->player_center_y,
			mlx->player->player_center_x + LINE_LEN * cos(rayAngle),
			mlx->player->player_center_y + LINE_LEN * sin(rayAngle),
			// mlx->vars->map_w * TILE_LEN * cos(rayAngle),
			// mlx->vars->map_h * TILE_LEN * sin(rayAngle),
			// horizon_x, horizon_y,
			i
		);
		rayAngle += FOV_ANGLE / (mlx->vars->map_w * TILE_LEN);
		mlx->player->rays[i].ray_angle = rayAngle;
			// printf("[%d] rayAngle: %f , distance %f  cords_wallhit(%f, %f)\n", i, mlx->player->rays[i].ray_angle, mlx->player->rays[i].distance
			// 	, mlx->player->rays[i].wall_hit_x, mlx->player->rays[i].wall_hit_y);
		// }
		// else
		// 	rayAngle += FOV_ANGLE / NUM_RAYS;

	}
}

void	draw_player(t_mlx *mlx, int color)
{
	int	player_square_size;
	int	i;
	int	j;

	player_square_size = 8;
	mlx->player->offset = (TILE_LEN - player_square_size) / 2;
	get_player_center(mlx);
	CastRays(mlx);
	i = 0;
	while (i < player_square_size)
	{
		j = 0;
		while (j < player_square_size)
		{
			my_mlx_pixel_put(mlx, mlx->player->player_x + i + mlx->player->offset, \
			mlx->player->player_y + j++ + mlx->player->offset, color);
		}
		i++;
	}
}

void	draw_black_screen(t_mlx *mlx)
{
	int		x;
	int		y;

	y = 0;
	while (y < mlx->vars->map_h * TILE_LEN)
	{
		x = 0;
		while (x < mlx->vars->map_w * TILE_LEN)
		{
			my_mlx_pixel_put(mlx, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	handle_events(t_mlx *mlx)
{
	double old_x;
	double old_y;

	old_x = mlx->player->player_x;
	old_y = mlx->player->player_y;
	if (mlx->player->key_w || mlx->player->key_s)
	{
		mlx->player->player_x += MOVE_SPEED * cos(mlx->player->player_angle) * mlx->player->direction_forward;
		mlx->player->player_y += MOVE_SPEED * sin(mlx->player->player_angle) * mlx->player->direction_forward;
	}
	if (mlx->player->key_a || mlx->player->key_d)
	{
		mlx->player->player_x += MOVE_SPEED * sin(mlx->player->player_angle) * mlx->player->direction_side;
		mlx->player->player_y -= MOVE_SPEED * cos(mlx->player->player_angle) * mlx->player->direction_side;
	}
	if (mlx->player->key_left)
	{
        mlx->player->player_angle -= ROT_SPEED;
        if (mlx->player->player_angle < 0)
            mlx->player->player_angle += 2 * M_PI;
    }
    else if (mlx->player->key_right)
    {
        mlx->player->player_angle += ROT_SPEED;
        if (mlx->player->player_angle >= 2 * M_PI)
            mlx->player->player_angle -= 2 * M_PI;
	}



	if (mlx->pars->map[(int)((mlx->player->player_y + TILE_LEN / 2)/ TILE_LEN)]\
	[(int)((old_x + TILE_LEN / 2) / TILE_LEN)] == '1')
		mlx->player->player_y = old_y;
	if (mlx->pars->map[(int)((old_y + TILE_LEN / 2) / TILE_LEN)]\
	[(int)((mlx->player->player_x + TILE_LEN / 2) / TILE_LEN)] == '1')
		mlx->player->player_x = old_x;
	// || check_circle_around_player(mlx, mlx->player->player_x, mlx->player->player_y, mlx->player->player_angle))
}
//  render 
int	 magic(t_mlx *mlx)
{
	int		x;
	int		y;
	int		color;
	t_vars	*vars;

	y = -1;
	vars = mlx->vars;
	draw_black_screen(mlx);
	handle_events(mlx);
	while (++y < mlx->vars->map_h)
	{
		x = 0;
		while (x < mlx->vars->map_w)
		{
			if (mlx->pars->map[y][x] == '1')
				color = WALL_COLOR;
			else if (mlx->pars->map[y][x] == ' ')
				color = SPACE_COLOR;
			else if (mlx->pars->map[y][x] == '0' || is_player(mlx->pars->map[y][x]))
				color = GROUND_COLOR;
			else if (mlx->pars->map[y][x] == '\0')
				color = SPACE_COLOR;
				// color = 0x4f81ff;
			draw_square(mlx, x++, y, color);
		}
	}
	draw_player(mlx, PLAYER_COLOR);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}

int control_key(int keycode, t_mlx *mlx)
{
    if (keycode == KEY_W)
	{
		mlx->player->key_w = 1;
		mlx->player->direction_forward = 1;
	}
	if (keycode == KEY_S)
	{
		mlx->player->key_s = 1;
		mlx->player->direction_forward = -1;
	}
    if (keycode == KEY_A)
	{
		mlx->player->key_a = 1;
		mlx->player->direction_side = LEFT;
	}
    if (keycode == KEY_D)
	{
		mlx->player->key_d = 1;
		mlx->player->direction_side = RIGHT;
	}
    if (keycode == KEY_LEFT)
		mlx->player->key_left = 1;
    if (keycode == KEY_RIGHT)
		mlx->player->key_right = 1;
    if (keycode == 53)
        exit(0);
    return 0;
}

int key_released(int keycode, t_mlx *mlx)
{
    if (keycode == KEY_W)
		mlx->player->key_w = 0;
	if (keycode == KEY_S)
		mlx->player->key_s = 0;
    if (keycode == KEY_A)
		mlx->player->key_a = 0;
    if (keycode == KEY_D)
		mlx->player->key_d = 0;
    if (keycode == KEY_LEFT)
		mlx->player->key_left = 0;
    if (keycode == KEY_RIGHT)
		mlx->player->key_right = 0;
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

t_mlx	*init(double *arr, int ac, char *av[])
{
	t_mlx *mlx;

	mlx = malloc (sizeof(t_mlx));
	mlx->pars = malloc (sizeof(t_pars));
	mlx->vars = malloc (sizeof(t_vars));
	mlx->player = malloc (sizeof(t_player));
	parsing(mlx->pars, ac, av);
	get_map_w_h(mlx->vars, mlx->pars);
	arr = get_player_position(mlx->pars->map);
	mlx->player->player_y = arr[0] * TILE_LEN;
	mlx->player->player_x = arr[1] * TILE_LEN;
	free(arr);
	get_player_direction(mlx);
	get_player_angle(mlx);
	mlx->height = mlx->vars->map_h * TILE_LEN;
	mlx->width = mlx->vars->map_w * TILE_LEN;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_M_PIxel, &mlx->img.line_length, &mlx->img.endian);
	mlx->player->key_a = 0;
	mlx->player->key_s = 0;
	mlx->player->key_d = 0;
	mlx->player->key_w = 0;
	mlx->player->key_left = 0;
	mlx->player->key_right = 0;
	return (mlx);
}

int main(int ac, char **av)
{
	t_mlx		*mlx;
	double		*arr;

	arr = NULL;
	mlx = init(arr, ac, av);
	mlx->player->rays = malloc((mlx->vars->map_w * TILE_LEN) * sizeof(t_rays));
/***********************                         ***************************/
	mlx_hook(mlx->win, 17, 0L, close_window, mlx);
	mlx_hook(mlx->win, 2, 1L << 2, control_key, mlx);
	mlx_hook(mlx->win, 3, 1L << 2, key_released, mlx);
	mlx_loop_hook(mlx->mlx, magic, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
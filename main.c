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

	if (ac < 2)
		error("Error\nNo input file\n");
	if (ac > 2)
		error("Error\nToo many arguments\n");
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		error("Error\nWrong file extension\n");
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

void draw_line(t_mlx *mlx, t_point point1, t_point point2, int index)
{
	double	x;
	double	y;
	double	step;
	double	i;
	double	j;

	x = point1.x;
	y = point1.y;
	step = 1;
	if (fabs(point2.x - point1.x) >= fabs(point2.y - point1.y))
		step = fabs(point2.x - point1.x);
	else
		step = fabs(point2.y - point1.y);
	i = (point2.x - point1.x) / step;
	j = (point2.y - point1.y) / step;
	mlx->player->rays[index].distance = step;
	while (step > 0)
	{
		my_mlx_pixel_put(mlx, x, y, LINE_COLOR);
		x += i;
		y += j;
		step--;
	}
}

double normalize_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

void	find_vertical(t_mlx *mlx, int id)
{
	t_point	intercept;
	t_point	delta;

	intercept.x = floor(mlx->player->player_center_x / TILE_LEN) * TILE_LEN + TILE_LEN * mlx->player->rays[id].is_ray_facing_right;
	if (mlx->player->rays[id].is_ray_facing_left)
		intercept.x -= 1;
	intercept.y = mlx->player->player_center_y + (intercept.x - mlx->player->player_center_x) * tan(mlx->player->rays[id].ray_angle);
	if (mlx->player->rays[id].is_ray_facing_left)
		delta.x = -TILE_LEN;
	else
		delta.x = TILE_LEN;
	if (mlx->player->rays[id].is_ray_facing_up)
		delta.y = -(TILE_LEN * fabs(tan(mlx->player->rays[id].ray_angle)));
	else
		delta.y = TILE_LEN * fabs(tan(mlx->player->rays[id].ray_angle));
	while (intercept.x >= 0 && intercept.x <= mlx->width && intercept.y >= 0 && intercept.y <= mlx->height)
	{
		if (mlx->pars->map[(int)(intercept.y / TILE_LEN)][(int)(intercept.x / TILE_LEN)] == '1')
		{
			mlx->player->rays[id].vert_hit_x = intercept.x;
			mlx->player->rays[id].vert_hit_y = intercept.y;
			mlx->player->rays[id].found_vert_wall_hit = 1;
			return ;
		}
		else
		{
			intercept.x += delta.x;
			intercept.y += delta.y;
		}
	}
}

void	find_horizontal(t_mlx *mlx, int id)
{
	t_point	intercept;
	t_point	delta;

	intercept.y = floor(mlx->player->player_center_y / TILE_LEN) * TILE_LEN + TILE_LEN * mlx->player->rays[id].is_ray_facing_down;
	if (mlx->player->rays[id].is_ray_facing_up)
		intercept.y -= 1;
	intercept.x = mlx->player->player_center_x + (intercept.y - mlx->player->player_center_y) / tan(mlx->player->rays[id].ray_angle);
	if (mlx->player->rays[id].is_ray_facing_up)
		delta.y = -TILE_LEN;
	else
		delta.y = TILE_LEN;
	if (mlx->player->rays[id].is_ray_facing_left)
		delta.x = -(TILE_LEN / fabs(tan(mlx->player->rays[id].ray_angle)));
	else
		delta.x = TILE_LEN / fabs(tan(mlx->player->rays[id].ray_angle));
	while (intercept.x >= 0 && intercept.x <= mlx->vars->map_w * TILE_LEN && intercept.y >= 0 && intercept.y <= mlx->vars->map_h * TILE_LEN)
	{
		if (mlx->pars->map[(int)(intercept.y / TILE_LEN)][(int)(intercept.x / TILE_LEN)] == '1')
		{
			mlx->player->rays[id].hor_hit_x = intercept.x;
			mlx->player->rays[id].hor_hit_y = intercept.y;
			mlx->player->rays[id].found_horz_wall_hit = 1;
			return ;
		}
		else
		{
			intercept.x += delta.x;
			intercept.y += delta.y;
		}
	}
}

double dist(t_point p1, t_point p2)
{
	return (sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));
}

t_point	get_wall_hit(t_mlx *mlx, int id)
{
	t_point	hor_hit;
	t_point	vert_hit;
	t_point	player_center;
	player_center = (t_point){mlx->player->player_center_x, mlx->player->player_center_y};
	hor_hit = (t_point){mlx->player->rays[id].hor_hit_x, mlx->player->rays[id].hor_hit_y};
	vert_hit = (t_point){mlx->player->rays[id].vert_hit_x, mlx->player->rays[id].vert_hit_y};
	if (mlx->player->rays[id].found_horz_wall_hit && mlx->player->rays[id].found_vert_wall_hit == 0)
		return (hor_hit);
	else if (mlx->player->rays[id].found_horz_wall_hit == 0 && mlx->player->rays[id].found_vert_wall_hit)
		return (vert_hit);
	if (dist(player_center, hor_hit) < dist(player_center, vert_hit) && mlx->player->rays[id].found_horz_wall_hit && mlx->player->rays[id].found_vert_wall_hit)
		return (hor_hit);
	else if (mlx->player->rays[id].found_horz_wall_hit && mlx->player->rays[id].found_vert_wall_hit)
		return (vert_hit);
	else
		return (player_center);
}

void	init_ray(t_rays *ray, double rayAngle)
{
	ray->found_horz_wall_hit = 0;
	ray->found_vert_wall_hit = 0;
	ray->is_ray_facing_down = rayAngle > 0 && rayAngle < M_PI;
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_left = rayAngle > M_PI / 2 && rayAngle < 1.5 * M_PI;
	ray->is_ray_facing_right = !ray->is_ray_facing_left;
}

// void	project_walls(t_mlx *mlx)
// {
// }

void CastRays(t_mlx *mlx)
{
	double	rayAngle;
	int		i;
	t_point	wall_hit;

	i = -1;
	rayAngle = normalize_angle(mlx->player->player_angle - (FOV_ANGLE / 2));
	while (++i < mlx->width)
	{
		mlx->player->rays[i].ray_id = i;
		init_ray(&mlx->player->rays[i], rayAngle);
		find_horizontal(mlx, i);
		find_vertical(mlx, i);
		wall_hit = get_wall_hit(mlx, i);
		draw_line(mlx, (t_point){mlx->player->player_center_x, mlx->player->player_center_y},
			wall_hit, i);
		rayAngle = normalize_angle(rayAngle + FOV_ANGLE / mlx->width);
		mlx->player->rays[i].ray_angle = rayAngle;
	}
	// project_walls(mlx);
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
	t_point	old;

	old.x = mlx->player->player_x;
	old.y = mlx->player->player_y;
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
        mlx->player->player_angle = normalize_angle(mlx->player->player_angle -  ROT_SPEED);
    else if (mlx->player->key_right)
        mlx->player->player_angle = normalize_angle(mlx->player->player_angle + ROT_SPEED);
	if (mlx->pars->map[(int)((mlx->player->player_y + TILE_LEN / 2)/ TILE_LEN)]\
	[(int)((old.x + TILE_LEN / 2) / TILE_LEN)] == '1')
		mlx->player->player_y = old.y;
	if (mlx->pars->map[(int)((old.y + TILE_LEN / 2) / TILE_LEN)]\
	[(int)((mlx->player->player_x + TILE_LEN / 2) / TILE_LEN)] == '1')
		mlx->player->player_x = old.x;
}

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
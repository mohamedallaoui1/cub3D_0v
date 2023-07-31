/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:15:18 by mallaoui          #+#    #+#             */
/*   Updated: 2023/07/31 13:48:30 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3D.h"

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

	// if (x <= 0 || x > (mlx->vars->map_w * TILE_SIZE)|| y <= 0 || y > (mlx->vars->map_h * TILE_SIZE))
	// 	return ;
	// getting color from address
	dst = mlx->img.addr + (y * mlx->img.line_length + x * (mlx->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	int_color(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

int	get_pixel_color(t_data *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_square(t_mlx *mlx, int x, int y, int color)
{
	int		i;
	int		j;
	int		square_size;

	i = 0;
	square_size = TILE_SIZE;
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

double		*player_pos(char **map)
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

void	player_center(t_mlx *mlx)
{
	mlx->player->center_x = mlx->player->pos.x + TILE_SIZE / 2;
	mlx->player->center_y = mlx->player->pos.y + TILE_SIZE / 2;
}

void draw_line(t_mlx *mlx, t_point point1, t_point point2)
{
	t_point	x_y;
	double	step;
	t_point	i_j;

	x_y.x = point1.x;
	x_y.y = point1.y;
	step = 1;
	if (fabs(point2.x - point1.x) >= fabs(point2.y - point1.y))
		step = fabs(point2.x - point1.x);
	else
		step = fabs(point2.y - point1.y);
	i_j.x = (point2.x - point1.x) / step;
	i_j.y = (point2.y - point1.y) / step;
	while (step > 0)
	{
		my_mlx_pixel_put(mlx, x_y.x, x_y.y, LINE_COLOR);
		x_y.x += i_j.x;
		x_y.y += i_j.y;
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

void	get_ver(t_mlx *mlx, int id)
{
	t_point	intercept;
	t_point	delta;

	intercept.x = floor(mlx->player->center_x / TILE_SIZE) * TILE_SIZE + TILE_SIZE * mlx->player->rays[id].facing_right;
	intercept.y = mlx->player->center_y + (intercept.x - mlx->player->center_x) * tan(mlx->player->rays[id].ray_angle);
	if (mlx->player->rays[id].facing_left)
		delta.x = -TILE_SIZE;
	else
		delta.x = TILE_SIZE;
	if (mlx->player->rays[id].facing_up)
		delta.y = -(TILE_SIZE * fabs(tan(mlx->player->rays[id].ray_angle)));
	else
		delta.y = TILE_SIZE * fabs(tan(mlx->player->rays[id].ray_angle));
	while (intercept.x >= 0 && intercept.x < mlx->width && intercept.y >= 0 && intercept.y < mlx->height)
	{
		if (mlx->pars->map[(int)(intercept.y / TILE_SIZE)][(int)((intercept.x - 0.01 * mlx->player->rays[id].facing_left) / TILE_SIZE)] == '1')
		{
			mlx->player->rays[id].vert_hit_x = intercept.x;
			mlx->player->rays[id].vert_hit_y = intercept.y;
			mlx->player->rays[id].found_vert = 1;
			return ;
		}
		intercept.x += delta.x;
		intercept.y += delta.y;
	}
}

void	get_hor(t_mlx *mlx, int id)
{
	t_point	intercept;
	t_point	delta;

	intercept.y = floor(mlx->player->center_y / TILE_SIZE) * TILE_SIZE + TILE_SIZE * mlx->player->rays[id].facing_down;
	intercept.x = mlx->player->center_x + (intercept.y - mlx->player->center_y) / tan(mlx->player->rays[id].ray_angle);
	if (mlx->player->rays[id].facing_up)
		delta.y = -TILE_SIZE;
	else
		delta.y = TILE_SIZE;
	if (mlx->player->rays[id].facing_left)
		delta.x = -(TILE_SIZE / fabs(tan(mlx->player->rays[id].ray_angle)));
	else
		delta.x = TILE_SIZE / fabs(tan(mlx->player->rays[id].ray_angle));
	while (intercept.x >= 0 && intercept.x < mlx->width && intercept.y >= 0 && intercept.y < mlx->height)
	{
		if (mlx->pars->map[(int)((intercept.y - 0.01 * mlx->player->rays[id].facing_up) / TILE_SIZE)][(int)((intercept.x) / TILE_SIZE)] == '1')
		{
			mlx->player->rays[id].hor_hit_x = intercept.x;
			mlx->player->rays[id].hor_hit_y = intercept.y;
			mlx->player->rays[id].found_horz = 1;
			return ;
		}
		intercept.x += delta.x;
		intercept.y += delta.y;
	}
}

double dist_(t_point p1, t_point p2)
{
	return (sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));
}

t_point	get_wall_hit(t_mlx *mlx, int id)
{
	t_point	hor_hit;
	t_point	vert_hit;
	t_point	player_center;

	player_center = (t_point){mlx->player->center_x, mlx->player->center_y};
	hor_hit = (t_point){mlx->player->rays[id].hor_hit_x, mlx->player->rays[id].hor_hit_y};
	vert_hit = (t_point){mlx->player->rays[id].vert_hit_x, mlx->player->rays[id].vert_hit_y};
	if (mlx->player->rays[id].found_horz && mlx->player->rays[id].found_vert == 0)
		return (mlx->player->rays[id].is_hor = 1, hor_hit);
	else if (mlx->player->rays[id].found_horz == 0 && mlx->player->rays[id].found_vert)
		return (mlx->player->rays[id].is_hor = 0, vert_hit);
	if (dist_(player_center, hor_hit) < dist_(player_center, vert_hit) && mlx->player->rays[id].found_horz && mlx->player->rays[id].found_vert)
		return (mlx->player->rays[id].is_hor = 1, hor_hit);
	else if (mlx->player->rays[id].found_horz && mlx->player->rays[id].found_vert)
		return (mlx->player->rays[id].is_hor = 0, vert_hit);
	else
		return (mlx->player->rays[id].is_hor = 0, player_center);
}

void	init_ray(t_rays *ray, double rayAngle)
{
	ray->ray_angle = rayAngle;
	ray->found_horz = 0;
	ray->found_vert = 0;
	ray->facing_down = rayAngle > 0 && rayAngle < M_PI;
	ray->facing_up = !ray->facing_down;
	ray->facing_left = rayAngle > M_PI / 2 && rayAngle < 1.5 * M_PI;
	ray->facing_right = !ray->facing_left;
}

unsigned int	shading(int color, double dist)
{
    unsigned int red = (color >> 16) & 0xFF;
    unsigned int alpha = (color >> 24) & 0xFF;
    unsigned int green = (color >> 8) & 0xFF;
    unsigned int blue = color & 0xFF;

	if (dist > 1)
		dist = 1;
	alpha = (unsigned int)(255 * dist);
    return (alpha << 24 | red << 16 | green << 8 | blue);
}

t_data	*get_texture(t_mlx *mlx, int id)
{
	if (mlx->player->rays[id].is_hor)
	{
		if (mlx->player->rays[id].facing_up)
			return (&mlx->textures[1]);
		else
			return (&mlx->textures[0]);
	}
	else
	{
		if (mlx->player->rays[id].facing_left)
			return (&mlx->textures[2]);
		else
			return (&mlx->textures[3]);
	}
}

void	project_wall(t_mlx *mlx, int id)
{
	int		i;
	int		p_wall_h;
	double	val;
	double	count;
	double	dist;

	if (mlx->player->rays[id].is_hor)
		val = get_wall_hit(mlx, id).x / TILE_SIZE;
	else
		val = get_wall_hit(mlx, id).y / TILE_SIZE;
	val = (val - (int)val) * get_texture(mlx, id)->img_width;
	i = -1;
	count = 0;
	dist = mlx->player->rays[id].dist;
	if (dist == 0)
		dist = 10;
	p_wall_h = round((TILE_SIZE / dist) * PROJ_DIST);
	if (p_wall_h > HEIGHT)
		count = (p_wall_h - HEIGHT) / 2;
	while (++i < HEIGHT)
	{
		if (i < HEIGHT / 2 - p_wall_h / 2)
			my_mlx_pixel_put(mlx, id, i, shading(int_color(mlx->pars->c_rgb), (double)i / (double)(HEIGHT / 2)));
		else if (i >= HEIGHT / 2 - p_wall_h / 2 && i < HEIGHT / 2 + p_wall_h / 2)
			my_mlx_pixel_put(mlx, id, i,
				shading(get_pixel_color(get_texture(mlx, id), val
					, (count++ / p_wall_h) * mlx->textures[0].img_height),  dist / SHADE_RANGE));
		else
			my_mlx_pixel_put(mlx, id, i, shading(int_color(mlx->pars->f_rgb), (double)(HEIGHT / 2) / (double)i));
	}
}

void castrays(t_mlx *mlx)
{
	double	rayAngle;
	int		i;
	t_point	wall_hit;

	i = -1;
	player_center(mlx);
	rayAngle = normalize_angle(mlx->player->player_angle - (FOV_ANGLE / 2));
	while (++i < WIDTH)
	{
		mlx->player->rays[i].ray_id = i;
		init_ray(&mlx->player->rays[i], rayAngle);
		get_ver(mlx, i);
		get_hor(mlx, i);
		wall_hit = get_wall_hit(mlx, i);
		mlx->player->rays[i].dist = dist_((t_point){mlx->player->center_x, mlx->player->center_y}
				, wall_hit) * cos(rayAngle - mlx->player->player_angle);
		project_wall(mlx, i);
		rayAngle = normalize_angle(rayAngle + FOV_ANGLE / (double)WIDTH);
	}
}

void	draw_player(t_mlx *mlx, int color)
{
	int	player_square_size;
	int	i;
	int	j;

	player_square_size = 8;
	mlx->player->offset = (TILE_SIZE - player_square_size) / 2;
	player_center(mlx);
	i = 0;
	while (i < player_square_size)
	{
		j = 0;
		while (j < player_square_size)
		{
			my_mlx_pixel_put(mlx, mlx->player->pos.x + i + mlx->player->offset, \
			mlx->player->pos.y + j++ + mlx->player->offset, color);
		}
		i++;
	}
}

void	draw_black_screen(t_mlx *mlx)
{
	int		x;
	int		y;

	y = 0;
	while (y < mlx->vars->map_h * TILE_SIZE)
	{
		x = 0;
		while (x < mlx->vars->map_w * TILE_SIZE)
		{
			my_mlx_pixel_put(mlx, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	handle_events(t_mlx *mlx)
{
	if (mlx->player->keys.key_w || mlx->player->keys.key_s)
		up_down(mlx);
	if (mlx->player->keys.key_a || mlx->player->keys.key_d)
		left_right(mlx);
	if (mlx->player->keys.key_left)
        mlx->player->player_angle = normalize_angle(mlx->player->player_angle -  ROT_SPEED);
    else if (mlx->player->keys.key_right)
        mlx->player->player_angle = normalize_angle(mlx->player->player_angle + ROT_SPEED);
}

int	 magic(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	handle_events(mlx);
	castrays(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}

int control_key(int keycode, t_mlx *mlx)
{
    if (keycode == KEY_W)
	{
		mlx->player->keys.key_w = 1;
		if (!mlx->player->dir_forw)
			mlx->player->dir_forw = 1;
	}
	if (keycode == KEY_S)
	{
		mlx->player->keys.key_s = 1;
		if (!mlx->player->dir_forw)
			mlx->player->dir_forw = -1;
	}
    if (keycode == KEY_A)
	{
		mlx->player->keys.key_a = 1;
		if (!mlx->player->dir_side)
			mlx->player->dir_side = LEFT;
	}
    if (keycode == KEY_D)
	{
		mlx->player->keys.key_d = 1;
		if (!mlx->player->dir_side)
			mlx->player->dir_side = RIGHT;
	}
    if (keycode == KEY_LEFT)
		mlx->player->keys.key_left = 1;
    if (keycode == KEY_RIGHT)
		mlx->player->keys.key_right = 1;
    (keycode == 53) && (exit(0), 0);
    return 0;
}

int key_released(int keycode, t_mlx *mlx)
{
    if (keycode == KEY_W)
	{
		mlx->player->keys.key_w = 0;
		mlx->player->dir_forw = 0;
	}
	if (keycode == KEY_S)
	{
		mlx->player->keys.key_s = 0;
		mlx->player->dir_forw = 0;
	}
    if (keycode == KEY_A)
	{
		mlx->player->keys.key_a = 0;
		mlx->player->dir_side = 0;	
	}
    if (keycode == KEY_D)
	{
		mlx->player->keys.key_d = 0;
		mlx->player->dir_side = 0;	
	}
    if (keycode == KEY_LEFT)
		mlx->player->keys.key_left = 0;
    if (keycode == KEY_RIGHT)
		mlx->player->keys.key_right = 0;
    return 0;
}

void	set_player_dir(t_mlx *mlx)
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
				mlx->player->player_dir = mlx->pars->map[i][j];
				break ;
			}
			j++;
		}
		i++;
	}
}

void	player_angle(t_mlx *mlx)
{
    if (mlx->player->player_dir == 'N')
        mlx->player->player_angle = 3 * M_PI / 2;
    else if (mlx->player->player_dir == 'S')
        mlx->player->player_angle = M_PI / 2;
    else if (mlx->player->player_dir == 'E')
        mlx->player->player_angle = 0;
    else if (mlx->player->player_dir == 'W')
        mlx->player->player_angle = M_PI;
}

void	texture_init(t_mlx *mlx)
{
	int	i;
	char	**strs;

	i = -1;
	strs = (char *[4]){mlx->pars->no, mlx->pars->so, mlx->pars->ea, mlx->pars->we};
	while (++i < 4)
	{
		mlx->textures[i].img = mlx_xpm_file_to_image(mlx->mlx,
				strs[i], &mlx->textures[i].img_width, &mlx->textures[i].img_height);
		if (!mlx->textures[i].img)
			(write(1, "Error\nImage Does not exist!", 28), exit(i));
		mlx->textures[i].addr = mlx_get_data_addr(mlx->textures[i].img,
				&mlx->textures[i].bits_per_pixel, &mlx->textures[i].line_length, &mlx->textures[i].endian);
		if (!mlx->textures[i].addr)
			(write(1, "Error\nImage Problem!", 28), exit(i));
	}

}

t_mlx	*init(double *arr, int ac, char *av[])
{
	t_mlx *mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->pars = malloc(sizeof(t_pars));
	mlx->vars = malloc(sizeof(t_vars));
	mlx->player = malloc(sizeof(t_player));
	parsing(mlx->pars, ac, av);
	map_w_h(mlx->vars, mlx->pars);
	arr = player_pos(mlx->pars->map);
	mlx->player->pos.y = arr[0] * TILE_SIZE;
	mlx->player->pos.x = arr[1] * TILE_SIZE;
	free(arr);
	set_player_dir(mlx);
	player_angle(mlx);
	mlx->height = mlx->vars->map_h * TILE_SIZE;
	mlx->width = mlx->vars->map_w * TILE_SIZE;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	texture_init(mlx);
	mlx->player->keys.key_a = 0;
	mlx->player->keys.key_s = 0;
	mlx->player->keys.key_d = 0;
	mlx->player->keys.key_w = 0;
	mlx->player->dir_forw = 0;
	mlx->player->dir_side = 0;
	mlx->player->keys.key_left = 0;
	mlx->player->keys.key_right = 0;
	return (mlx);
}

int main(int ac, char **av)
{
	t_mlx		*mlx;
	double		*arr;

	arr = NULL;
	mlx = init(arr, ac, av);
	mlx->player->rays = malloc(WIDTH * sizeof(t_rays));
/***********************                         ***************************/

	mlx_hook(mlx->win, 17, 0L, close_window, mlx);
	mlx_hook(mlx->win, 2, 1L << 2, control_key, mlx);
	mlx_hook(mlx->win, 3, 1L << 2, key_released, mlx);
	mlx_loop_hook(mlx->mlx, magic, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
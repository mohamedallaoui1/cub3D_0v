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

	if (x < 0 || x >= mlx->width|| y < 0 || y >= mlx->height)
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
	mlx->player->player_center_x = mlx->player->px * TILE_LEN + TILE_LEN /2;
	mlx->player->player_center_y = mlx->player->py * TILE_LEN + TILE_LEN /2;
}

void draw_line(t_mlx *mlx, double x1, double y1, double x2, double y2)
{
    double dx;
    double dy;
    int steps;
    float xIncrement;
    float yIncrement;
    float x;
	int	i;
    float y;
    
	dx = x2 - x1;
    dy = y2 - y1;
    if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
    xIncrement = (float)dx / (float)steps;
    yIncrement = (float)dy / (float)steps;
    x = x1;
    y = y1;
	i = -1;
	while (++i <= steps)
    {
        my_mlx_pixel_put(mlx, (int)x, (int)y, LINE_COLOR);
        x += xIncrement;
        y += yIncrement;
    }
}

void	dir_next_grid(t_mlx *mlx, double *x, double *y)
{
	t_vector	dir;

	if (mlx->player->dir_x < 0)
	{
		*x = -1;
		dir.x = floor(mlx->player->dir_x);
	}
	else
	{
		*x = 0;
		dir.x = ceil(mlx->player->dir_x);
	}
	*y = mlx->player->dir_y;
}

void	ray_casting(t_mlx *mlx)
{
	t_vector	ray_dir;
	double		CameraX;
	double		i;
	double		x;
	double		y;

	i = 0.0;
	// printf("Width ==== %d\n", mlx->width);
	// CameraX = (2 * i - mlx->width) /  mlx->width;
	// printf("cam_x: %f\n", CameraX);
	// exit(0);
	while (i <  mlx->width)
	{
		dir_next_grid(mlx, &x, &y);
		CameraX = (2 * i - (double)mlx->width) /  (double)mlx->width;
		ray_dir.x = (mlx->player->px + 0.5) + mlx->player->dir_x + mlx->player->plane_x * CameraX;
		ray_dir.y = (mlx->player->py + 0.5) + mlx->player->dir_y + mlx->player->plane_y * CameraX;
		// printf("index = %f, cam_x: %f\n", i, CameraX);
		// printf("px = %f, ray_dir_x: %f\n", mlx->player->px, ray_dir.x);
		// printf("py = %f, ray_dir_y: %f\n", mlx->player->py, ray_dir.y);
		draw_line(mlx,
			mlx->player->player_center_x,
			mlx->player->player_center_y,
			ray_dir.x * TILE_LEN,
			ray_dir.y * TILE_LEN);
		i++;
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
	// draw_plane(mlx);
	// draw_line(mlx, mlx->player->player_center_x, mlx->player->player_center_y,
	// 	mlx->player->player_center_x + LINE_LEN * cos(mlx->player->player_angle),
	// 	mlx->player->player_center_y + LINE_LEN * sin(mlx->player->player_angle)
	// , 0);
	ray_casting(mlx);
	i = 0;
	while (i < player_square_size)
	{
		j = 0;
		while (j < player_square_size)
		{
			my_mlx_pixel_put(mlx, mlx->player->px * TILE_LEN + i + mlx->player->offset, \
			mlx->player->py * TILE_LEN + j++ + mlx->player->offset, color);
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

	old_x = mlx->player->px;
	old_y = mlx->player->py;
	if (mlx->player->keys.key_w || mlx->player->keys.key_s)
	{
		mlx->player->px += mlx->player->dir_x * MOVE_SPEED * mlx->player->direction_ws;
		mlx->player->py += mlx->player->dir_y * MOVE_SPEED * mlx->player->direction_ws;
	}
	if (mlx->player->keys.key_a || mlx->player->keys.key_d)
	{
		mlx->player->px += -1 * mlx->player->dir_y * MOVE_SPEED * mlx->player->direction_ad;
		mlx->player->py += mlx->player->dir_x * MOVE_SPEED * mlx->player->direction_ad;
	}
	if (mlx->player->keys.key_left || mlx->player->keys.key_right)
		update_angle(mlx);

	if (mlx->pars->map[(int)(mlx->player->py + 0.5)]\
	[(int)(old_x + 0.5)] == '1')
		mlx->player->py = old_y;
	if (mlx->pars->map[(int)(old_y + 0.5)]\
	[(int)(mlx->player->px + 0.5)] == '1')
		mlx->player->px = old_x;
	get_player_center(mlx);
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
		mlx->player->keys.key_w = 1;
		mlx->player->direction_ws = 1;
	}
	if (keycode == KEY_S)
	{
		mlx->player->keys.key_s = 1;
		mlx->player->direction_ws = -1;
	}
    if (keycode == KEY_A)
	{
		mlx->player->keys.key_a = 1;
		mlx->player->direction_ad = LEFT;
	}
    if (keycode == KEY_D)
	{
		mlx->player->keys.key_d = 1;
		mlx->player->direction_ad = RIGHT;
	}
    if (keycode == KEY_LEFT)
		mlx->player->keys.key_left = 1;
    if (keycode == KEY_RIGHT)
		mlx->player->keys.key_right = -1;
    if (keycode == 53)
        exit(0);
    return 0;
}

int key_released(int keycode, t_mlx *mlx)
{
    if (keycode == KEY_W)
		mlx->player->keys.key_w = 0;
	if (keycode == KEY_S)
		mlx->player->keys.key_s = 0;
    if (keycode == KEY_A)
		mlx->player->keys.key_a = 0;
    if (keycode == KEY_D)
		mlx->player->keys.key_d = 0;
    if (keycode == KEY_LEFT)
		mlx->player->keys.key_left = 0;
    if (keycode == KEY_RIGHT)
		mlx->player->keys.key_right = 0;
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
				if (mlx->pars->map[i][j] == 'N')
					mlx->player->dir_y = -1;
				else if (mlx->pars->map[i][j] == 'S')
					mlx->player->dir_y = 1;
				else if (mlx->pars->map[i][j] == 'W')
					mlx->player->dir_x = -1;
				else if (mlx->pars->map[i][j] == 'E')
					mlx->player->dir_x = 1;
				break ;
			}
			j++;
		}
		i++;
	}
}


void	rotate(double *x, double *y, double angle)
{
	double	tmp_x;

	tmp_x = *x;
	*x = *x * cos(angle) - *y * sin(angle);
	*y = *y * cos(angle) + tmp_x * sin(angle);
}

void	update_angle(t_mlx *mlx)
{
	double	angle;

	angle = ROT_SPEED * (1.0 - 2.0 * (mlx->player->keys.key_left));
	rotate(&mlx->player->dir_x, &mlx->player->dir_y, angle);
	rotate(&mlx->player->plane_x, &mlx->player->plane_y, angle);
}

// void	get_player_angle(t_mlx *mlx)
// {
//     // if (mlx->player->player_direction == 'N')
//     //     mlx->player->player_angle = 3 * M_PI / 2;
//     // else if (mlx->player->player_direction == 'E')
//     //     mlx->player->player_angle = M_PI / 2;
//     // else if (mlx->player->player_direction == 'S')
//     //     mlx->player->player_angle = 0;
//     // else if (mlx->player->player_direction == 'W')
//     //     mlx->player->player_angle = M_PI;
// }

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
	mlx->player->py = arr[0];
	mlx->player->px = arr[1];
	free(arr);
	mlx->player->keys.key_a = 0;
	mlx->player->keys.key_s = 0;
	mlx->player->keys.key_d = 0;
	mlx->player->keys.key_w = 0;
	mlx->player->keys.key_left = 0;
	mlx->player->keys.key_right = 0;
	mlx->player->direction_ad = 0;
	mlx->player->direction_ws = 0;
	mlx->player->dir_x = 0;
	mlx->player->dir_y = 0;
	get_player_direction(mlx);
	// get_player_angle(mlx);
	mlx->height = mlx->vars->map_h * TILE_LEN;
	mlx->width = mlx->vars->map_w * TILE_LEN;
	mlx->player->plane_x = 0;
	mlx->player->plane_y = tan(FOV_ANGLE / 2);
	// plane->x - (player.x + LINE_LEN * dir.x) + plane->y - (player.y + LINE_LEN * dir.y) = FOV_ANGLE / 2
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "cub3D");
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_M_PIxel, &mlx->img.line_length, &mlx->img.endian);

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
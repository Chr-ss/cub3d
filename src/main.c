/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: andmadri <andmadri@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 13:49:00 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/12 01:32:19 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	mlx_finish(t_minilx *milx)
{
	mlx_destroy_display(milx->mlx);
	mlx_destroy_window(milx->mlx, milx->mlx_window);
	free(milx->mlx);
	exit(0);
}

int	key_press(int keycode, t_minilx *milx)
{
	if (keycode == 0xff1b)
		mlx_finish(milx);
	return (0);
}

void	img_mlx_pixel_put(t_minilx_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_map_square(t_data *data, t_minilx *milx, int y, int x, int color)
{
	int	pixel_x;
	int	pixel_y;
	int	sq_size;

	sq_size = MINI_MAP / data->map.x_max;
	if (sq_size > (MINI_MAP / data->map.y_max))
		sq_size = MINI_MAP / data->map.y_max;
	pixel_x = (x * sq_size);
	while (++pixel_x < sq_size + (x * sq_size))
	{
		pixel_y = (y * sq_size);
		while (++pixel_y < sq_size + (y * sq_size))
		{
			img_mlx_pixel_put(&(milx->mini[DRAW]), pixel_x, pixel_y, color);
		}
	}
}

void	draw_map(void *param)
{
	t_data		*data;
	t_minilx	*milx;

	data = (t_data *) param;
	milx = &data->milx;
	int	x;
	int	y;

	x = -1;
	while (++x < MINI_MAP)
	{
		y = -1;
		while (++y < MINI_MAP)
		{
			img_mlx_pixel_put(&(milx->mini[DRAW]), x, y, create_trgb(100, 24, 24, 24));
		}
	}
	t_map *map = &(data->map);
	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == ' ')
				draw_map_square(data, milx, y, x, create_trgb(0, 22, 22, 22));
			else if (map->map[y][x] == '1')
				draw_map_square(data, milx, y, x, create_trgb(0, 88, 77, 66));
			else if (map->map[y][x] == '0')
				draw_map_square(data, milx, y, x, create_trgb(0, 155, 125, 98));
			x++;
		}
		y++;
	}
	(void)data;
}

void draw_player_line(t_minilx *milx, int x_start, int x_end, int y, int color)
{
	while (x_start <= x_end)
	{
		img_mlx_pixel_put(&(milx->mini[DRAW]), x_start, y, color);
		x_start++;
	}
}
void	draw_player(t_minilx *milx, int color, int radius)
{
	int	center;
	int y;
	int decision;

	center = MINI_MAP / 2;
	decision = 1 - radius;
	y = 0;
	while (y <= radius)
	{
		draw_player_line(milx, center - radius, center + radius, center + y, color);
		draw_player_line(milx, center - radius, center + radius, center - y, color);
		draw_player_line(milx, center - y, center + y, center + radius, color);
		draw_player_line(milx, center - y, center + y, center - radius, color);
		y++;
		if (decision <= 0)
			decision += 2 * y + 1;
		else
			decision += 2 * (y - radius--) + 1;
	}
}

void draw_pov_line(t_minilx *milx, int x0, int y0, float vx, float vy, int length, int color)
{
	float magnitude = sqrt(vx * vx + vy * vy);
	vx /= magnitude;
	vy /= magnitude;

	float x = x0;
	float y = y0;

	for (int i = 0; i < length; i++)
	{
		img_mlx_pixel_put(&(milx->mini[DRAW]), (int)round(x), (int)round(y), color);
		x += vx;
		y += vy;
	}
}

void	draw_pov(t_data *data, t_minilx *milx, int color, int size)
{
	// printf("POV: %fx%f, %fx%f\n", data->player.pos[X], data->player.pos[Y], data->player.direct[X], data->player.direct[Y]);
	draw_pov_line(milx, MINI_MAP / 2, MINI_MAP / 2, data->player.direct[X], data->player.direct[Y], size, color);
}

void	draw_border(t_minilx *milx, int color, int size)
{
	int	x;
	int	y;

	y = 0;
	while (y <= MINI_MAP)
	{
		x = MINI_MAP;
		while (x < MINI_MAP + size)
		{
			img_mlx_pixel_put(&(milx->mini[DRAW]), x, y, color);
			x++;
		}
		y++;
	}
	y = MINI_MAP;
	while (y <= MINI_MAP + size)
	{
		x = 0;
		while (x < MINI_MAP + size)
		{
			img_mlx_pixel_put(&(milx->mini[DRAW]), x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_clear(t_minilx *milx)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINI_MAP + 20)
	{
		x = 0;
		while (x < MINI_MAP + 20)
		{
			img_mlx_pixel_put(&(milx->mini[DRAW]), x, y, 0);
			x++;
		}
		y++;
	}
}

int	draw_minimap_switch_display(void *param)
{
	t_minilx_img	buffer;
	t_data			*data;

	data = (t_data *) param;
	buffer = data->milx.mini[DRAW];
	data->milx.mini[DRAW] = data->milx.mini[DISPLAY];
	data->milx.mini[DISPLAY] = buffer;
	mlx_put_image_to_window(data->milx.mlx, data->milx.mlx_window, data->milx.mini[DISPLAY].img, 0, 0);
	return (0);
}

int	draw_minimap(void *param)
{
	t_data		*data;
	t_minilx	*milx;

	data = (t_data *) param;
	milx = &data->milx;
	draw_clear(milx);
	draw_border(milx, create_trgb(0, 55, 55, 55), 10);
	draw_player(milx, create_trgb(0, 20, 80, 200), 10);
	draw_pov(data, milx, create_trgb(0, 255, 0, 255), 30);
	draw_minimap_switch_display(data);
	return (0);
}

// W 119, A 97, S 115, D 100
int	key_hook_wasd(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == 119)
	{
		data->player.pos[X] += data->player.direct[X];
		data->player.pos[Y] += data->player.direct[Y];
	}
	else if (keycode == 115)
	{
		data->player.pos[X] -= data->player.direct[X];
		data->player.pos[Y] -= data->player.direct[Y];
	}
	else if (keycode == 97)
	{
		data->player.direct[X] = data->player.direct[X] * cos(-0.1) - data->player.direct[Y] * sin(-0.1);
		data->player.direct[Y] = data->player.direct[X] * sin(-0.1) + data->player.direct[Y] * cos(-0.1);
		data->player.direct[X] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
		data->player.direct[Y] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
	}
	else if (keycode == 100)
	{
		data->player.direct[X] = data->player.direct[X] * cos(0.1) - data->player.direct[Y] * sin(0.1);
		data->player.direct[Y] = data->player.direct[X] * sin(0.1) + data->player.direct[Y] * cos(0.1);
		data->player.direct[X] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
		data->player.direct[Y] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
	}
	printf("\tPOS: %f %f\tVIEW: %f %f\n", data->player.pos[X], data->player.pos[Y], data->player.direct[X], data->player.direct[Y]);
	return (0);
}

void	image(t_data *data)
{
	data->milx.mini[0].img = mlx_new_image(data->milx.mlx, MINI_MAP + 50, MINI_MAP + 50);
	data->milx.mini[1].img = mlx_new_image(data->milx.mlx, MINI_MAP + 50, MINI_MAP + 50);
	data->milx.mini[0].addr = mlx_get_data_addr(data->milx.mini[0].img, &data->milx.mini[0].bits_per_pixel, &data->milx.mini[0].line_length, &data->milx.mini[0].endian);
	data->milx.mini[1].addr = mlx_get_data_addr(data->milx.mini[1].img, &data->milx.mini[1].bits_per_pixel, &data->milx.mini[1].line_length, &data->milx.mini[1].endian);
}

int	main(int argc, char **argv)
{
	t_data		data;

	ft_bzero(&data, sizeof(t_data));
	if (argc <= 1)
		error("Missing map.", &data);
	else if (argc > 2)
		error("To many arguments.", &data);
	data.map.map_read.filename = argv[1];
	map_init(&data, &data.map);
	map_parse(&data, data.map.map);
	map_print(&data, &data.map);

	data.milx.mlx = mlx_init();
	if (!data.milx.mlx)
		return (EXIT_FAILURE); //maybe do it somewhere else or free something
	// mlx_get_screen_size(milx.mlx, &milx.size_x, &milx.size_y);
	data.milx.size_x = 800;
	data.milx.size_y = 800;
	data.milx.mlx_window = mlx_new_window(data.milx.mlx, data.milx.size_x, data.milx.size_y, "CUBE3D");
	if (!data.milx.mlx_window)
		return (free(data.milx.mlx), free_all(&data), EXIT_FAILURE); //maybe free_all data
	image(&data);
	mlx_loop_hook(data.milx.mlx, draw_minimap, (void *)&data);
	mlx_hook(data.milx.mlx_window, 17, 0L, &mlx_finish, &data.milx); // closing the window with x in window
	mlx_hook(data.milx.mlx_window, 2, 1L << 0, &key_press, &data.milx); // closing the window with ESC
	mlx_key_hook(data.milx.mlx_window, key_hook_wasd, (void *)&data);
	mlx_loop(data.milx.mlx);
	free_all(&data); //it should go here?/
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: andmadri <andmadri@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 13:49:00 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/11 21:24:51 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	mlx_finish(t_minilx *milx)
{
	// mlx_destroy_display(milx->mlx);
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
			mlx_pixel_put(milx->mlx, milx->mlx_window, pixel_x, pixel_y, color);
		}
	}
}

void	draw_map(t_data *data, t_minilx *milx)
{
	int	x;
	int	y;

	x = -1;
	while (++x < MINI_MAP)
	{
		y = -1;
		while (++y < MINI_MAP)
		{
			mlx_pixel_put(milx->mlx, milx->mlx_window, x, y, create_trgb(100, 24, 24, 24));
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
		mlx_pixel_put(milx->mlx, milx->mlx_window, x_start, y, color);
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

void draw_pov_line(t_minilx *milx, int x0, int y0, float vx, float vy, int length, int color) {
    float magnitude = sqrt(vx * vx + vy * vy);
    vx /= magnitude;
    vy /= magnitude;

    float x = x0;
    float y = y0;

    for (int i = 0; i < length; i++) {
		mlx_pixel_put(milx->mlx, milx->mlx_window, (int)round(x), (int)round(y), color);
        // draw_pixel((int)round(x), (int)round(y)); // Draw the nearest pixel
        x += vx;  // Step in the x direction
        y += vy;  // Step in the y direction
    }
}

void	draw_pov(t_data *data, t_minilx *milx, int color, int size)
{
	draw_pov_line(milx, MINI_MAP / 2, MINI_MAP / 2, data->player.direction[X], data->player.direction[Y], size, color);
}

void	draw_minimap(t_data *data, t_minilx *milx)
{
	draw_pov(data, milx, create_trgb(0, 20, 80, 200), 10);
	draw_player(milx, create_trgb(0, 20, 80, 200), 10);
	(void)data;
}

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

int	main(int argc, char **argv)
{
	t_data		data;
	t_minilx	milx;

	ft_bzero(&data, sizeof(t_data));
	if (argc <= 1)
		error("Missing map.", &data);
	else if (argc > 2)
		error("To many arguments.", &data);
	data.map.map_read.filename = argv[1];
	map_init(&data, &data.map);
	map_parse(&data, data.map.map);
	map_print(&data, &data.map);

	milx.mlx = mlx_init();
	if (!milx.mlx)
		return (EXIT_FAILURE); //maybe do it somewhere else or free something
	// mlx_get_screen_size(milx.mlx, &milx.size_x, &milx.size_y);
	milx.size_x = 1920;
	milx.size_y = 1080;
	milx.mlx_window = mlx_new_window(milx.mlx, milx.size_x, milx.size_y, "CUBE3D");
	if (!milx.mlx_window)
		return (free(milx.mlx), EXIT_FAILURE); //maybe free_all data
	// draw_map(&data, &milx);
	draw_minimap(&data, &milx);
	mlx_hook(milx.mlx_window, 17, 0L, &mlx_finish, &milx); // closing the window with x in window
	mlx_hook(milx.mlx_window, 2, 1L << 0, &key_press, &milx); // closing the window with ESC
	mlx_loop(milx.mlx);
	free_all(&data); //it should go here?/
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: andmadri <andmadri@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 13:49:00 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:47:01 by crasche       ########   odam.nl         */
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

void	draw_minimap(t_data *data, t_minilx *milx)
{

}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc <= 1)
		error("Missing map.", &data);
	else if (argc > 2)
		error("To many arguments.", &data);
	data.map.map_read.filename = argv[1];
	map_init(&data, &data.map);
	// rgb_check(&data, &data.map);
	map_parse(&data, data.map.map);
	map_print(&data, &data.map);
	
	milx.mlx = mlx_init();
	if (!milx.mlx)
		return (EXIT_FAILURE); //maybe do it somewhere else or free something
	mlx_get_screen_size(milx.mlx, &milx.size_x, &milx.size_y);
	// milx.size_x = 1920;
	// milx.size_y = 1080;
	milx.mlx_window = mlx_new_window(milx.mlx, milx.size_x, milx.size_y, "CUBE3D");
	if (!milx.mlx_window)
		return (free(milx.mlx), EXIT_FAILURE); //maybe free_all data
	draw_map(&data, &milx);
	draw_minimap(&data, &milx);
	mlx_hook(milx.mlx_window, 17, 0L, &mlx_finish, &milx); // closing the window with x in window
	mlx_hook(milx.mlx_window, 2, 1L << 0, &key_press, &milx); // closing the window with ESC
	mlx_loop(milx.mlx);
	free_all(&data); //it should go here?/
	return (0);
}

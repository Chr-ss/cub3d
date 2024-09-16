/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:49:00 by crasche           #+#    #+#             */
/*   Updated: 2024/09/13 23:15:13 by andmadri         ###   ########.fr       */
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

// int	inbounds(float	x, float y, t_map map)
// {
// 	if (x >= 0 && y >= 0 &&  x < map.x_max && y <  x > map.y_max)
// 		return (1);
// 	return (0);
// }


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

void	draw_pov(t_data *data, t_minilx *milx, int color, int length)
{
	// printf("POV: %fx%f, %fx%f\n", data->player.pos[X], data->player.pos[Y], data->player.direct[X], data->player.direct[Y]);
	draw_pov_line(milx, MINI_MAP / 2, MINI_MAP / 2, data->player.direct[X], data->player.direct[Y], length, color);
}

void	step_direction(t_raycaster *ray)
{
	if (ray->direction[X] >= 0)
	{
		ray->step[X] = 1;
		ray->length[X] = (((float)ray->r_pos[X] + 1) - ray->r_start[X]) * ray->step_size;
	}
	if (ray->direction[X] < 0)
	{
		ray->step[X] = -1;
		ray->length[X] = (ray->r_start[X] - (float)ray->r_pos[X]) * ray->step_size;
	}
	if (ray->direction[Y] >= 0)
	{
		ray->step[Y] = 1;
		ray->length[Y] = (((float)ray->r_pos[Y] + 1) - ray->r_start[Y]) * ray->step_size;
	}
	if (ray->direction[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->length[Y] = (ray->r_start[Y] - (float)ray->r_pos[Y]) * ray->step_size;
	}
}


void	ray_caster(t_data *data, t_minilx *milx)
{
	t_raycaster	*ray;
	t_player	*player;
	int		x;
	float		plane_zone;
	int	cube_size;
	
	x = 0;
	cube_size = data->map.x_max * data->map.y_max;
	ft_bzero(&ray, sizeof(t_raycaster));
	ray = &data->ray;
	player = &data->player;
	data->player.plane[X] = 0.66; //solve this
	data->player.plane[Y] = 0; //solve this
	ray->r_start[X] = player->pos[X];
	ray->r_start[Y] = player->pos[Y];
	ray->r_pos[X] = ray->r_start[X];
	ray->r_pos[Y] = ray->r_start[X];
	while(x < milx->screen_width)
	{
		ray->wall_found = false;
		plane_zone = 2 * ((float)x / (float)milx->screen_width) - 1; // find a range in -1 and 1 of screenray
		ray->direction[X] = player->direct[X] + (player->plane[X] * plane_zone);
		ray->direction[Y] = player->direct[Y] + (player->plane[Y] * plane_zone);
		ray->step_size[X] = sqrt(1 + (ray->direction[Y] / ray->direction[X]) * (ray->direction[Y] / ray->direction[X])); // 1 = dx wich is set to 1, (dy/dx) squared
		ray->step_size[Y] = sqrt(1 + (ray->direction[X] / ray->direction[Y]) * (ray->direction[X] / ray->direction[Y])); // 1 = dy wich is set to 1, (dx/dy) squared
		step_direction(ray);
		while(!ray->wall_found)
		{
			if(ray->length[X] < ray->length[Y])
			{
				ray->r_pos[X] += ray->step[X];
				ray->final_distance = ray->length[X];
				ray->length[X] += ray->step_size[X];
			}
			else
			{
				ray->r_pos[Y] += ray->step[Y];
				ray->final_distance = ray->length[Y];
				ray->length[Y] += ray->step_size[Y];
			}
			// if (inbounds(ray->position[X], ray->position[Y], data->map))
			if (ray->r_pos[X] >= 0 && ray->r_pos[Y] >= 0 && ray->r_pos[X] < data->map.x_max && ray->r_pos[Y] < data->map.y_max)
			{
				if (data->map.map[(int)ray->r_pos[Y]][(int)ray->r_pos[X]] == '1')
					ray->wall_found = true;
			}
			// else 
			// {
			// 	ray->r_pos[X] -= 1;
			// 	ray->r_pos[Y] -= 1;
			// 	ray->wall_found = true;
			// }
		}
		ray->intersect[X] = player->pos[X] + ray->direction[X] * ray->final_distance;
		ray->intersect[Y] = player->pos[Y] + ray->direction[Y] * ray->final_distance;
		//printf("%f, %f\n", ray->direction[Y] / ray->final_distance, ray->final_distance);
		int	line_heigth = (cube_size * milx->screen_length) / ray->final_distance;
		if (line_heigth > milx->screen_length)
			line_heigth = milx->screen_length;
		draw_pov_line(milx, MINI_MAP / 2, MINI_MAP / 2, ray->direction[X], ray->direction[Y], (int)((ray->direction[Y] / ray->final_distance) * TILE_SIZE), create_trgb(0, 255, 0, 0));
		x++;
	}
}

void	draw_map(t_data *data, t_minilx *milx, int tile_size)
{
	int	map_x;
	int	map_y;
	int	x;
	int	y;

	map_x = data->player.pos[X] * tile_size - (MINI_MAP / 2);
	map_y = data->player.pos[Y] * tile_size - (MINI_MAP /2);
	y = 0;
	while (y < MINI_MAP)
	{
		x = 0;
		while (x < MINI_MAP)
		{
			if((float)(map_x + x)/tile_size >= 0 && (float)(map_y + y)/tile_size >= 0 && (map_x + x)/tile_size < data->map.x_max && (map_y + y)/tile_size < data->map.y_max)
			{
				if	(data->map.map[(map_y + y)/tile_size][(map_x + x)/tile_size] == '1')
					img_mlx_pixel_put(&(milx->mini[DRAW]), x, y, create_trgb(0, 0, 0, 0));
				else if (data->map.map[(map_y + y)/tile_size][(map_x + x)/tile_size] == '0')
					img_mlx_pixel_put(&(milx->mini[DRAW]), x, y, create_trgb(0, 255, 255, 255));
				else
					img_mlx_pixel_put(&(milx->mini[DRAW]), x, y, create_trgb(0, 0, 0, 0));
				
			}
			x++;
		}
		y++;
	}
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

int	is_wall(t_data *data, float x, float y)
{
	int map_x;
	int map_y;
	
	map_x = x; //round(x);
	map_y = y; // round(y); 
	if (x > data->map.x_max || x < 1 || y < 1 || y > data->map.y_max) // Map brounds check, includeing x=1, y=1, x=max or y=max as they have to be walls
		return (1);
	if (data->map.map[map_y][map_x] == '1' || data->map.map[map_y][map_x] == ' ')
		return (1);
	return (0);
}

int	draw_minimap(void *param)
{
	t_data		*data;
	t_minilx	*milx;

	data = (t_data *) param;
	milx = &data->milx;
	draw_clear(milx);
	draw_border(milx, create_trgb(0, 55, 55, 55), 4);
	draw_map(data, milx, TILE_SIZE);
	draw_player(milx, create_trgb(0, 20, 80, 200), 10);
	ray_caster(data, milx);
	// draw_pov(data, milx, create_trgb(0, 255, 0, 255), 40);
	draw_minimap_switch_display(data);
	return (0);
}

// WSL: W 119, A 97, S 115, D 100
// MAC: W 13, A 0, S 1, D 2, ESC 53
int	key_hook_wasd(int keycode, void *param)
{
	t_data	*data;
	float	new_x;
	float	new_y;

	data = (t_data *)param;
	// mlx_do_key_autorepeaton(&(data->milx));
	printf("KEY:%d ", keycode);
	if (keycode == 119 || keycode == 13)
	{
		new_x = data->player.pos[X] + (data->player.direct[X] * STEP_SIZE);
		new_y = data->player.pos[Y] + (data->player.direct[Y] * STEP_SIZE);
		if (!is_wall(data, new_x, new_y))
		{
			data->player.pos[X] = new_x;
			data->player.pos[Y] = new_y;
		}
	}
	else if (keycode == 115 || keycode == 1)
	{
		new_x = data->player.pos[X] - (data->player.direct[X] * STEP_SIZE);
		new_y = data->player.pos[Y] - (data->player.direct[Y] * STEP_SIZE);
		if (!is_wall(data, new_x, new_y))
		{
			data->player.pos[X] = new_x;
			data->player.pos[Y] = new_y;
		}
	}
	else if (keycode == 97 || keycode == 0)
	{
		data->player.direct[X] = data->player.direct[X] * cos(-0.1) - data->player.direct[Y] * sin(-0.1);
		data->player.direct[Y] = data->player.direct[X] * sin(-0.1) + data->player.direct[Y] * cos(-0.1);
		data->player.direct[X] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
		data->player.direct[Y] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
	}
	else if (keycode == 100 || keycode == 2)
	{
		data->player.direct[X] = data->player.direct[X] * cos(0.1) - data->player.direct[Y] * sin(0.1);
		data->player.direct[Y] = data->player.direct[X] * sin(0.1) + data->player.direct[Y] * cos(0.1);
		data->player.direct[X] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
		data->player.direct[Y] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
	}
	else if (keycode == 53) // ESC quit for mac
		mlx_finish(&(data->milx));
	printf("\tPOS: %f %f\tVIEW: %f %f\n", data->player.pos[X], data->player.pos[Y], data->player.direct[X], data->player.direct[Y]);
	// mlx_do_key_autorepeatoff(&(data->milx));
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
	// mlx_get_screen_size(data.milx.mlx, &data.milx.screen_length, &data.milx.screen_width);
	data.milx.screen_length = 800;
	data.milx.screen_width = 1200;
	data.milx.mlx_window = mlx_new_window(data.milx.mlx, data.milx.screen_width, data.milx.screen_length, "CUBE3D");
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

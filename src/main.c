/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:49:00 by crasche           #+#    #+#             */
/*   Updated: 2024/09/17 19:32:07 by andmadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void draw_pov_line(t_minilx_img *img, int x0, int y0, float vx, float vy, int length, int color)
{
	float	magnitude;
	float	x;
	float	y;
	int		i;

	magnitude = sqrt(vx * vx + vy * vy);
	vx /= magnitude;
	vy /= magnitude;
	x = x0;
	y = y0;
	i = 0;
	while (i < length)
	{
		img_mlx_pixel_put(img, (int)round(x), (int)round(y), color);
		x += vx;
		y += vy;
		i++;
	}
}

void	step_direction(t_raycaster *ray)
{
	if (ray->direction[X] >= 0)
	{
		ray->step[X] = 1;
		ray->length[X] = (((float)ray->r_pos[X] + 1) - ray->r_start[X]) * ray->step_size[X];
	}
	else if (ray->direction[X] < 0)
	{
		ray->step[X] = -1;
		ray->length[X] = (ray->r_start[X] - (float)ray->r_pos[X]) * ray->step_size[X];
	}
	if (ray->direction[Y] >= 0)
	{
		ray->step[Y] = 1;
		ray->length[Y] = (((float)ray->r_pos[Y] + 1) - ray->r_start[Y]) * ray->step_size[Y];
	}
	else if (ray->direction[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->length[Y] = (ray->r_start[Y] - (float)ray->r_pos[Y]) * ray->step_size[Y];
	}
}

//vertical line draw 
void	draw_line(t_minilx *milx, int x, int start_y, int line_heigth, int color)
{
	int	y;

	y = 0;
	while(y < line_heigth)
	{
			img_mlx_pixel_put(&milx->big[DRAW], x, start_y + y, color);
		y++;
	}
}

int	shadowing_cube(t_raycaster ray)
{
	if (ray.length[X] < ray.length[Y])
		return (create_trgb(0, 222, 30, 0)); //x
	return (create_trgb(0, 141, 19, 0)); //y
}

void	draw_texture_line(t_data *data, int x, int texture, float line_height)
{
	unsigned int		wall_color;
	int	start_y =  data->milx.screen_y / 2 - round(line_height / 2);
	int line_pos = 0;

	wall_color = 0;
	if (texture == NORTH)
	{
		while (line_pos < line_height)
		{
			img_get_pixel_color(&data->map.img_n, (int)(data->map.img_n.max_x * data->ray.texture_perc), (int)(data->map.img_n.max_y * ((float)line_pos / line_height)), &wall_color);
			// printf("x_max:%d * perc:%f X:%d color:%u\n", (int)data->map.img_n.max_x, data->ray.texture_perc, (int)(data->map.img_n.max_x * data->ray.texture_perc), wall_color);
			// printf("Y_max:%d * (pos:%d / screenY:%d) Y:%d color:%u\n", (int)data->map.img_n.max_y, start_y + line_pos, data->milx.screen_y, (int)(data->map.img_n.max_y * ((float)(start_y + line_pos) / data->milx.screen_y)), wall_color);
			// printf("Y:%d color:%u\n", (int)(data->map.img_n.max_y * ((float)(start_y + line_pos) / data->milx.screen_y)), wall_color);
			img_mlx_pixel_put(&data->milx.big[DRAW], x, start_y + line_pos, wall_color);
			line_pos++;
		}
	}
	else if (texture == EAST)
	{
		while (line_pos < line_height)
		{
			img_get_pixel_color(&data->map.img_e, data->map.img_e.max_x * data->ray.texture_perc, (int)(data->map.img_e.max_y * (float)line_pos / (float)line_height), &wall_color);
			// printf("color:%u\n", wall_color);
			img_mlx_pixel_put(&data->milx.big[DRAW], x, start_y + line_pos, wall_color);
			line_pos++;
		}
	}
	else if (texture == SOUTH)
	{
		while (line_pos < line_height)
		{
			img_get_pixel_color(&data->map.img_s, data->map.img_s.max_x * data->ray.texture_perc,  (int)(data->map.img_s.max_y * (float)line_pos / (float)line_height), &wall_color);
			// printf("color:%u\n", wall_color);
			img_mlx_pixel_put(&data->milx.big[DRAW], x, start_y + line_pos, wall_color);
			line_pos++;
		}
	}
	else if (texture == WEST)
	{
		while (line_pos < line_height)
		{
			img_get_pixel_color(&data->map.img_w, data->map.img_w.max_x * data->ray.texture_perc,  (int)(data->map.img_w.max_y * (float)line_pos / (float)line_height), &wall_color);
			// printf("color:%u\n", wall_color);
			img_mlx_pixel_put(&data->milx.big[DRAW], x, start_y + line_pos, wall_color);
			line_pos++;
		}
	}
}

void	draw_texture(t_data *data, int x, float line_height)
{
	if(data->ray.wall_direction == TB)
	{
		data->ray.texture_perc = (data->ray.intersect[X] - (int)data->ray.intersect[X]);
		if (data->ray.intersect[Y] > data->player.pos[Y])
		{
			// printf("S, interX:%f,interY:%f, pos:%f || %f\n", data->ray.intersect[X], data->ray.intersect[Y], data->player.pos[Y], data->ray.texture_perc);
			draw_texture_line(data, x, SOUTH, line_height);
		}
		else
		{
			// data->ray.texture_perc = (data->ray.intersect[X] - (int)data->ray.intersect[X]);
			// printf("N, interX:%f,interY:%f, pos:%f || %f\n", data->ray.intersect[X], data->ray.intersect[Y], data->player.pos[Y], data->ray.texture_perc);
			draw_texture_line(data, x, NORTH, line_height);
		}
	}
	else if (data->ray.wall_direction == LR)
	{
		data->ray.texture_perc = (data->ray.intersect[Y] - (int)data->ray.intersect[Y]);
		if (data->ray.intersect[X] > data->player.pos[X])
		{
			// printf("E, interX:%f,interY:%f, pos:%f || %f\n", data->ray.intersect[X], data->ray.intersect[Y], data->player.pos[X], data->ray.texture_perc);
			draw_texture_line(data, x, EAST, line_height);
		}
		else
		{
			// data->ray.texture_perc = (data->ray.intersect[Y] - (int)data->ray.intersect[Y]);
			// printf("E, interX:%f,interY:%f, pos:%f || %f\n", data->ray.intersect[X], data->ray.intersect[Y], data->player.pos[X], data->ray.texture_perc);
			draw_texture_line(data, x, WEST, line_height);
		}
	}

}

void	ray_caster(t_data *data, t_minilx *milx)
{
	t_raycaster	ray;
	t_player	player;
	int			x;
	long double		plane_scale;
	float		plane_magnitude;
	// int			wall_color;
	
	x = 0;
	ft_bzero(&ray, sizeof(t_raycaster));
	player = data->player;
	player.plane[X] = -player.direct[Y];
	player.plane[Y] = player.direct[X];
	ray.r_start[X] = player.pos[X];
	ray.r_start[Y] = player.pos[Y];

	// x = milx->screen_x / 2; // one line
	// while(x == (milx->screen_x / 2)) //  
	while(x < milx->screen_x) //  x < milx->screen_x
	{
		ray.r_pos[X] = ray.r_start[X];
		ray.r_pos[Y] = ray.r_start[Y];
		ray.wall_found = false;
		// plane_scale = (float)2 * ((float)x / (float)milx->screen_x) - (float)1;
		plane_scale = (float)2 * ((float)x / (float)milx->screen_x) - (float)1;
		plane_magnitude = tan((float)(FOV / 2) * (float)(M_PI / 180));
		ray.direction[X] = player.direct[X] + (player.plane[X] * plane_magnitude) * plane_scale;
		ray.direction[Y] = player.direct[Y] + (player.plane[Y] * plane_magnitude) * plane_scale;
		ray.step_size[X] = sqrt(1 + (ray.direction[Y] / ray.direction[X]) * (ray.direction[Y] / ray.direction[X]));
		ray.step_size[Y] = sqrt(1 + (ray.direction[X] / ray.direction[Y]) * (ray.direction[X] / ray.direction[Y]));
		step_direction(&ray);
		while(!ray.wall_found)
		{
			if(ray.length[X] < ray.length[Y])
			{
				ray.r_pos[X] += ray.step[X];
				ray.final_distance = ray.length[X];
				ray.length[X] += ray.step_size[X];
				ray.wall_direction = LR;
			}
			else
			{
				ray.r_pos[Y] += ray.step[Y];
				ray.final_distance = ray.length[Y];
				ray.length[Y] += ray.step_size[Y];
				ray.wall_direction = TB;
				
			}
			// if (ray.r_pos[X] >= 0 && ray.r_pos[Y] >= 0 && ray.r_pos[X] < data->map.x_max && ray.r_pos[Y] < data->map.y_max)
			// {
			if (data->map.map[ray.r_pos[Y]][ray.r_pos[X]] == '1')
			{
				ray.wall_found = true;
			}
			// }
			// else 
			// {
			// 	ray.wall_found = true;
			// 	if (ray.r_pos[X] >= 0)
			// 		ray.r_pos[X] = 0;
			// 	if (ray.r_pos[Y] >= 0)
			// 		ray.r_pos[Y] = 0;
			// 	if (ray.r_pos[X] < data->map.x_max)
			// 		ray.r_pos[X] = data->map.x_max;
			// 	if (ray.r_pos[Y] < data->map.y_max)
			// 		ray.r_pos[Y] = data->map.y_max;
			// }
		}
		// float	line_heigth = milx->screen_y / ray.final_distance;
		float	line_heigth = (float)milx->screen_y / (float)(ray.final_distance * cos((float)(M_PI/180) * (float)(FOV/2)));//* cos(M_PI/180 * FOV/2 * plane_scale));
		// if (line_heigth > milx->screen_y)
		// 	line_heigth = milx->screen_y;
		// int	start_y =  milx->screen_y / 2 - line_heigth / 2;
		ray.intersect[X] = ray.direction[X] * ray.final_distance + ray.r_start[X];
		ray.intersect[Y] = ray.direction[Y] * ray.final_distance + ray.r_start[Y];
		data->ray = ray;
		if (x % 120 == 1)
			draw_pov_line(&milx->mini[DRAW], MINI_MAP / 2, MINI_MAP / 2, ray.direction[X], ray.direction[Y], ray.final_distance * TILE_SIZE, create_trgb(0, 255, 0, 0));
		draw_line(milx, x, 0, (milx->screen_y - line_heigth) / 2, create_trgb(2, 220, 100, 0)); //sky
		// draw_line(milx, x, start_y, line_heigth, wall_color); //walls
		draw_line(milx, x, milx->screen_y / 2 + line_heigth / 2, (milx->screen_y - line_heigth) / 2, create_trgb(2, 0, 102, 102)); //floor
		draw_texture(data, x, line_heigth);
		// get_intersect(ray, x, ray.direction[X] * ray.final_distance + ray.r_start[X], ray.direction[Y] * ray.final_distance + ray.r_start[Y]);
		x++;
	}
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
	map_print(&data, &data.map); //I do not like the name
	data.milx.mlx = mlx_init();
	if (!data.milx.mlx)
		return (free_all(&data), EXIT_FAILURE); //maybe do it somewhere else or free something
	mlx_get_screen_size(data.milx.mlx, &data.milx.screen_x, &data.milx.screen_y);
	// data.milx.screen_x = 800;
	// data.milx.screen_y = 620;
	data.milx.mlx_window = mlx_new_window(data.milx.mlx, data.milx.screen_x, data.milx.screen_y, "CUBE3D");
	if (!data.milx.mlx_window)
		return (free(data.milx.mlx), free_all(&data), EXIT_FAILURE);
	init_image(&data);
	hooks_mlx(&data);
	mlx_loop(data.milx.mlx);
	free_all(&data); //it should go here?/
	return (0);
}

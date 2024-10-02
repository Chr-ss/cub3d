/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/10/02 22:39:45 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	draw_texture_north(t_data *data)
{
	int	start_y;
	int line_pos;
	int	color_x;
	int	color_y;

	start_y =  data->milx.screen_y / 2 - round(data->ray.line_height / 2);
	line_pos = 0;
	if (start_y < 0)
		line_pos = -start_y;
	color_x = data->map.img_n.max_x * data->ray.texture_perc;
	while (line_pos < data->ray.line_height && (start_y + line_pos) < data->milx.screen_y)
	{
		if (color_y != round(data->map.img_n.max_y * ((float)line_pos / (float)data->ray.line_height)))
		{
			color_y = round(data->map.img_n.max_y * ((float)line_pos / (float)data->ray.line_height));
			data->ray.wall_color = img_get_pixel_color(&data->map.img_n, color_x, color_y);
		}
		img_mlx_pixel_put(&data->milx.big, data->ray.x, start_y + line_pos, data->ray.wall_color);
		line_pos++;
	}
}

static void	draw_texture_east(t_data *data)
{
	int	start_y;
	int line_pos;
	int	color_x;
	int	color_y;

	start_y =  data->milx.screen_y / 2 - round(data->ray.line_height / 2);
	line_pos = 0;
	if (start_y < 0)
		line_pos = -start_y;
	color_x = data->map.img_e.max_x * data->ray.texture_perc;
	while (line_pos < data->ray.line_height && (start_y + line_pos) < data->milx.screen_y)
	{
		if (color_y != round((data->map.img_e.max_y * (float)line_pos / (float)data->ray.line_height)))
		{
			color_y = round((data->map.img_e.max_y * (float)line_pos / (float)data->ray.line_height));
			data->ray.wall_color = img_get_pixel_color(&data->map.img_e, color_x, color_y);
		}
		img_mlx_pixel_put(&data->milx.big, data->ray.x, start_y + line_pos, data->ray.wall_color);
		line_pos++;
	}
}

static void	draw_texture_south(t_data *data)
{
	int	start_y;
	int line_pos;
	int	color_x;
	int	color_y;

	start_y =  data->milx.screen_y / 2 - round(data->ray.line_height / 2);
	line_pos = 0;
	if (start_y < 0)
		line_pos = -start_y;
	color_x = data->map.img_s.max_x * data->ray.texture_perc;
	while (line_pos < data->ray.line_height && (start_y + line_pos) < data->milx.screen_y)
	{
		if (color_y != round((data->map.img_s.max_y * (float)line_pos / (float)data->ray.line_height)))
		{
			color_y = round((data->map.img_s.max_y * (float)line_pos / (float)data->ray.line_height));
			data->ray.wall_color = img_get_pixel_color(&data->map.img_s, color_x, color_y);
		}
		img_mlx_pixel_put(&data->milx.big, data->ray.x, start_y + line_pos, data->ray.wall_color);
		line_pos++;
	}
}

static void	draw_texture_west(t_data *data)
{
	int	start_y;
	int line_pos;
	int	color_x;
	int	color_y;

	start_y =  data->milx.screen_y / 2 - round(data->ray.line_height / 2);
	line_pos = 0;
	if (start_y < 0)
		line_pos = -start_y;
	color_x = data->map.img_w.max_x * data->ray.texture_perc;
	while (line_pos < data->ray.line_height && (start_y + line_pos) < data->milx.screen_y)
	{
		if (color_y != round((data->map.img_w.max_y * (float)line_pos / (float)data->ray.line_height)))
		{
			color_y = round((data->map.img_w.max_y * (float)line_pos / (float)data->ray.line_height));
			data->ray.wall_color = img_get_pixel_color(&data->map.img_w, color_x, color_y);
		}
		img_mlx_pixel_put(&data->milx.big, data->ray.x, start_y + line_pos, data->ray.wall_color);
		line_pos++;
	}
}

void	draw_texture(t_data *data)
{
	if(data->ray.wall_direction == TB)
	{
		data->ray.texture_perc = (data->ray.intersect[X] - (int)data->ray.intersect[X]);
		if (data->ray.intersect[Y] > data->player.pos[Y])
			draw_texture_north(data);
		else
			draw_texture_south(data);
	}
	else if (data->ray.wall_direction == LR)
	{
		data->ray.texture_perc = (data->ray.intersect[Y] - (int)data->ray.intersect[Y]);
		if (data->ray.intersect[X] > data->player.pos[X])
			draw_texture_west(data);
		else
			draw_texture_east(data);
	}
}

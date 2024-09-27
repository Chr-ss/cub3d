/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:44:17 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"


void	draw_texture_north(t_data *data)
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
		if (color_y != round(data->map.img_n.max_y * (float)line_pos / (float)data->ray.line_height))
		{
			color_y = round(data->map.img_n.max_y * (float)line_pos / (float)data->ray.line_height);
			data->ray.wall_color = img_get_pixel_color(&data->map.img_n, color_x, color_y);
		}
		img_mlx_pixel_put(&data->milx.big[DRAW], data->ray.x, start_y + line_pos, data->ray.wall_color);
		line_pos++;
	}
	// printf("%d \t %d \t %d \t %d \t %d\n", line_pos, start_y, data->milx.screen_y, (start_y + line_pos), (start_y + line_pos) < data->milx.screen_y);
}


// void	draw_texture_line(t_data *data, int texture)
// {
// 	int	start_y =  data->milx.screen_y / 2 - round(data->ray.line_height / 2);
// 	int line_pos = 0;

// 	if (texture == NORTH)
// 	{
// 		while (line_pos < data->ray.line_height)
// 		{
// 			data->ray.wall_color = img_get_pixel_color(&data->map.img_n, (int)(data->map.img_n.max_x * data->ray.texture_perc), (int)(data->map.img_n.max_y * ((float)line_pos / data->ray.line_height)));
// 			// printf("x_max:%d * perc:%f X:%d color:%u\n", (int)data->map.img_n.max_x, data->ray.texture_perc, (int)(data->map.img_n.max_x * data->ray.texture_perc), wall_color);
// 			// printf("Y_max:%d * (pos:%d / screenY:%d) Y:%d color:%u\n", (int)data->map.img_n.max_y, start_y + line_pos, data->milx.screen_y, (int)(data->map.img_n.max_y * ((float)(start_y + line_pos) / data->milx.screen_y)), wall_color);
// 			// printf("Y:%d color:%u\n", (int)(data->map.img_n.max_y * ((float)(start_y + line_pos) / data->milx.screen_y)), wall_color);
// 			img_mlx_pixel_put(&data->milx.big[DRAW], data->ray.x, start_y + line_pos, data->ray.wall_color);
// 			line_pos++;
// 		}
// 	}
// 	else if (texture == EAST)
// 	{
// 		while (line_pos < data->ray.line_height)
// 		{
// 			data->ray.wall_color = img_get_pixel_color(&data->map.img_e, data->map.img_e.max_x * data->ray.texture_perc, (int)(data->map.img_e.max_y * (float)line_pos / (float)data->ray.line_height));
// 			// printf("color:%u\n", data->ray.wall_color);
// 			img_mlx_pixel_put(&data->milx.big[DRAW], data->ray.x, start_y + line_pos, data->ray.wall_color);
// 			line_pos++;
// 		}
// 	}
// 	else if (texture == SOUTH)
// 	{
// 		while (line_pos < data->ray.line_height)
// 		{
// 			data->ray.wall_color = img_get_pixel_color(&data->map.img_s, data->map.img_s.max_x * data->ray.texture_perc,  (int)(data->map.img_s.max_y * (float)line_pos / (float)data->ray.line_height));
// 			// printf("color:%u\n", data->ray.wall_color);
// 			img_mlx_pixel_put(&data->milx.big[DRAW], data->ray.x, start_y + line_pos, data->ray.wall_color);
// 			line_pos++;
// 		}
// 	}
// 	else if (texture == WEST)
// 	{
// 		while (line_pos < data->ray.line_height)
// 		{
// 			data->ray.wall_color = img_get_pixel_color(&data->map.img_w, data->map.img_w.max_x * data->ray.texture_perc,  (int)(data->map.img_w.max_y * (float)line_pos / (float)data->ray.line_height));
// 			// printf("color:%u\n", data->ray.wall_color);
// 			img_mlx_pixel_put(&data->milx.big[DRAW], data->ray.x, start_y + line_pos, data->ray.wall_color);
// 			line_pos++;
// 		}
// 	}
// }

void	draw_texture(t_data *data)
{
	if(data->ray.wall_direction == TB)
	{
		data->ray.texture_perc = (data->ray.intersect[X] - (int)data->ray.intersect[X]);
		if (data->ray.intersect[Y] > data->player.pos[Y])
			draw_texture_north(data);
		else
			draw_texture_north(data);
	}
	else if (data->ray.wall_direction == LR)
	{
		data->ray.texture_perc = (data->ray.intersect[Y] - (int)data->ray.intersect[Y]);
		if (data->ray.intersect[X] > data->player.pos[X])
			draw_texture_north(data);
		else
			draw_texture_north(data);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/10/03 16:44:31 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	repalce_texture_color(t_raycaster *ray, int x, int y, float prec)
{
	if (y != (int)(ray->img->max_y * prec))
	{
		y = (int)ray->img->max_y * prec;
		ray->wall_color = img_get_pixel_color(ray->img, x, y);
		return (y);
	}
	return (y);
}

static void	draw_texture_lines(t_data *data, int s_y)
{
	int	line_pos;
	int	c_x;
	int	c_y;
	t_raycaster ray;

	ray = data->ray;
	line_pos = 0;
	if (s_y < 0)
		line_pos = -s_y;
	c_x = data->map.img_n.max_x * ray.texture_perc;
	while (line_pos < ray.line_height && (s_y + line_pos) < data->milx.screen_y)
	{
		// if (c_y != (int)(data->map.img_e.max_y * (float)line_pos / (float)ray.line_height))
		// {
		// 	c_y = (int)data->map.img_n.max_y * ((float)line_pos / (float)ray.line_height);
		// 	ray.wall_color = img_get_pixel_color(&data->map.img_n, c_x, c_y);
		// }
		c_y = repalce_texture_color(&ray, c_x, c_y, (float)line_pos / (float)ray.line_height);
		if (CRAZY)
			ray.wall_color = color_fraction(ray.wall_color, WHITE, fmax(ray.final_distance, 1.1));
		if (BONUS)
			img_mlx_pixel_put(&data->milx.big, ray.x, s_y + line_pos, \
			color_fraction(ray.wall_color, WHITE, fmin(ray.final_distance / 6, 1.0)));
		else
			img_mlx_pixel_put(&data->milx.big, ray.x, s_y + line_pos, ray.wall_color);
		line_pos++;
	}
}

void	draw_texture(t_data *data)
{	
	t_raycaster	*ray;

	ray = &data->ray;
	if (ray->wall_direction == TB)
	{
		ray->texture_perc = (ray->intersect[X] - (int)ray->intersect[X]);
		if (ray->intersect[Y] > data->player.pos[Y])
			ray->img = &data->map.img_s;
		else
			ray->img = &data->map.img_n;
	}
	else if (ray->wall_direction == LR)
	{
		ray->texture_perc = (ray->intersect[Y] - (int)ray->intersect[Y]);
		if (ray->intersect[X] > data->player.pos[X])
			ray->img = &data->map.img_w;
		else
			ray->img = &data->map.img_e;
	}
	draw_texture_lines(data, data->milx.screen_y / 2 - round(ray->line_height / 2));
}

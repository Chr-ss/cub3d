/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:38:21 by crasche           #+#    #+#             */
/*   Updated: 2024/09/17 19:32:20 by andmadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void draw_fov_lines(t_minilx_img *img, int x0, int y0, float vx, float vy)
{
	float	magnitude;
	float	x;
	float	y;
	int		i;
	unsigned int	get_color;

	magnitude = sqrt(vx * vx + vy * vy);
	vx /= magnitude;
	vy /= magnitude;
	x = x0;
	y = y0;
	i = 0;
	get_color = 0;
	while (i < VIEW_DISTANCE)
	{
		img_get_pixel_color(img, (int)round(x), (int)round(y), &get_color);
		if (get_color == MINI_MAP_WALL_COLOR)
			return ;
		img_mlx_pixel_put(img, (int)round(x), (int)round(y), MINI_MAP_VIEW_COLOR);
		x += vx;
		y += vy;
		i++;
	}
}

void	draw_minimap_view(t_data *data, t_minilx *milx)
{
	int	i;
	float	vx;
	float	vy;
	
	i = -(FOV / 2);
	while (i < (FOV / 2))
	{
		vx = data->player.direct[X] * cos(i * M_PI / 180) - data->player.direct[Y] * sin(i * M_PI / 180);
		vy = data->player.direct[X] * sin(i * M_PI / 180) + data->player.direct[Y] * cos(i * M_PI / 180);
		draw_fov_lines(&milx->mini[DRAW], MINI_MAP / 2, MINI_MAP / 2, vx, vy);
		i++;
	}
}

int	draw_minimap_switch_img(void *param)
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
	draw_minimap_clear(milx);
	draw_minimap_tiles(data, milx, TILE_SIZE);
	draw_minimap_player(milx, create_trgb(0, 20, 80, 200), 10);
	draw_minimap_border(milx, create_trgb(0, 55, 55, 55), MINI_MAP_BORDER);
	draw_minimap_view(data, milx);
	draw_minimap_switch_img(data);
	return (0);
}

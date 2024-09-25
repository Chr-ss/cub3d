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
	draw_minimap_switch_img(data);
	return (0);
}

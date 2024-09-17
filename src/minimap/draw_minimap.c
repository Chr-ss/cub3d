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

// remove when not needed:
void	ray_caster(t_data *data, t_minilx *milx);
void	draw_map_floor_ciling(t_minilx *milx);

int	draw_minimap_switch_img(void *param)
{
	t_minilx_img	buffer_1;
	t_minilx_img	buffer_2;
	t_data			*data;

	data = (t_data *) param;
	buffer_1 = data->milx.mini[DRAW];
	buffer_2 = data->milx.big[DRAW];
	data->milx.mini[DRAW] = data->milx.mini[DISPLAY];
	data->milx.big[DRAW] = data->milx.big[DISPLAY];
	data->milx.mini[DISPLAY] = buffer_1;
	data->milx.big[DISPLAY] = buffer_2;
	mlx_put_image_to_window(data->milx.mlx, data->milx.mlx_window, data->milx.big[DISPLAY].img, 0, 0);
	mlx_put_image_to_window(data->milx.mlx, data->milx.mlx_window, data->milx.mini[DISPLAY].img, 0, 0);
	return (0);
}

int	draw_minimap(void *param)
{
	t_data		*data;
	t_minilx	*milx;
	static int			i;

	i = 0;
	data = (t_data *) param;
	milx = &data->milx;
	draw_minimap_clear(milx);
	draw_minimap_tiles(data, milx, TILE_SIZE);
	draw_minimap_player(milx, create_trgb(0, 20, 80, 200), 10);
	ray_caster(data, milx);
	draw_minimap_border(milx, create_trgb(0, 55, 55, 55), 4);
	draw_minimap_switch_img(data);
	return (0);
}
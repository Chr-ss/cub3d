/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_tiles.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:44:17 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	draw_minimap_tiles(t_data *data, t_minilx *milx, int tile_size)
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
					img_mlx_pixel_put(&(milx->mini[DRAW]), x, y, MINI_MAP_WALL_COLOR);
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
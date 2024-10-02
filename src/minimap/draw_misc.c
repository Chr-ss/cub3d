/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_misc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:44:17 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	draw_minimap_player_line(t_minilx *milx, int x_start, int x_end, int y, int color)
{
	while (x_start <= x_end)
	{
		img_mlx_pixel_put(&milx->mini, x_start, y, color);
		x_start++;
	}
}

void	draw_minimap_player(t_minilx *milx, int color, int radius)
{
	int	center;
	int y;
	int decision;

	center = MINI_MAP / 2;
	decision = 1 - radius;
	y = 0;
	while (y <= radius)
	{
		draw_minimap_player_line(milx, center - radius, center + radius, center + y, color);
		draw_minimap_player_line(milx, center - radius, center + radius, center - y, color);
		draw_minimap_player_line(milx, center - y, center + y, center + radius, color);
		draw_minimap_player_line(milx, center - y, center + y, center - radius, color);
		y++;
		if (decision <= 0)
			decision += 2 * y + 1;
		else
			decision += 2 * (y - radius--) + 1;
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: andmadri <andmadri@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/10/02 20:33:32 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void draw_fov_lines(t_mlx_img *img, float vx, float vy)
{
	float	magnitude;
	float	x;
	float	y;
	int		i;

	magnitude = sqrt(vx * vx + vy * vy);
	vx /= magnitude;
	vy /= magnitude;
	x = MINI_MAP / 2;
	y = MINI_MAP / 2;
	i = 0;
	while (i < VIEW_DISTANCE)
	{
		if (img_get_pixel_color(img, (int)x, (int)y) == MM_WALL_COLOR)
			return ;
		img_mlx_pixel_put(img, (int)x, (int)y, color_fraction(MM_VIEW_COLOR, \
			create_trgb(0, 255, 255, 255), ((float)i / (float)VIEW_DISTANCE)));
		x += vx;
		y += vy;
		i++;
	}
}

void	draw_minimap_view(t_data *data, t_minilx *milx)
{
	t_player	player;
	float		vx;
	float		vy;
	int			i;

	i = -(FOV / 2);
	player = data->player;
	while (i < (FOV / 2))
	{
		vx = player.direct[X] * cos(i * RAD) - player.direct[Y] * sin(i * RAD);
		vy = player.direct[X] * sin(i * RAD) + player.direct[Y] * cos(i * RAD);
		draw_fov_lines(&milx->mini, vx, vy);
		i++;
	}
}

int	draw_minimap(void *param)
{
	t_data		*data;
	t_minilx	*milx;

	data = (t_data *) param;
	milx = &data->milx;
	draw_minimap_clear(milx);
	draw_minimap_tiles(data);
	draw_minimap_view(data, milx);
	draw_minimap_player(milx, MM_PLAYER_COLOR, MM_PLAYER_SIZE);
	draw_minimap_border(milx, MM_BORDER_COLOR, MM_BORDER_SIZE);
	return (0);
}

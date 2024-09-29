/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:44:17 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	img_mlx_pixel_put(t_minilx_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < img->max_x && y < img->max_y)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

unsigned int	img_get_pixel_color(t_minilx_img *img, int x, int y)
{
	if (x >= 0 && y >= 0 && x < img->max_x && y < img->max_y)
		return (*(unsigned int*)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8))));
	return (0);
}

uint32_t	color_fraction(uint32_t c1, uint32_t c2, float fraction)
{
	int	r;
	int	g;
	int	b;

	r = (int)((c1 >> 16) & 0xFF) + (((int)((c2 >> 16) & 0xFF) \
	- (int)((c1 >> 16) & 0xFF)) * fraction);
	g = (int)((c1 >> 8) & 0xFF) + (((int)((c2 >> 8) & 0xFF) \
	- (int)((c1 >> 8) & 0xFF)) * fraction);
	b = (int)((c1) & 0xFF) + (((int)((c2) & 0xFF) \
	- (int)((c1) & 0xFF)) * fraction);
	return (create_trgb(0, r, g, b));
}
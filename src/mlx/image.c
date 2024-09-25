/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:44:17 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_image_set_size(t_minilx_img *img, int max_x, int max_y)
{
	img->max_x = max_x;
	img->max_y = max_y;
}

void	init_image_define_size(t_data *data)
{
	init_image_set_size(&data->milx.big[0], data->milx.screen_x, data->milx.screen_y);
	init_image_set_size(&data->milx.big[1], data->milx.screen_x, data->milx.screen_y);
	init_image_set_size(&data->milx.mini[0], MINI_MAP + MINI_MAP_BORDER, MINI_MAP + MINI_MAP_BORDER);
	init_image_set_size(&data->milx.mini[1], MINI_MAP + MINI_MAP_BORDER, MINI_MAP + MINI_MAP_BORDER);

}

void	init_image(t_data *data)
{
	data->milx.mini[0].img = mlx_new_image(data->milx.mlx, MINI_MAP + MINI_MAP_BORDER, MINI_MAP + MINI_MAP_BORDER);
	data->milx.mini[1].img = mlx_new_image(data->milx.mlx, MINI_MAP + MINI_MAP_BORDER, MINI_MAP + MINI_MAP_BORDER);
	data->milx.mini[0].addr = mlx_get_data_addr(data->milx.mini[0].img, &data->milx.mini[0].bits_per_pixel, &data->milx.mini[0].line_length, &data->milx.mini[0].endian);
	data->milx.mini[1].addr = mlx_get_data_addr(data->milx.mini[1].img, &data->milx.mini[1].bits_per_pixel, &data->milx.mini[1].line_length, &data->milx.mini[1].endian);
	data->milx.big[0].img = mlx_new_image(data->milx.mlx, data->milx.screen_x, data->milx.screen_y);
	data->milx.big[1].img = mlx_new_image(data->milx.mlx, data->milx.screen_x, data->milx.screen_y);
	data->milx.big[0].addr = mlx_get_data_addr(data->milx.big[0].img, &data->milx.big[0].bits_per_pixel, &data->milx.big[0].line_length, &data->milx.big[0].endian);
	data->milx.big[1].addr = mlx_get_data_addr(data->milx.big[1].img, &data->milx.big[1].bits_per_pixel, &data->milx.big[1].line_length, &data->milx.big[1].endian);
	init_image_define_size(data);
	data->map.img_n.img = mlx_png_file_to_image(data->milx.mlx, data->map.n_tex, &data->map.img_n.max_x, &data->map.img_n.max_y);
	data->map.img_n.addr = mlx_get_data_addr(data->map.img_n.img, &data->map.img_n.bits_per_pixel, &data->map.img_n.line_length, &data->map.img_n.endian);
	data->map.img_e.img = mlx_png_file_to_image(data->milx.mlx, data->map.e_tex, &data->map.img_e.max_x, &data->map.img_e.max_y);
	data->map.img_e.addr = mlx_get_data_addr(data->map.img_e.img, &data->map.img_e.bits_per_pixel, &data->map.img_e.line_length, &data->map.img_e.endian);
	data->map.img_s.img = mlx_png_file_to_image(data->milx.mlx, data->map.s_tex, &data->map.img_s.max_x, &data->map.img_s.max_y);
	data->map.img_s.addr = mlx_get_data_addr(data->map.img_s.img, &data->map.img_s.bits_per_pixel, &data->map.img_s.line_length, &data->map.img_s.endian);
	data->map.img_w.img = mlx_png_file_to_image(data->milx.mlx, data->map.w_tex, &data->map.img_w.max_x, &data->map.img_w.max_y);
	data->map.img_w.addr = mlx_get_data_addr(data->map.img_w.img, &data->map.img_w.bits_per_pixel, &data->map.img_w.line_length, &data->map.img_w.endian);
	printf("north_mx:%d, north_my:%d\n", data->map.img_n.max_x, data->map.img_n.max_y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/10/02 22:07:17 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	init_image_set_size(t_mlx_img *img, int max_x, int max_y)
{
	img->max_x = max_x;
	img->max_y = max_y;
}

static void	init_image_texture(t_data *data)
{
	data->map.img_n.img = mlx_xpm_file_to_image(data->milx.mlx, \
		data->map.n_tex, &data->map.img_n.max_x, &data->map.img_n.max_y);
	data->map.img_n.addr = mlx_get_data_addr(data->map.img_n.img, \
		&data->map.img_n.bits_per_pixel, &data->map.img_n.line_length, \
		&data->map.img_n.endian);
	data->map.img_e.img = mlx_xpm_file_to_image(data->milx.mlx, \
		data->map.e_tex, &data->map.img_e.max_x, &data->map.img_e.max_y);
	data->map.img_e.addr = mlx_get_data_addr(data->map.img_e.img, \
		&data->map.img_e.bits_per_pixel, &data->map.img_e.line_length, \
		&data->map.img_e.endian);
	data->map.img_s.img = mlx_xpm_file_to_image(data->milx.mlx, \
		data->map.s_tex, &data->map.img_s.max_x, &data->map.img_s.max_y);
	data->map.img_s.addr = mlx_get_data_addr(data->map.img_s.img, \
		&data->map.img_s.bits_per_pixel, &data->map.img_s.line_length, \
		&data->map.img_s.endian);
	data->map.img_w.img = mlx_xpm_file_to_image(data->milx.mlx, \
		data->map.w_tex, &data->map.img_w.max_x, &data->map.img_w.max_y);
	data->map.img_w.addr = mlx_get_data_addr(data->map.img_w.img, \
		&data->map.img_w.bits_per_pixel, &data->map.img_w.line_length, \
		&data->map.img_w.endian);
}

void	init_image(t_data *data)
{
	data->milx.mini.img = mlx_new_image(data->milx.mlx, \
		MINI_MAP + MM_BORDER_SIZE, MINI_MAP + MM_BORDER_SIZE);
	data->milx.mini.addr = mlx_get_data_addr(data->milx.mini.img, \
		&data->milx.mini.bits_per_pixel, &data->milx.mini.line_length, \
		&data->milx.mini.endian);
	data->milx.big.img = mlx_new_image(data->milx.mlx, data->milx.screen_x, \
		data->milx.screen_y);
	data->milx.big.addr = mlx_get_data_addr(data->milx.big.img, \
		&data->milx.big.bits_per_pixel, &data->milx.big.line_length, \
		&data->milx.big.endian);
	init_image_set_size(&data->milx.big, data->milx.screen_x, \
		data->milx.screen_y);
	init_image_set_size(&data->milx.mini, MINI_MAP + MM_BORDER_SIZE, \
		MINI_MAP + MM_BORDER_SIZE);
	init_image_texture(data);
}

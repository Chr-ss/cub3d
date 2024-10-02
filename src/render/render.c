/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: andmadri <andmadri@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/10/02 22:01:57 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	render(t_data *data)
{
	if (data->keys.exit)
		finish_mlx(&data->milx);
	key_hook_move(data);
	key_hook_strafe(data);
	key_hook_turn(data);
	draw_minimap(data);
	ray_caster(data, &data->milx);
	mlx_put_image_to_window(data->milx.mlx, data->milx.mlx_window, data->milx.big.img, 0, 0);
	mlx_put_image_to_window(data->milx.mlx, data->milx.mlx_window, data->milx.mini.img, 5, 5);
	// data->keys.forward = true;
	// frame_counter++;
	// mlx_string_put(data->milx.mlx, data->milx.mlx_window, data->milx.screen_x - 250, 20, create_trgb(0, 0, 0, 0), ft_itoa(frame_counter));
	// mlx_string_put(data->milx.mlx, data->milx.mlx_window, data->milx.screen_x - 300, 20, create_trgb(0, 0, 0, 0), ft_itoa(step_counter));
	// data->keys.turn_right = true;
	// switch_img(data, data->milx.big);
	// switch_img(data, data->milx.mini);
	return (0);
}

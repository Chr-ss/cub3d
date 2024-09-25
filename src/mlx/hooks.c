/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:38:21 by crasche           #+#    #+#             */
/*   Updated: 2024/09/17 11:02:31 by andmadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	finish_mlx(t_minilx *milx)
{
	// mlx_destroy_display(milx->mlx);
	mlx_destroy_window(milx->mlx, milx->mlx_window);
	free(milx->mlx);
	exit(0);
}

// remove when not needed:
void	ray_caster(t_data *data, t_minilx *milx);
void	key_hook_move(void *param);
void	key_hook_turn(void *param);

int	ray_switch_img(void *param)
{
	t_minilx_img	buffer;
	t_data			*data;

	data = (t_data *) param;
	buffer = data->milx.big[DRAW];
	data->milx.big[DRAW] = data->milx.big[DISPLAY];
	data->milx.big[DISPLAY] = buffer;
	mlx_put_image_to_window(data->milx.mlx, data->milx.mlx_window, data->milx.big[DISPLAY].img, 0, 0);
	return (0);
}

int	render(void *param)
{
	t_data	*data;

	data = (t_data*) param;
	if (data->keys.exit)
		finish_mlx(&data->milx);
	key_hook_move(param);
	key_hook_turn(param);
	ray_caster(data, &data->milx);
	ray_switch_img(param);
	draw_minimap(param);
	return (0);
}

int	key_pressed(int key, void *param)
{
	t_keys	*keys;

	keys = (t_keys*)param;
	if (key == KEY_ARROW_UP || key == KEY_W)
		keys->forward = true;
	else if (key == KEY_ARROW_DOWN || key == KEY_S)
		keys->back = true;
	else if (key == KEY_A)
		keys->strafe_left = true;
	else if (key == KEY_D)
		keys->strafe_right = true;
	else if (key == KEY_ARROW_LEFT)
		keys->turn_left = true;
	else if (key == KEY_ARROW_RIGHT)
		keys->turn_right = true;
	else if (key == ESC)
		keys->exit = true;
	return (0);
}

int	key_released(int key, void *param)
{
	t_keys	*keys;

	keys = (t_keys*)param;
	if (key == KEY_ARROW_UP || key == KEY_W)
		keys->forward = false;
	else if (key == KEY_ARROW_DOWN || key == KEY_S)
		keys->back = false;
	else if (key == KEY_A)
		keys->strafe_left = false;
	else if (key == KEY_D)
		keys->strafe_right = false;
	else if (key == KEY_ARROW_LEFT)
		keys->turn_left = false;
	else if (key == KEY_ARROW_RIGHT)
		keys->turn_right = false;
	return (0);
}

void	hooks_mlx(t_data *data)
{
	mlx_loop_hook(data->milx.mlx, render, (void *)data);
	mlx_hook(data->milx.mlx_window, 2, 1L<<0,  key_pressed, &data->keys);
	mlx_hook(data->milx.mlx_window, 3, 1L<<1,  key_released, &data->keys);
	mlx_hook(data->milx.mlx_window, 17, 0L, finish_mlx, &data->milx); // closing the window with x in window
}

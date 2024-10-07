/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: andmadri <andmadri@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/10/07 14:37:04 by crasche       ########   odam.nl         */
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

static int	update_frames(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->frame_time == 0)
		data->frame_time = get_curr_time();
	if (((get_curr_time() - data->frame_time) < (uint64_t)(1000000 / FPS)))
		return (0);
	data->fps = get_curr_time() - data->frame_time;
	data->frame_time = get_curr_time();
	render(data);
	data->fps = round((float)1000000 / data->fps);
	if (BONUS)
		mlx_string_put(data->milx.mlx, data->milx.mlx_window, \
			data->milx.screen_x - 100, 20, RED, \
			ft_itoa(data->fps));
	return (0);
}

static int	key_pressed(int key, void *param)
{
	t_keys	*keys;

	keys = (t_keys *)param;
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
	else if (key == KEY_OPTION)
		keys->mouse = false;
	return (0);
}

static int	key_released(int key, void *param)
{
	t_keys	*keys;

	keys = (t_keys *)param;
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
	else if (key == KEY_OPTION)
		keys->mouse = true;
	return (0);
}

void	hooks_mlx(t_data *data)
{
	mlx_loop_hook(data->milx.mlx, update_frames, (void *)data);
	if (BONUS && data->keys.mouse)
		mlx_mouse_hide(data->milx.mlx, data->milx.mlx_window);
	mlx_hook(data->milx.mlx_window, 2, 1L << 0, key_pressed, &data->keys);
	mlx_hook(data->milx.mlx_window, 3, 1L << 1, key_released, &data->keys);
	mlx_hook(data->milx.mlx_window, 17, 0L, finish_mlx, &data->milx);
}

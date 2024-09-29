/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:38:21 by crasche           #+#    #+#             */
/*   Updated: 2024/09/29 17:07:41 by andmadri         ###   ########.fr       */
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
void	key_hook_move(void *param);
void	key_hook_turn(void *param);
void	key_hook_strafe(void *param);

void	switch_img(t_data *data, t_minilx_img *img)
{
	t_minilx_img	buffer;

	buffer = img[DRAW];
	img[DRAW] = img[DISPLAY];
	img[DISPLAY] = buffer;
	mlx_put_image_to_window(data->milx.mlx, data->milx.mlx_window, img[DISPLAY].img, 0, 0);
}

#include <sys/time.h>

size_t	get_curr_time(void)
{
	struct timeval	timeofday;

	gettimeofday(&timeofday, NULL);
	return (timeofday.tv_sec * 1000000 + timeofday.tv_usec);
}

int	render(void *param)
{
	t_data		*data;
	size_t		time;

	time = get_curr_time();
	data = (t_data*) param;
	if (data->keys.exit)
		finish_mlx(&data->milx);
	key_hook_move(param);
	key_hook_strafe(param);
	key_hook_turn(param);
	draw_minimap(param);
	ray_caster(data, &data->milx);
	switch_img(data, data->milx.big);
	switch_img(data, data->milx.mini);
	time = get_curr_time() - time;
	time = 60000000 / time;
	mlx_string_put(data->milx.mlx, data->milx.mlx_window, data->milx.screen_x - 200, 20, create_trgb(0, 255, 255, 255), ft_itoa(time));
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	int	delta_x;

	delta_x = x - data->mouse_x;
	(void)y;
	// printf("direction of y: %i\n", y);
	if (abs(delta_x) < MOUSE_SENSITIVITY)
	{
		// data->keys.turn_right = false;
		// data->keys.turn_left = false;
		printf("no movement\n");
		return (0);
	}
	if (delta_x > 0)
	{
		// data->player.direct[X] = data->player.direct[X] * cos(TURN_STEP) - data->player.direct[Y] * sin(TURN_STEP);
		// data->player.direct[Y] = data->player.direct[X] * sin(TURN_STEP) + data->player.direct[Y] * cos(TURN_STEP);
		// data->player.direct[X] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
		// data->player.direct[Y] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
		data->keys.turn_right = true;
		printf("right\n");
	}
	else if (delta_x < 0)
	{
		// data->player.direct[X] = data->player.direct[X] * cos(-TURN_STEP) - data->player.direct[Y] * sin(-TURN_STEP);
		// data->player.direct[Y] = data->player.direct[X] * sin(-TURN_STEP) + data->player.direct[Y] * cos(-TURN_STEP);
		// data->player.direct[X] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
		// data->player.direct[Y] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
		data->keys.turn_left = true;
		printf("left\n");
	}
	data->mouse_x = x;
	return(0);
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
	data->keys.turn_left = false;
	data->keys.turn_right = false;
	mlx_loop_hook(data->milx.mlx, render, (void *)data);
	mlx_hook(data->milx.mlx_window, 6, 1L<<6, mouse_move, data);
	mlx_hook(data->milx.mlx_window, 2, 1L<<0,  key_pressed, &data->keys);
	mlx_hook(data->milx.mlx_window, 3, 1L<<1,  key_released, &data->keys);
	mlx_hook(data->milx.mlx_window, 17, 0L, finish_mlx, &data->milx); // closing the window with x in window
}

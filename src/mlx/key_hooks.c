/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hooks.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: andmadri <andmadri@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/10/02 20:18:45 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

uint64_t	get_curr_time(void);

void	rotate_vector(float *dir, float *temp_x, float *temp_y, double angle)
{
	*temp_x = dir[X] * cos(angle) - dir[Y] * sin(angle);
	*temp_y = dir[X] * sin(angle) + dir[Y] * cos(angle);
	*temp_x /= sqrt(*temp_x * *temp_x + *temp_y * *temp_y);
	*temp_y /= sqrt(*temp_x * *temp_x + *temp_y * *temp_y);
}

void	key_hook_strafe(void *param)
{
	t_data	*data;
	float	temp_x;
	float	temp_y;
	double	angle;

	data = (t_data *)param;
	angle = -90 * RAD;
	rotate_vector(data->player.direct, &temp_x, &temp_y, angle);
	if (data->keys.strafe_left && is_not_wall(data, temp_x, temp_y, LEFT))
	{
		data->player.pos[X] += (temp_x * STEP_SIZE);// * (get_curr_time() - data->frame_time));
		data->player.pos[Y] += (temp_y * STEP_SIZE);// * (get_curr_time() - data->frame_time));
	}
	angle = 90 * RAD;
	rotate_vector(data->player.direct, &temp_x, &temp_y, angle);
	if (data->keys.strafe_right && is_not_wall(data, temp_x, temp_y, RIGHT))
	{
		data->player.pos[X] += (temp_x * STEP_SIZE);// * (get_curr_time() - data->frame_time));
		data->player.pos[Y] += (temp_y * STEP_SIZE);// * (get_curr_time() - data->frame_time));
	}
}

void	key_hook_move(void *param)
{
	t_data	*data;
	t_keys	keys;

	data = (t_data *)param;
	keys = data->keys;
	if (keys.forward && is_not_wall(data, data->player.direct[X], data->player.direct[Y], FORWARD))
	{
		data->player.pos[X] += (data->player.direct[X] * STEP_SIZE);// * (get_curr_time() - data->frame_time));
		data->player.pos[Y] += (data->player.direct[Y] * STEP_SIZE);// * (get_curr_time() - data->frame_time));
	}
	else if (keys.back && is_not_wall(data, -data->player.direct[X], -data->player.direct[Y], BACKWARD))
	{
		data->player.pos[X] -= (data->player.direct[X] * STEP_SIZE);// * (get_curr_time() - data->frame_time));
		data->player.pos[Y] -= (data->player.direct[Y] * STEP_SIZE);// * (get_curr_time() - data->frame_time));
	}
}

void	test(t_data *data)
{
	int x;
	int y;

	data->keys.mouse_right = false;
	data->keys.mouse_left = false;
	mlx_mouse_get_pos(data->milx.mlx, data->milx.mlx_window, &x, &y);
	mlx_mouse_move(data->milx.mlx, data->milx.mlx_window, data->milx.screen_x / 2, data->milx.screen_y / 2);
	data->keys.mouse_step = x - data->milx.screen_x / 2;
	if (data->keys.mouse_step > 0)
		data->keys.mouse_right = true;
	else if (data->keys.mouse_step < 0)
		data->keys.mouse_left = true;
	x = data->milx.screen_x / 2;
}

void	key_hook_turn(void *param)
{
	t_data	*data;
	t_keys	keys;

	data = (t_data *)param;
	keys = data->keys;
	test(data);
	if (keys.turn_left || keys.mouse_left)
		rotate_vector(data->player.direct, &data->player.direct[X], &data->player.direct[Y], (-TURN_STEP + (data->keys.mouse_step * 0.001)));
	else if (keys.turn_right || keys.mouse_right)
		rotate_vector(data->player.direct, &data->player.direct[X], &data->player.direct[Y], (TURN_STEP + (data->keys.mouse_step * 0.001)));
}

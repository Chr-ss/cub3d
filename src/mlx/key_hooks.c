/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:38:21 by crasche           #+#    #+#             */
/*   Updated: 2024/09/30 19:22:31 by andmadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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
		data->player.pos[X] += (temp_x * STEP_SIZE);
		data->player.pos[Y] += (temp_y * STEP_SIZE);
	}
	angle = 90 * RAD;
	rotate_vector(data->player.direct, &temp_x, &temp_y, angle);
	if (data->keys.strafe_right && is_not_wall(data, temp_x, temp_y, RIGHT))
	{
		data->player.pos[X] += (temp_x * STEP_SIZE);
		data->player.pos[Y] += (temp_y * STEP_SIZE);
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
		data->player.pos[X] += (data->player.direct[X] * STEP_SIZE);
		data->player.pos[Y] += (data->player.direct[Y] * STEP_SIZE);
	}
	else if (keys.back && is_not_wall(data, -data->player.direct[X], -data->player.direct[Y], BACKWARD))
	{
		data->player.pos[X] -= (data->player.direct[X] * STEP_SIZE);
		data->player.pos[Y] -= (data->player.direct[Y] * STEP_SIZE);
	}
}

void	key_hook_turn(void *param)
{
	t_data	*data;
	t_keys	keys;

	data = (t_data *)param;
	keys = data->keys;
	if (keys.turn_left)
		rotate_vector(data->player.direct, &data->player.direct[X], &data->player.direct[X], -TURN_STEP);
	else if (keys.turn_right)
		rotate_vector(data->player.direct, &data->player.direct[X], &data->player.direct[X], TURN_STEP);
}

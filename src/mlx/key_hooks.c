/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hooks.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:44:17 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	step_direction(t_raycaster *ray);

t_raycaster	collision(t_data *data, float dir_x, float dir_y)
{
	t_raycaster	ray;

	ray = data->ray;
	ray.r_start[X] = data->player.pos[X];
	ray.r_start[Y] = data->player.pos[Y];
	ray.r_pos[X] = ray.r_start[X];
	ray.r_pos[Y] = ray.r_start[Y];
	ray.direction[X] = dir_x;
	ray.direction[Y] = dir_y;
	ray.step_size[X] = sqrt(1 + (ray.direction[Y] / ray.direction[X]) * (ray.direction[Y] / ray.direction[X]));
	ray.step_size[Y] = sqrt(1 + (ray.direction[X] / ray.direction[Y]) * (ray.direction[X] / ray.direction[Y]));
	ray.wall_found = false;
	step_direction(&ray);
	while(!ray.wall_found)
	{
		if(ray.length[X] < ray.length[Y])
		{
			ray.r_pos[X] += ray.step[X];
			ray.final_distance = ray.length[X];
			ray.length[X] += ray.step_size[X];
		}
		else
		{
			ray.r_pos[Y] += ray.step[Y];
			ray.final_distance = ray.length[Y];
			ray.length[Y] += ray.step_size[Y];
		}
		if (data->map.map[ray.r_pos[Y]][ray.r_pos[X]] == '1')
			ray.wall_found = true;
	}
	return (ray);
}

double


int	is_not_wall(t_data *data, float x, float y, int direction)
{
	t_raycaster	ray_forward;
	t_raycaster	ray_backwards;
	t_raycaster	ray_left;
	t_raycaster	ray_right;
	
	ray_forward = collision(data, data->player.direct[X], data->player.direct[Y]);
	ray_backwards = collision(data, -data->player.direct[X], -data->player.direct[Y]);
	ray_left = collision(data, data->player.direct[X] * cos(-90 * (M_PI / 180)) - data->player.direct[Y] * sin(-90 * (M_PI / 180)), data->player.direct[X] * sin(-90 * M_PI / 180) + data->player.direct[Y] * cos(-90 * M_PI / 180));
	ray_right = collision(data, data->player.direct[X] * cos(90 * M_PI / 180) - data->player.direct[Y] * sin(90 * M_PI / 180), data->player.direct[X] * sin(90 * M_PI / 180) + data->player.direct[Y] * cos(90 * M_PI / 180));
	if (ray_forward.final_distance < STEP_SIZE * 8 && direction == FORWARD)
		return (0);
	if (ray_backwards.final_distance < STEP_SIZE * 8 && direction == BACKWARD)
		return (0);
	if (ray_left.final_distance < STEP_SIZE * 8 && direction == LEFT)
		return (0);
	if (ray_right.final_distance < STEP_SIZE * 8 && direction == RIGHT)
		return (0);
	return (1);
}

void	key_hook_move(void *param)
{
	t_data	*data;
	t_keys	keys;
	float	new_x;
	float	new_y;

	data = (t_data *)param;
	keys = data->keys;
	if (keys.forward)
	{
		new_x = data->player.pos[X] + (data->player.direct[X] * STEP_SIZE);
		new_y = data->player.pos[Y] + (data->player.direct[Y] * STEP_SIZE);
		if (is_not_wall(data, new_x, new_y, FORWARD))
		{
			data->player.pos[X] = new_x;
			data->player.pos[Y] = new_y;
		}
	}
	else if (keys.back)
	{
		new_x = data->player.pos[X] - (data->player.direct[X] * STEP_SIZE);
		new_y = data->player.pos[Y] - (data->player.direct[Y] * STEP_SIZE);
		if (is_not_wall(data, new_x, new_y, BACKWARD))
		{
			data->player.pos[X] = new_x;
			data->player.pos[Y] = new_y;
		}
	}
	if (keys.strafe_left)
	{
		float temp_x = data->player.direct[X] * cos(-90 * M_PI / 180) - data->player.direct[Y] * sin(-90 * M_PI / 180);
		float temp_y = data->player.direct[X] * sin(-90 * M_PI / 180) + data->player.direct[Y] * cos(-90 * M_PI / 180);
		temp_x /= sqrt(temp_x * temp_x + temp_y * temp_y);
		temp_y /= sqrt(temp_x * temp_x + temp_y * temp_y);
		new_x = data->player.pos[X] + (temp_x * STEP_SIZE);
		new_y = data->player.pos[Y] + (temp_y * STEP_SIZE);
		if (is_not_wall(data, new_x, new_y, LEFT))
		{
			data->player.pos[X] = new_x;
			data->player.pos[Y] = new_y;
		}
	}
	else if (keys.strafe_right)
	{
		float temp_x = data->player.direct[X] * cos(90 * M_PI / 180) - data->player.direct[Y] * sin(90 * M_PI / 180);
		float temp_y = data->player.direct[X] * sin(90 * M_PI / 180) + data->player.direct[Y] * cos(90 * M_PI / 180);
		temp_x /= sqrt(temp_x * temp_x + temp_y * temp_y);
		temp_y /= sqrt(temp_x * temp_x + temp_y * temp_y);
		new_x = data->player.pos[X] + (temp_x * STEP_SIZE);
		new_y = data->player.pos[Y] + (temp_y * STEP_SIZE);
		if (is_not_wall(data, new_x, new_y, RIGHT))
		{
			data->player.pos[X] = new_x;
			data->player.pos[Y] = new_y;
		}
	}
}

void	key_hook_turn(void *param)
{
	t_data	*data;
	t_keys	keys;

	data = (t_data *)param;
	keys = data->keys;
	if (keys.turn_left)
	{
		data->player.direct[X] = data->player.direct[X] * cos(-TURN_STEP) - data->player.direct[Y] * sin(-TURN_STEP);
		data->player.direct[Y] = data->player.direct[X] * sin(-TURN_STEP) + data->player.direct[Y] * cos(-TURN_STEP);
		data->player.direct[X] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
		data->player.direct[Y] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
	}
	else if (keys.turn_right)
	{
		data->player.direct[X] = data->player.direct[X] * cos(TURN_STEP) - data->player.direct[Y] * sin(TURN_STEP);
		data->player.direct[Y] = data->player.direct[X] * sin(TURN_STEP) + data->player.direct[Y] * cos(TURN_STEP);
		data->player.direct[X] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
		data->player.direct[Y] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
	}
}

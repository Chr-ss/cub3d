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
	// int			plane[2];

	ray = data->ray;
	// plane[X] = -dir_y;
	// plane[Y] = dir_x;
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
		// printf("here\n");
		if (data->map.map[ray.r_pos[Y]][ray.r_pos[X]] == '1')
		{
			// printf("no segmentation fauls\n");
			ray.wall_found = true;
		}
	}
	return (ray);
}

int	is_wall(t_data *data, float x, float y)
{
	// int 		map_x;
	// int 		map_y;
	t_raycaster	ray;
	
	// map_x = x;
	// map_y = y;
	(void)x;
	(void)y;
	ray = collision(data, data->player.direct[X], data->player.direct[Y]);
	// Map brounds check, includeing x=1, y=1, x=max or y=max as they have to be walls
	// if (x > data->map.x_max || x < 1 || y < 1 || y > data->map.y_max)
	// 	return (1);
	// if (data->map.map[map_y][map_x] == '1' || data->map.map[map_y][map_x] == ' ')
	// 	return (1);
	// printf("not wall--> final distance: %f \n", ray.final_distance);
	if (data->player.direct[Y] >= 0 && data->player.direct[X] <= 0 && (ray.final_distance < STEP_SIZE ))
	{
		// printf("collision--> final distance: %f \n",ray.final_distance);
		return (1);
	}
	// if (data->player.direct[Y] > 0 && data->player.direct[X] <= 0 && (ray.final_distance < STEP_SIZE))
	// 	return (1);
	return (0);
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
		if (!is_wall(data, new_x, new_y))
		{
			data->player.pos[X] = new_x;
			data->player.pos[Y] = new_y;
		}
	}
	else if (keys.back)
	{
		new_x = data->player.pos[X] - (data->player.direct[X] * STEP_SIZE);
		new_y = data->player.pos[Y] - (data->player.direct[Y] * STEP_SIZE);
		if (!is_wall(data, new_x, new_y))
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
		if (!is_wall(data, new_x, new_y))
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
		if (!is_wall(data, new_x, new_y))
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

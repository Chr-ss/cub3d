/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:38:21 by crasche           #+#    #+#             */
/*   Updated: 2024/09/29 17:08:51 by andmadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	step_direction(t_raycaster *ray);

void	collision_ray_init(t_data *data, t_raycaster *ray, float dir_x, float dir_y)
{
	ft_bzero(ray, sizeof(t_raycaster));
	ray->r_start[X] = data->player.pos[X];
	ray->r_start[Y] = data->player.pos[Y];
	ray->r_pos[X] = ray->r_start[X];
	ray->r_pos[Y] = ray->r_start[Y];
	ray->direction[X] = dir_x;
	ray->direction[Y] = dir_y;
	ray->step_size[X] = sqrt(1 + (ray->direction[Y] / ray->direction[X]) * (ray->direction[Y] / ray->direction[X]));
	ray->step_size[Y] = sqrt(1 + (ray->direction[X] / ray->direction[Y]) * (ray->direction[X] / ray->direction[Y]));
	ray->wall_found = false;
	step_direction(ray);
}

int	collision(t_data *data, float dir_x, float dir_y)
{
	t_raycaster	ray;

	collision_ray_init(data, &ray, dir_x, dir_y);
	while(ray.final_distance < (STEP_SIZE * 3))
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
			break ;
	}
	if (ray.final_distance < (STEP_SIZE * 2))
		return (1);
	else 
		return (0);
}

int	is_not_wall(t_data *data, float vx, float vy, int direction)
{
	if (direction == FORWARD && collision(data, vx, vy))
		return (0);
	if (direction == BACKWARD && collision(data, vx, vy))
		return (0);
	if (direction == LEFT && collision(data, vx, vy))
		return (0);
	if (direction == RIGHT && collision(data, vx, vy))
		return (0);
	return (1);
}

void	key_hook_strafe(void *param)
{
	t_data	*data;
	float temp_x;
	float temp_y;

	data = (t_data *)param;
	temp_x = data->player.direct[X] * cos(-90 * RAD) - data->player.direct[Y] * sin(-90 * RAD);
	temp_y = data->player.direct[X] * sin(-90 * RAD) + data->player.direct[Y] * cos(-90 * RAD);
	temp_x /= sqrt(temp_x * temp_x + temp_y * temp_y);
	temp_y /= sqrt(temp_x * temp_x + temp_y * temp_y);
	if (data->keys.strafe_left && is_not_wall(data, temp_x, temp_y, LEFT))
	{
		data->player.pos[X] += (temp_x * STEP_SIZE);
		data->player.pos[Y] += (temp_y * STEP_SIZE);
	}
	temp_x = data->player.direct[X] * cos(90 * RAD) - data->player.direct[Y] * sin(90 * RAD);
	temp_y = data->player.direct[X] * sin(90 * RAD) + data->player.direct[Y] * cos(90 * RAD);
	temp_x /= sqrt(temp_x * temp_x + temp_y * temp_y);
	temp_y /= sqrt(temp_x * temp_x + temp_y * temp_y);
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

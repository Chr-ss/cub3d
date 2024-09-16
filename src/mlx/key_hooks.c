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

int	is_wall(t_data *data, float x, float y)
{
	int map_x;
	int map_y;
	
	map_x = x;
	map_y = y;
	// Map brounds check, includeing x=1, y=1, x=max or y=max as they have to be walls
	if (x > data->map.x_max || x < 1 || y < 1 || y > data->map.y_max)
		return (1);
	if (data->map.map[map_y][map_x] == '1' || data->map.map[map_y][map_x] == ' ')
		return (1);
	return (0);
}

// WSL: W 119, A 97, S 115, D 100
// MAC: W 13, A 0, S 1, D 2, ESC 53
int	key_hook_ws(int keycode, void *param)
{
	t_data	*data;
	float	new_x;
	float	new_y;

	data = (t_data *)param;
	if (keycode == 119 || keycode == 13)
	{
		printf("KEY:%d ", keycode);
		new_x = data->player.pos[X] + (data->player.direct[X] * STEP_SIZE);
		new_y = data->player.pos[Y] + (data->player.direct[Y] * STEP_SIZE);
		if (!is_wall(data, new_x, new_y))
		{
			data->player.pos[X] = new_x;
			data->player.pos[Y] = new_y;
		}
	}
	else if (keycode == 115 || keycode == 1)
	{
		printf("KEY:%d ", keycode);
		new_x = data->player.pos[X] - (data->player.direct[X] * STEP_SIZE);
		new_y = data->player.pos[Y] - (data->player.direct[Y] * STEP_SIZE);
		if (!is_wall(data, new_x, new_y))
		{
			data->player.pos[X] = new_x;
			data->player.pos[Y] = new_y;
		}
	}
	else 
		return (0);
	printf("\tPOS: %f %f\tVIEW: %f %f\n", data->player.pos[X], data->player.pos[Y], data->player.direct[X], data->player.direct[Y]);
	return (0);
}

int	key_hook_ad(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 97 || keycode == 0)
	{
		printf("KEY:%d ", keycode);
		data->player.direct[X] = data->player.direct[X] * cos(-0.1) - data->player.direct[Y] * sin(-0.1);
		data->player.direct[Y] = data->player.direct[X] * sin(-0.1) + data->player.direct[Y] * cos(-0.1);
		data->player.direct[X] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
		data->player.direct[Y] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
	}
	else if (keycode == 100 || keycode == 2)
	{
		printf("KEY:%d ", keycode);
		data->player.direct[X] = data->player.direct[X] * cos(0.1) - data->player.direct[Y] * sin(0.1);
		data->player.direct[Y] = data->player.direct[X] * sin(0.1) + data->player.direct[Y] * cos(0.1);
		data->player.direct[X] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
		data->player.direct[Y] /= sqrt(data->player.direct[X] * data->player.direct[X] + data->player.direct[Y] * data->player.direct[Y]);
	}
	else 
		return (0);
	printf("\tPOS: %f %f\tVIEW: %f %f\n", data->player.pos[X], data->player.pos[Y], data->player.direct[X], data->player.direct[Y]);
	return (0);
}

int	key_hook_esc(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 0xff1b)
	{
		printf("KEY:%d \n", keycode);
		finish_mlx(&(data->milx));
	}
	return (0);
}

int	key_hook_esc_mac(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 53)
	{
		printf("KEY:%d \n", keycode);
		finish_mlx(&(data->milx));
	}
	return (0);
}

int	key_hook(int keycode, void *param)
{
	key_hook_ws(keycode, param);
	key_hook_ad(keycode, param);
	key_hook_esc_mac(keycode, param);
	return (0);
}
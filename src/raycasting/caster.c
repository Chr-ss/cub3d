/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   caster.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:44:17 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	draw_line(t_minilx *milx, int x, int start_y, int line_height, int color)
{
	int	y;

	y = 0;
	while(y < line_height)
	{
			img_mlx_pixel_put(&milx->big[DRAW], x, start_y + y, color);
		y++;
	}
}

void	step_direction(t_raycaster *ray)
{
	if (ray->direction[X] >= 0)
	{
		ray->step[X] = 1;
		ray->length[X] = (((float)ray->r_pos[X] + 1) - ray->r_start[X]) * ray->step_size[X];
	}
	else if (ray->direction[X] < 0)
	{
		ray->step[X] = -1;
		ray->length[X] = (ray->r_start[X] - (float)ray->r_pos[X]) * ray->step_size[X];
	}
	if (ray->direction[Y] >= 0)
	{
		ray->step[Y] = 1;
		ray->length[Y] = (((float)ray->r_pos[Y] + 1) - ray->r_start[Y]) * ray->step_size[Y];
	}
	else if (ray->direction[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->length[Y] = (ray->r_start[Y] - (float)ray->r_pos[Y]) * ray->step_size[Y];
	}
}

void	ray_caster_init(t_raycaster	*ray, t_player *player)
{
	ft_bzero(ray, sizeof(t_raycaster));
	player->plane[X] = -player->direct[Y];
	player->plane[Y] = player->direct[X];
	ray->r_start[X] = player->pos[X];
	ray->r_start[Y] = player->pos[Y]; 
	ray->plane_magnitude = tan((float)(FOV / 2) * RAD);
}

void	ray_caster_calculations(t_data *data, t_raycaster *ray, t_player *player, int x)
{
	ray->r_pos[X] = ray->r_start[X];
	ray->r_pos[Y] = ray->r_start[Y];
	ray->wall_found = false;
	ray->plane_scale = (float)2 * ((float)x / (float)data->milx.screen_x) - (float)1;
	ray->direction[X] = player->direct[X] + (player->plane[X] * ray->plane_magnitude) * ray->plane_scale;
	ray->direction[Y] = player->direct[Y] + (player->plane[Y] * ray->plane_magnitude) * ray->plane_scale;
	ray->step_size[X] = sqrt(1 + (ray->direction[Y] / ray->direction[X]) * (ray->direction[Y] / ray->direction[X]));
	ray->step_size[Y] = sqrt(1 + (ray->direction[X] / ray->direction[Y]) * (ray->direction[X] / ray->direction[Y]));
	step_direction(ray);
}

void	ray_caster_step(t_data *data, t_raycaster *ray)
{
	if(ray->length[X] < ray->length[Y])
	{
		ray->r_pos[X] += ray->step[X];
		ray->final_distance = ray->length[X];
		ray->length[X] += ray->step_size[X];
		ray->wall_direction = LR;
	}
	else
	{
		ray->r_pos[Y] += ray->step[Y];
		ray->final_distance = ray->length[Y];
		ray->length[Y] += ray->step_size[Y];
		ray->wall_direction = TB;
	}
	if (data->map.map[ray->r_pos[Y]][ray->r_pos[X]] == '1')
		ray->wall_found = true;
}

void	ray_caster(t_data *data, t_minilx *milx)
{
	t_raycaster	ray;
	t_player	player;
	// int			x;
	// float		line_height;

	player = data->player;
	ray_caster_init(&ray, &player);
	while(ray.x < milx->screen_x)
	{
		ray_caster_calculations(data, &ray, &player, ray.x);
		while(!ray.wall_found)
			ray_caster_step(data, &ray);
		ray.line_height = (float)milx->screen_y / (float)(ray.final_distance * cos((float)(FOV/2) * RAD)); // (float)milx->screen_y / 
		ray.intersect[X] = ray.direction[X] * ray.final_distance + ray.r_start[X];
		ray.intersect[Y] = ray.direction[Y] * ray.final_distance + ray.r_start[Y];
		data->ray = ray;
		draw_line(milx, ray.x, 0, (milx->screen_y - ray.line_height) / 2, create_trgb(2, 220, 100, 0)); //sky
		draw_line(milx, ray.x, milx->screen_y / 2 + ray.line_height / 2, (milx->screen_y - ray.line_height) / 2, create_trgb(2, 0, 102, 102)); //floor
		draw_texture(data);
		ray.x++;
	}
}

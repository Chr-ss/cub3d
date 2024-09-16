/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:44:17 by crasche       ########   odam.nl         */
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

void	hooks_mlx(t_data *data)
{
	mlx_loop_hook(data->milx.mlx, draw_minimap, (void *)data);
	mlx_hook(data->milx.mlx_window, 17, 0L, finish_mlx, &data->milx); // closing the window with x in window
	mlx_hook(data->milx.mlx_window, 2, 1L << 0, key_hook_esc, &data->milx); // closing the window with ESC
	mlx_key_hook(data->milx.mlx_window, key_hook, (void *)data);
}

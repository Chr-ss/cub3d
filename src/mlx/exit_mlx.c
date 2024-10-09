/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: andmadri <andmadri@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/10/09 14:24:50 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	destroy_images(t_data *data, t_minilx *milx)
{
	mlx_destroy_image(milx->mlx, milx->big.img);
	mlx_destroy_image(milx->mlx, data->map.img_n.img);
	mlx_destroy_image(milx->mlx, data->map.img_s.img);
	mlx_destroy_image(milx->mlx, data->map.img_e.img);
	mlx_destroy_image(milx->mlx, data->map.img_w.img);
	if (BONUS)
		mlx_destroy_image(milx->mlx, milx->mini.img);
}

int	finish_mlx(t_data *data)
{
	t_minilx	milx;

	milx = data->milx;
	destroy_images(data, &milx);
	mlx_destroy_window(milx.mlx, milx.mlx_window);
	mlx_destroy_display(milx.mlx);
	free(milx.mlx);
	free_all(data);
	exit(0);
}

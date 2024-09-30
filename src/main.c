/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:49:00 by crasche           #+#    #+#             */
/*   Updated: 2024/09/30 19:03:44 by andmadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	init_mlx_struct(t_data *data, t_minilx *milx)
{
	milx->mlx = mlx_init();
	if (!milx->mlx)
		return (free_all(data), EXIT_FAILURE);
	mlx_get_screen_size(milx->mlx, &milx->screen_x, &milx->screen_y);
	// milx->screen_x = 800;
	// milx->screen_y = 620;
	milx->mlx_window = mlx_new_window(milx->mlx, milx->screen_x, \
	milx->screen_y, "CUBE3D");
	if (!milx->mlx_window)
		return (free_all(data), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data		data;

	ft_bzero(&data, sizeof(t_data));
	data.mouse_x = 0;
	data.mouse_y = 0;
	if (argc <= 1)
		error("Missing map.", &data);
	else if (argc > 2)
		error("To many arguments.", &data);
	data.map.map_read.filename = argv[1];
	map_init(&data, &data.map);
	map_parse(&data, data.map.map);
	if (init_mlx_struct(&data, &data.milx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_image(&data);
	hooks_mlx(&data);
	mlx_loop(data.milx.mlx);
	free_all(&data);
	return (0);
}

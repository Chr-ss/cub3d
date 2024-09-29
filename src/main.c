/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:49:00 by crasche           #+#    #+#             */
/*   Updated: 2024/09/17 19:32:07 by andmadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
	// map_print(&data, &data.map);
	data.milx.mlx = mlx_init();
	if (!data.milx.mlx)
		return (free_all(&data), EXIT_FAILURE);
	mlx_get_screen_size(data.milx.mlx, &data.milx.screen_x, &data.milx.screen_y);
	// data.milx.screen_x = 800;
	// data.milx.screen_y = 620;
	data.milx.mlx_window = mlx_new_window(data.milx.mlx, data.milx.screen_x, data.milx.screen_y, "CUBE3D");
	if (!data.milx.mlx_window)
		return (free_all(&data), EXIT_FAILURE); // does this happen in free_all?? free(data.milx.mlx), 
	init_image(&data);
	hooks_mlx(&data);
	mlx_loop(data.milx.mlx);
	free_all(&data); // does this happen in free all?? free(data.milx.mlx),
	return (0);
}

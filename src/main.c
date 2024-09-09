/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:49:00 by crasche           #+#    #+#             */
/*   Updated: 2024/09/09 17:06:49 by andmadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_minilx	milx;

	ft_bzero(&data, sizeof(t_data));
	if (argc <= 1)
		error("Missing map.", &data);
	else if (argc > 2)
		error("To many arguments.", &data);
	data.map.map_read.filename = argv[1];
	map_init(&data, &data.map);
	map_parse(&data, data.map.map);
	map_print(&data, &data.map);
	exit(1);


	milx.mlx = mlx_init();
	if (!milx.mlx)
		return (EXIT_FAILURE); //maybe do it somewhere else or free something
	mlx_get_screen_size(milx.mlx, &milx.size_x, &milx.size_y);
	milx.mlx_window = mlx_new_window(milx.mlx, milx.size_x, milx.size_y, "CUBE3D");
	if (!milx.mlx_window)
		return (free(milx.mlx), EXIT_FAILURE); //maybe free_all data
	mlx_hook(milx.mlx_window, 17, 0L, &mlx_finish, &milx);
	free_all(&data); //it should go here?
	mlx_loop(milx.mlx);
	return (0);
}

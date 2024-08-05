/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 13:49:00 by crasche       #+#    #+#                 */
/*   Updated: 2024/08/05 14:20:38 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	error(char msg)
{
	if (msg)
		perror(msg);
	exit(1);
}

int	read_map(t_data *data, t_map *map)
{

	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_map	map;

	if (argc <= 1)
		error("Missing map.");
	else if (argc > 2)
		error("To many arguments.");
	data.map = map;
	map.filename = argv[1];
	if (read_map(&data, &map))
		error(NULL);
}
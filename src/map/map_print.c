/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_print.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:38:21 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:44:17 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	map_print(t_data *data, t_map *map)
{
	int	i;

	i = 0;
	if (map->n_tex)
		printf("n_tex: %s\n", map->n_tex);
	if (map->e_tex)
		printf("e_tex: %s\n", map->e_tex);
	if (map->s_tex)
		printf("s_tex: %s\n", map->s_tex);
	if (map->w_tex)
		printf("w_tex: %s\n", map->w_tex);
	if (map->f_col)
		printf("f_col: %s\n", map->f_col);
	if (map->c_col)
		printf("c_col: %s\n", map->c_col);
	printf("x_max: %d\n", map->x_max);
	printf("y_max: %d\n", map->y_max);
	printf("---MAP---\n");
	while (map->map[i])
	{
		printf("%s$\n", map->map[i]);
		i++;
	}
	printf("---END MAP---\n");
	(void) data;
}

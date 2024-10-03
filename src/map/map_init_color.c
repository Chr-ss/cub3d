/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_init_color.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: andmadri <andmadri@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:31:41 by crasche       #+#    #+#                 */
/*   Updated: 2024/10/02 22:51:59 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	map_color_array_size(t_data *data, char **c_split, char **f_split)
{
	int	i;

	i = 0;
	while (c_split && c_split[i])
		i++;
	if (i != 3)
		error("Error, ceiling color invalid.", data);
	i = 0;
	while (f_split && f_split[i])
		i++;
	if (i != 3)
		error("Error, floor color invalid.", data);
}

static int	map_color_range_check(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	else
		return (0);
}

static void	map_color_rgb_convert(t_data *data, t_color *color)
{
	color->c[R] = ft_atoi(color->c_split[R]);
	color->c[G] = ft_atoi(color->c_split[G]);
	color->c[B] = ft_atoi(color->c_split[B]);
	if (map_color_range_check(color->c[R], color->c[G], color->c[B]))
		error("Error, ceiling color invalid.", data);
	color->f[R] = ft_atoi(color->f_split[R]);
	color->f[G] = ft_atoi(color->f_split[G]);
	color->f[B] = ft_atoi(color->f_split[B]);
	if (map_color_range_check(color->f[R], color->f[G], color->f[B]))
		error("Error, floor color invalid.", data);
}

void	map_color(t_data *data, t_color *color)
{
	color->c_split = ft_split(color->c_col, ',');
	color->f_split = ft_split(color->f_col, ',');
	if (!color->c_split || !color->f_split)
		error("Malloc error, color split.", data);
	map_color_array_size(data, color->c_split, color->f_split);
	map_color_rgb_convert(data, color);
	data->map.c_col = create_trgb(0, color->c[R], color->c[G], color->c[B]);
	data->map.f_col = create_trgb(0, color->f[R], color->f[G], color->f[B]);
}

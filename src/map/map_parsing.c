/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:26:53 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:44:21 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	map_parse_wallcheck(t_data *data, char **map, int i, int j)
{
	if (i == 0 || (i && map[i - 1][j] == ' '))
		error("Error, unclosed map", data);
	if (j == 0 || (j && map[i][j - 1] == ' '))
		error("Error, unclosed map", data);
	if (!map[i + 1] || (map[i + 1] && map[i + 1][j] == ' '))
		error("Error, unclosed map", data);
	if (map[i][j + 1] == '\0' || map[i][j + 1] == ' ')
		error("Error, unclosed map", data);
}

void	map_parse_player(t_data *data, char **map, int i, int j)
{
	data->player.x_pos = i;
	data->player.y_pos = j;
	data->player.direction = map[i][j];
	map[i][j] = '0';
	map_parse_wallcheck(data, map, i, j);
}

void	map_parse_meta(t_data *data)
{
	if (!data->map.n_tex)
		error("Error, missing north texture", data);
	if (!data->map.e_tex)
		error("Error, missing east texture", data);
	if (!data->map.s_tex)
		error("Error, missing south texture", data);
	if (!data->map.w_tex)
		error("Error, missing west texture", data);
	if (!data->map.f_col)
		error("Error, missing floor color", data);
	if (!data->map.c_col)
		error("Error, missing ceiling color", data);
}

void	map_parse(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	map_parse_meta(data);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				map_parse_wallcheck(data, map, i, j);
			else if (map[i][j] == 'N' || map[i][j] == 'E' \
				|| map[i][j] == 'S' || map[i][j] == 'W')
				map_parse_player(data, map, i, j);
			else if (map[i][j] != '1' && map[i][j] != ' ')
				error("Error, invalid char in map", data);
			j++;
		}
		i++;
	}
	if (!data->player.direction)
		error("Error, missing player position", data);
}

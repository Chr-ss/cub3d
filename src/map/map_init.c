/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:28:42 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:44:23 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	map_fill(t_data *data, t_map *map)
{
	int		i;
	char	*old;

	i = 0;
	while (map->map[i])
	{
		if ((int) ft_strlen(map->map[i]) != map->y_max)
		{
			old = map->map[i];
			map->map[i] = ft_calloc(map->y_max + 1, sizeof(char));
			if (!map->map[i])
			{
				freenull((void **) &old);
				error("Error, malloc map_fill", data);
			}
			memset(map->map[i], ' ', map->y_max);
			ft_strlcpy(map->map[i], old, ft_strlen(old) + 1);
			map->map[i][ft_strlen(old)] = ' ';
			freenull((void **) &old);
		}
		i++;
	}
}

void	map_meta(t_data *data, t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		if (!ft_strncmp(map->map[i], "NO ", 3))
			map_meta_copy(data, map->map[i], &map->n_tex, 2);
		else if (!ft_strncmp(map->map[i], "SO ", 3))
			map_meta_copy(data, map->map[i], &map->s_tex, 2);
		else if (!ft_strncmp(map->map[i], "WE ", 3))
			map_meta_copy(data, map->map[i], &map->w_tex, 2);
		else if (!ft_strncmp(map->map[i], "EA ", 3))
			map_meta_copy(data, map->map[i], &map->e_tex, 2);
		else if (!ft_strncmp(map->map[i], "F ", 2))
			map_meta_copy(data, map->map[i], &map->f_col, 1);
		else if (!ft_strncmp(map->map[i], "C ", 2))
			map_meta_copy(data, map->map[i], &map->c_col, 1);
		else
		{
			i++;
			continue ;
		}
		map_clear_line(data, map, i);
	}
}

void	map_split(t_data *data, t_map *map)
{
	map->map = ft_split(map->map_read.read, '\n');
	if (!map->map)
		error("Error, split map malloc", data);
}

void	map_read(t_data *data, t_map *map)
{
	char	buf[READBUF + 1];
	int		readbyt;
	char	*old;

	readbyt = 1;
	while (readbyt > 0)
	{
		ft_bzero(buf, READBUF + 1);
		readbyt = read(map->map_read.fd, buf, READBUF);
		if (readbyt == -1)
			error ("Error, read error for map", data);
		old = map->map_read.read;
		if (!map->map_read.read)
			map->map_read.read = ft_strdup(buf);
		else
			map->map_read.read = ft_strjoin(map->map_read.read, buf);
		free(old);
		if (!map->map_read.read)
			error ("Error, read malloc", data);
	}
}

int	map_init(t_data *data, t_map *map)
{
	if (check_extension(map->map_read.filename))
		error("Error, not .cub file", data);
	map->map_read.fd = open(map->map_read.filename, O_RDONLY);
	if (map->map_read.fd == -1)
		error("Error, unable to open map", data);
	map->map_read.read = NULL;
	map_read(data, map);
	if (close(map->map_read.fd) == -1)
		error("Error, unable to close map", data);
	map_split(data, map);
	map_meta(data, map);
	map_clear(data, map);
	map_fill(data, map);
	return (0);
}

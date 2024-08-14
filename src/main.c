/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 13:49:00 by crasche       #+#    #+#                 */
/*   Updated: 2024/08/14 15:00:02 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

void	freenull(void **to_free)
{
	free(*to_free);
	*to_free = NULL;
}

void	free_all(t_data *data)
{
	freenull((void **) &data->map.map_read.read);
}

void	error(char *msg, t_data *data)
{
	if (msg)
		perror(msg);
	free_all(data);
	exit(1);
}

void	map_meta_copy(t_data *data, char *line, char **meta, int prefix)
{
	if (*meta)
		error("Error, duplicate metadata in map", data);
	while (ft_isspace(line[prefix]))
		prefix++;
	if (line[prefix])
	{
		*meta = ft_strdup(&line[prefix]);
		if (!*meta)
			error("Error, map meta malloc", data);
	}
}

void	map_clear_line(t_data *data, t_map *map, int i)
{
	int	j;

	(void) data;
	j = i + 1;
	freenull((void **) &map->map[i]);
	while (map->map[j])
	{
		map->map[i] = map->map[j];
		i++;
		j++;
	}
	map->map[i] = NULL;
}

void	map_meta(t_data *data, t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		if (!ft_strncmp(map->map[i], "NO", 2))
			map_meta_copy(data, map->map[i], &map->n_tex, 2);
		else if (!ft_strncmp(map->map[i], "SO", 2))
			map_meta_copy(data, map->map[i], &map->s_tex, 2);
		else if (!ft_strncmp(map->map[i], "WE", 2))
			map_meta_copy(data, map->map[i], &map->w_tex, 2);
		else if (!ft_strncmp(map->map[i], "EA", 2))
			map_meta_copy(data, map->map[i], &map->e_tex, 2);
		else if (!ft_strncmp(map->map[i], "F", 1))
			map_meta_copy(data, map->map[i], &map->f_col, 1);
		else if (!ft_strncmp(map->map[i], "C", 1))
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
		map->map_read.read = ft_strjoin(map->map_read.read, buf);
		free(old);
		if (!map->map_read.read)
			error ("Error, read malloc", data);
	}
}

void	map_clear(t_data *data, t_map *map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (ft_isspace(map->map[i][j]))
			j++;
		if (!map->map[i][j])
			map_clear_line(data, map, i);
		len = ft_strlen(map->map[i]);
		if (len > map->y_max)
			map->y_max = len;
		i++;
	}
	map->x_max = i - 1;
}

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

int	map_init(t_data *data, t_map *map)
{
	map->map_read.fd = open(map->map_read.filename, O_RDONLY);
	if (map->map_read.fd == -1)
		error("Error, unable to open map", data);
	map->map_read.read = ft_calloc(0, 0);
	map_read(data, map);
	if (close(map->map_read.fd) == -1)
		error("Error, unable to close map", data);
	map_split(data, map);
	map_meta(data, map);
	map_clear(data, map);
	map_fill(data, map);
	return (0);
}

void	init(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
}

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
	if (!data->player.direction)
		error("Error, missing player position", data);
}

void	map_parse(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
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
	map_parse_meta(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init(&data);
	if (argc <= 1)
		error("Missing map.", &data);
	else if (argc > 2)
		error("To many arguments.", &data);
	data.map.map_read.filename = argv[1];
	map_init(&data, &data.map);
	map_parse(&data, data.map.map);
	map_print(&data, &data.map);
	free_all(&data);
	return (0);
}

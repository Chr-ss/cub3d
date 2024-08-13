/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 13:49:00 by crasche       #+#    #+#                 */
/*   Updated: 2024/08/13 18:52:32 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"



void	map_print(t_data *data, t_map *map)
{
	int	i;

	i = 0;
	printf("---MAP---\n");
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
	printf("---END MAP---\n");
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
	(void) data;
}


void	freenull(void **to_free)
{
	free(*to_free);
	*to_free = NULL;
}

void	free_all(t_data *data)
{
	if (data->map)
		freenull((void **) &data->map->read);
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
	while (ft_isspace(line[prefix]))
		prefix++;
	if (line[prefix])
	{
		*meta = ft_strdup(&line[prefix]);
		if (!*meta)
			error("Error, map meta malloc.", data);
	}
}
void	map_clear_line(t_data *data, t_map *map, int i)
{
	(void)data;
	int	j;

	j = i + 1;
	freenull((void **) &map->map[i]);
	while(map->map[j])
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
			continue;
		}
		map_clear_line(data, map, i);
	}
	map_print(data, map);
}

void	map_split(t_data *data, t_map *map)
{
	map->map = ft_split(map->read, '\n');
	if (!map->map)
		error("Error, split map malloc.", data);
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
		readbyt = read(map->fd, buf, READBUF);
		if (readbyt == -1)
			error ("Error, read error for map.", data);
		old = map->read;
		map->read = ft_strjoin(map->read, buf);
		free(old);
		if (!map->read)
			error ("Error, read malloc.", data);
	}
}

void	map_clear(t_data *data, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while(map->map[i])
	{
		j = 0;
		while (ft_isspace(map->map[i][j]))
			j++;
		if (!map->map[i][j])
			map_clear_line(data, map, i);
		i++;
	}
}

int	map_init(t_data *data, t_map *map)
{
	map->fd = open(map->filename, O_RDONLY);
	if (map->fd == -1)
		error("Error, unable to open map.", data);
	map->read = ft_calloc(0, 0);
	map_read(data, map);
	if (close(map->fd) == -1)
		error("Error, unable to close map.", data);
	map_split(data, map);
	map_meta(data, map);
	map_clear(data, map);
	return (0);
}

void	init(t_data *data, t_map *map)
{
	ft_bzero(data, sizeof(t_data));
	ft_bzero(map, sizeof(t_map));
	// map->capacity = DYNSTR;
}


int	main(int argc, char **argv)
{
	t_data	data;
	t_map	map;

	init(&data, &map);
	if (argc <= 1)
		error("Missing map.", &data);
	else if (argc > 2)
		error("To many arguments.", &data);
	data.map = &map;
	map.filename = argv[1];
	map_init(&data, &map);
	map_print(&data, &map);
}
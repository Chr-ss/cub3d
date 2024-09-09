/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_untils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:31:41 by crasche           #+#    #+#             */
/*   Updated: 2024/09/09 13:53:14 by andmadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	check_extension(char *str)
{
	int	i;

<<<<<<< HEAD
	i = 1;
	while (str[i] && str[i] != '.')
		i++;
	if (!ft_strncmp(&str[i], ".cub", ft_strlen(&str[i])))
=======
	i = ft_strlen(str);
	if (i < 4)
		return (1);
	else if (!ft_strcmp(&str[i - 4], ".cub"))
>>>>>>> main
		return (0);
	return (1);
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
<<<<<<< HEAD
		printf("the length represents x: %i\n", len);
=======
>>>>>>> main
		if (len > map->x_max)
			map->x_max = len;
		i++;
	}
	map->y_max = i;
}

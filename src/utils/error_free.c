/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:27:39 by crasche           #+#    #+#             */
/*   Updated: 2024/10/08 15:56:03 by andmadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	freenull(void **to_free)
{
	free(*to_free);
	*to_free = NULL;
}

void	free_dbl_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_all(t_data *data)
{
	freenull((void **) &data->map.map_read.read);
	free(data->map.n_tex);
	free(data->map.s_tex);
	free(data->map.e_tex);
	free(data->map.w_tex);
	free(data->map.color.f_col);
	free(data->map.color.c_col);
	free_dbl_array(data->map.map);
	free_dbl_array(data->map.color.f_split);
	free_dbl_array(data->map.color.c_split);
}

void	error(char *msg, t_data *data)
{
	if (msg)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	free_all(data);
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_free.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 20:27:39 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/08 20:44:16 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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

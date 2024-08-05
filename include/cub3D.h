/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 13:49:31 by crasche       #+#    #+#                 */
/*   Updated: 2024/08/05 14:56:41 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// authorised external functions:
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

// libft authorised
# include "../lib/libft/include/libft.h"
// MLX42
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef	struct	s_map
{
	char	*filename;
	char	*read;

}	t_map;

typedef	struct	s_data
{
	t_map	*map;
}	t_data;

// marcos
# include <errno.h>
# include <fcntl.h>
# include <errno.h>

#endif // CUB3D_H
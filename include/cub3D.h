/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:49:31 by crasche           #+#    #+#             */
/*   Updated: 2024/09/07 14:11:43 by andmadri         ###   ########.fr       */
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
// # include "../lib/MLX42/include/MLX42/MLX42.h"
// minilibx
# include "../lib/minilibx_linux/mlx.h"
# include "../lib/minilibx_linux/mlx_int.h"

typedef	struct s_minilx
{
	void	*mlx;
	void	*mlx_window;
	int		size_x;
	int		size_y;
}	t_minilx;

typedef	struct	s_payer
{
	int		x_pos;
	int		y_pos;
	char	direction;
}	t_player;

typedef	struct	s_map_read
{
	char	*filename;
	int		fd;
	char	*read;
}	t_map_read;

typedef struct s_color
{
	char	**floor;
	char	**ceiling;
	int		f[4];
	int		c[4];
}	t_color;


typedef	struct	s_map
{
	t_map_read	map_read;
	t_color		color;
	char		**map;
	int			x_max;
	int			y_max;
	char		*n_tex;
	char		*e_tex;
	char		*s_tex;
	char		*w_tex;
	char		*f_col;
	char		*c_col;
}	t_map;

typedef	struct	s_data
{
	t_map		map;
	t_player	player;
}	t_data;

// marcos
# include <errno.h>
# include <fcntl.h>
# include <errno.h>

# define DYNSTR 8
# define READBUF 1024

#endif // CUB3D_H
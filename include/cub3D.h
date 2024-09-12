/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 13:49:31 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/12 01:31:04 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// external functions:
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

// libft
# include "../lib/libft/include/libft.h"
// minilibx
# include "../lib/minilibx/mlx.h"

# define X 0
# define Y 1

# define BASE_FOV 60

# define MINI_MAP 300
# define MINI_MAP_GRID 11

# define X 0
# define Y 1

# define DRAW 0
# define DISPLAY 1

# define TURN_STEP 0.1

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

# define BASE_FOV 60


typedef	struct s_minilx_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		offset;
}	t_minilx_img;

typedef	struct s_minilx
{
	void			*mlx;
	void			*mlx_window;
	int				size_x;
	int				size_y;
	t_minilx_img	mini[2];
}	t_minilx;

typedef	struct	s_payer
{
	// int		x_pos;
	// int		y_pos;
	// char	direction;
	float	pos[2];
	float	direct[2];
	float	plane[2];
	int		fov;
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
	t_minilx	milx;
}	t_data;

// marcos
# include <errno.h>
# include <fcntl.h>
# include <errno.h>

# define DYNSTR 8
# define READBUF 1024



// map/map_init_utils.c
int		check_extension(char *str);
void	map_clear(t_data *data, t_map *map);
void	map_clear_line(t_data *data, t_map *map, int i);
void	map_meta_copy(t_data *data, char *line, char **meta, int prefix);

// map/map_init.c
int		map_init(t_data *data, t_map *map);
void	map_read(t_data *data, t_map *map);
void	map_split(t_data *data, t_map *map);
void	map_meta(t_data *data, t_map *map);
void	map_fill(t_data *data, t_map *map);

// map/map_parsing.c
void	map_parse(t_data *data, char **map);
void	map_parse_meta(t_data *data);
void	map_parse_player(t_data *data, char **map, int i, int j);
void	map_parse_wallcheck(t_data *data, char **map, int i, int j);

// map/map_print.c
void	map_print(t_data *data, t_map *map);

// utils/error_free.c
void	freenull(void **to_free);
void	error(char *msg, t_data *data);
void	free_all(t_data *data);

#endif // CUB3D_H

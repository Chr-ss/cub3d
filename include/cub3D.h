/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmadri <andmadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:49:31 by crasche           #+#    #+#             */
/*   Updated: 2024/09/17 19:16:05 by andmadri         ###   ########.fr       */
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
# include <stdbool.h>

// libft
# include "../lib/libft/include/libft.h"
// minilibx
# include "../lib/minilibx/mlx.h"

# define X 0
# define Y 1

# define MINI_MAP 300
# define MINI_MAP_GRID 11
# define MINI_MAP_BORDER 3
# define TILE_SIZE MINI_MAP / 10

# define STEP_SIZE 0.1
# define TURN_STEP 0.1

# define X 0
# define Y 1

# define DRAW 0
# define DISPLAY 1

# define LR 0
# define TB 1

# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

# define TEXTURE_RES 64

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

# define FOV 60

typedef	struct s_raycaster
{
	float	direction[2];
	float	r_start[2];
	int		r_pos[2];
	float	length[2];
	float	step_size[2];
	float	step[2];
	float	intersect[2];
	float	final_distance;
	bool	wall_found;
	int		wall_direction;
	float		texture_perc;
}	t_raycaster;


typedef	struct s_minilx_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		offset;
	int		max_x;
	int		max_y;

}	t_minilx_img;

typedef	struct s_minilx
{
	void			*mlx;
	void			*mlx_window;
	int				screen_x;
	int				screen_y;
	t_minilx_img	mini[2];
	t_minilx_img	big[2];
}	t_minilx;

typedef	struct	s_payer
{
	float	pos[2];
	float	direct[2];
	float	plane[2];
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
	t_map_read		map_read;
	t_color			color;
	char			**map;
	int				x_max;
	int				y_max;
	char			*n_tex;
	t_minilx_img	img_n;
	char			*e_tex;
	t_minilx_img	img_e;
	char			*s_tex;
	t_minilx_img	img_s;
	char			*w_tex;
	t_minilx_img	img_w;
	char			*f_col;
	char			*c_col;
}	t_map;

typedef	struct	s_data
{
	t_map		map;
	t_player	player;
	t_raycaster	ray;
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

// minimap/draw_misc.c
void	draw_minimap_player_line(t_minilx *milx, int x_start, int x_end, int y, int color);
void	draw_minimap_player(t_minilx *milx, int color, int radius);
void	draw_minimap_border(t_minilx *milx, int color, int size);
void	draw_minimap_clear(t_minilx *milx);

// minimap/draw_tiles.c
void	draw_minimap_tiles(t_data *data, t_minilx *milx, int tile_size);

// minimap/hooks_image.c
int		draw_minimap_switch_img(void *param);
int		draw_minimap(void *param);

// mlx/hooks.c
int		finish_mlx(t_minilx *milx);
void	hooks_mlx(t_data *data);

// mlx/image.c
void	init_image(t_data *data);

// mlx/key_hooks.c
int		is_wall(t_data *data, float x, float y);
int		key_hook_ad(int keycode, void *param);
int		key_hook_ws(int keycode, void *param);
int		key_hook_esc(int keycode, void *param);
int		key_hook_esc_mac(int keycode, void *param);
int	key_hook(int keycode, void *param);

// mlx/utils.c
void	img_mlx_pixel_put(t_minilx_img *img, int x, int y, int color);
void	img_get_pixel_color(t_minilx_img *img, int x, int y, unsigned int *color);
int		create_trgb(int t, int r, int g, int b);

#endif // CUB3D_H

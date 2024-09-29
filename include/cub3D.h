/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: andmadri <andmadri@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 13:49:31 by crasche       #+#    #+#                 */
/*   Updated: 2024/09/29 18:34:50 by crasche       ########   odam.nl         */
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
# include <stdint.h>

// libft
# include "../lib/libft/include/libft.h"
// minilibx
# include "../lib/minilibx/mlx.h"

// WSL: W 119, A 97, S 115, D 100
// MAC: W 13, A 0, S 1, D 2, ESC 53
// KEY:124 KEY:125 KEY:126 KEY:123
// if (keycode == 119 || keycode == 13 || keycode == 126 || keycode == 65362)
// else if (keycode == 115 || keycode == 1 || keycode == 125 || keycode == 65364)

// KEYS
# ifndef LINUX
#  define LINUX 0
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ARROW_LEFT 123
#  define KEY_ARROW_RIGHT 124
#  define KEY_ARROW_UP 126
#  define KEY_ARROW_DOWN 125
#  define ESC 53
# define STEP_SIZE 0.06
# define TURN_STEP 0.02
# else
#  define LINUX 1
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ARROW_LEFT 65361
#  define KEY_ARROW_RIGHT 65363
#  define KEY_ARROW_UP 65362
#  define KEY_ARROW_DOWN 65364
#  define ESC 0xff1b
# define STEP_SIZE 0.1
# define TURN_STEP 0.1
# endif

# define FORWARD 1
# define BACKWARD 2
# define LEFT 3
# define RIGHT 4

# define FOV 60

// create_trgb(0, 255, 0, 0)
# define RED 16711680
// create_trgb(0, 0, 255, 0)
# define BLUE 65280
// create_trgb(0, 0, 0, 255)
# define GREEN 255
// create_trgb(0, 255, 255, 255)
# define WHITE 16777215

// MINI_MAP
# define MINI_MAP 300
# define MM_BORDER_SIZE 3
# define MM_PLAYER_SIZE 10
# define MM_TILE_SIZE 30
# define VIEW_DISTANCE 120
// create_trgb(0, 20, 80, 200)
# define MM_PLAYER_COLOR 1331400
// create_trgb(0, 55, 55, 55)
# define MM_BORDER_COLOR 3618615
// create_trgb(0, 55, 55, 55)
# define MM_WALL_COLOR 3618615
# define MM_VIEW_COLOR RED


// MLX IMAGE
# define DRAW 0
# define DISPLAY 1

# define X 0
# define Y 1

# define LR 0
# define TB 1

# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

// MATH
# define RAD 0.01745329251
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

typedef	struct s_raycaster
{
	float	direction[2];
	float	r_start[2];
	float	length[2];
	float	step_size[2];
	float	step[2];
	float	intersect[2];
	float	final_distance;
	float	texture_perc;
	float	plane_magnitude;
	float	plane_scale;
	int		r_pos[2];
	int		x;
	int		line_height;
	int		wall_direction;
	int		wall_color;
	bool	wall_found;
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

typedef	struct	s_keys
{
	bool	forward;
	bool	back;
	bool	strafe_left;
	bool	strafe_right;
	bool	turn_left;
	bool	turn_right;
	bool	exit;
}	t_keys;

typedef	struct	s_data
{
	t_map		map;
	t_player	player;
	t_raycaster	ray;
	t_minilx	milx;
	t_keys		keys;
	size_t		frame_time;
}	t_data;

// marcos
# include <errno.h>
# include <fcntl.h>
# include <errno.h>

# define DYNSTR 8
# define READBUF 1024


void	ray_caster(t_data *data, t_minilx *milx);
void	switch_img(t_data *data, t_minilx_img *img);

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
void	draw_minimap_tiles(t_data *data);

// minimap/hooks_image.c
int		draw_minimap(void *param);

// mlx/hooks.c
int		finish_mlx(t_minilx *milx);
void	hooks_mlx(t_data *data);

// mlx/image.c
void	init_image(t_data *data);

// mlx/key_hooks.c
// int		is_wall(t_data *data, float x, float y);
// int		key_hook(int keycode, void *param);

// mlx/utils.c
void			img_mlx_pixel_put(t_minilx_img *img, int x, int y, int color);
unsigned int	img_get_pixel_color(t_minilx_img *img, int x, int y);
int				create_trgb(int t, int r, int g, int b);
uint32_t		color_fraction(uint32_t c1, uint32_t c2, float fraction);

void	draw_texture(t_data *data);
void	draw_texture_line(t_data *data, int texture);


#endif // CUB3D_H

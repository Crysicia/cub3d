/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:42:21 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/09 15:59:46 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

// ERROR CODEX
#define EXTENSION_ERROR -42
#define OPEN_ERROR -43
#define READ_ERROR -44
#define ALLOCATION_ERROR -45
#define UNKNOWN_SETTING_ERROR -46
#define INVALID_SETTING_ERROR -47
#define GENERIC_ERROR -48
#define ALREADY_SET_ERROR -49
#define MAP_ERROR -50
#define STARTING_POINT_ERROR -51
#define MALFORMED_MAP_ERROR -52
#define WRITE_ERROR -53
#define ARG_ERROR -54
#define SUCCESS 42

#define X11_MAX_SIZE 20000

#define NOT_SET -256

#define FOV 1.047197551196598 // 60 * (M_PI / 180)

#define TWO_PI 6.283185307179586
#define ONE_A_HALF_PI 4.71238898038469
#define PI_180 0.017453292519943
#define WINDOW_TITLE "Cub3D"

#define UP 65362
#define W 119
#define A 97
#define S 115
#define D 100
#define DOWN 65364
#define RIGHT 65361
#define LEFT 65363
#define ESC 65307

#define WALL '1'
#define SPRITE '2'
#define PLAYER "NSEW"

#define SCREEN_WIDTH 0
#define SCREEN_HEIGHT 0

#define MAP_WIDTH 10
#define MAP_HEIGHT 25

#define WHITE 0x00FFFFFF
#define BLACK 0xFF000000
#define BLUE 0x000000FF
#define GREEN 0x0000FF00
#define RED 0x00FF0000
#define YELLOW 0x00FFFF00

#define TILE_SIZE 64

#define BMP_PATH "./saved.bmp"

typedef struct s_dib_header
{
	int header_size;
	int width;
	int height;
	short planes;
	short bits_per_pixel;
	int compression;
	int image_size;
	int horizontal_res;
	int vertical_res;
	int palette;
	int important_colors;
}				t_dib_header;

typedef struct s_bmp_pixel
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
}				t_bmp_pixel;

typedef struct s_bmp_header
{
	unsigned char signature[2];
	int size;
	int reserved;
	int image_offset;
	struct s_dib_header dib_header;
}				t_bmp_header;


typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	int			width;
	int			height;
}               t_data;

typedef struct  s_pos
{
	float x;
	float y;
}				t_pos;

typedef enum e_bool
{
	false,
	true
} 			t_bool;

typedef struct s_wall
{
	int height;
	int top;
	int bottom;
}				t_wall;

typedef struct s_sprite
{
	t_pos pos;
	t_bool is_visible;
	float distance;
	double angle;
}				t_sprite;

typedef struct s_resolution
{
	int width;
	int height;
}				t_resolution;

typedef struct s_ray
{
	t_pos wall_hit;
	float distance;
	float angle;
	int hit_north;
	int hit_south;
	int hit_east;
	int hit_west;
	int facing_up;
	int facing_left;
}				t_ray;

typedef struct s_player
{
	t_pos pos;
	int current_direction;
	int current_strafing;
	int current_rotation;
	double facing_angle;
	double move_speed;
	double rotate_speed;
}			t_player;

typedef struct s_map
{
	int width;
	int height;
	char **matrix;
	int sprites_count;
	t_sprite *sprites;
	t_player player;
}				t_map;

typedef struct	s_game
{
	t_data		img;
	void		*mlx;
	void		*win;
	t_map 		map;
	double		projection_plane;
	int			map_height;
	int			map_width;

	int			floor_color;
	int			ceiling_color;

	char *gnl_remaining;

	t_resolution resolution;
	t_data		texture[4];
	t_data		sprite_texture;
	int			sprite_alpha;
	t_ray		*rays;
}				t_game;
#endif

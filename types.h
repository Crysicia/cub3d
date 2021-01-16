/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:42:21 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/16 10:59:06 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

#define TWO_PI 6.283185307179586
#define ONE_A_HALF_PI 4.71238898038469
#define PI_180 0.017453292519943
#define UP 65362
#define DOWN 65364
#define RIGHT 65361
#define LEFT 65363
#define ESC 65307

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

#define WHITE 0x00FFFFFF
#define BLACK 0xFF000000
#define BLUE 0xFF0000FF
#define GREEN 0x0000FF00
#define RED 0x00FF0000
#define YELLOW 0x00FFFF00

#define TILE_SIZE 64
#define NUM_RAYS 640
#define FOV 1.047197551196598 // 60 * (M_PI / 180)

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
	int current_rotation;
	double facing_angle;
	double move_speed;
	double rotate_speed;
}			t_player;

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_data		texture[4];
	char		map[MAP_HEIGHT][MAP_WIDTH];
	t_player	player;
	t_ray rays[NUM_RAYS];
	double projection_plane;
}				t_game;
#endif

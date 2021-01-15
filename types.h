/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:42:21 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/15 11:51:37 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
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
#define FOV 60 * (M_PI / 180)

typedef struct s_ray
{
	float distance;
	float wall_x;
	float wall_y;
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
	float x;
	float y;
	int current_direction;
	int current_rotation;
	double facing_angle;
	double move_speed;
	double rotate_speed;
}			t_player;

typedef struct  s_pos
{
	float x;
	float y;
}				t_pos;

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
	t_data		texture;
	char		map[MAP_HEIGHT][MAP_WIDTH];
	t_player	player;
	t_ray rays[NUM_RAYS];
}				t_game;
#endif

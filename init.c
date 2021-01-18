/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:43:44 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/18 16:31:27 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include <math.h>
#include <string.h>
#include "init.h"
#include "shapes.h"
#include <limits.h>
#include "cub3d.h"


void init(t_game *game)
{
	int size;

	size = 64;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	game->img.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
		&game->img.line_length, &game->img.endian);
	game->texture[0].img = mlx_xpm_file_to_image(game->mlx, "./wall.xpm", &size, &size);
	game->texture[0].addr = mlx_get_data_addr(game->texture[0].img, &game->texture[0].bits_per_pixel,
		&game->texture[0].line_length, &game->texture[0].endian);
	game->texture[1].img = mlx_xpm_file_to_image(game->mlx, "./wood.xpm", &size, &size);
	game->texture[1].addr = mlx_get_data_addr(game->texture[1].img, &game->texture[1].bits_per_pixel,
		&game->texture[1].line_length, &game->texture[1].endian);
	game->sprite.texture.img = mlx_xpm_file_to_image(game->mlx, "./barrel.xpm", &size, &size);
	game->sprite.texture.addr = mlx_get_data_addr(game->sprite.texture.img, &game->sprite.texture.bits_per_pixel,
		&game->sprite.texture.line_length, &game->sprite.texture.endian);
	game->sprite.pos.x = 4.5;
	game->sprite.pos.y = 4.5;
	game->sprite.is_visible = false;
	init_map(game);
	init_player(game);
}

void init_map(t_game *game)
{
	char map[MAP_HEIGHT][MAP_WIDTH] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};
	memcpy(game->map, map, sizeof(char) * MAP_WIDTH * MAP_HEIGHT);
}

void init_player(t_game *game)
{
	game->player.pos.x = 128;
	game->player.pos.y = 128;
	game->player.current_direction = 0;
	game->player.current_rotation = 0;
	game->player.facing_angle = M_PI / 2;
	game->player.move_speed = 2;
	game->player.rotate_speed = 2 * (M_PI / 180);
	game->projection_plane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
}

void init_ray(t_ray *ray, float angle)
{
	ray->distance = 0;
	set_pos(&ray->wall_hit, INT_MAX, INT_MAX);
	ray->angle = normalize_angle(angle);
	ray->facing_up = 1;
	ray->facing_left = 1;
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->facing_up = 0;
	if (ray->angle < M_PI_2 || ray->angle > ONE_A_HALF_PI)
		ray->facing_left = 0;
	ray->hit_east = 0;
	ray->hit_west = 0;
	ray->hit_north = 0;
	ray->hit_south = 0;
}

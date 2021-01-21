/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:43:44 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/21 14:44:03 by lpassera         ###   ########.fr       */
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
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	game->projection_plane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
	game->num_sprites = 1;
	game->sprites = malloc(sizeof(t_sprite) * game->num_sprites);
	game->img.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
		&game->img.line_length, &game->img.endian);
	game->texture[0].img = mlx_xpm_file_to_image(game->mlx, "./wall.xpm", &game->texture[0].width, &game->texture[0].height);
	game->texture[0].addr = mlx_get_data_addr(game->texture[0].img, &game->texture[0].bits_per_pixel,
		&game->texture[0].line_length, &game->texture[0].endian);
	game->texture[1].img = mlx_xpm_file_to_image(game->mlx, "./wood.xpm", &game->texture[1].width, &game->texture[1].height);
	game->texture[1].addr = mlx_get_data_addr(game->texture[1].img, &game->texture[1].bits_per_pixel,
		&game->texture[1].line_length, &game->texture[1].endian);
	game->sprites[0].texture.img = mlx_xpm_file_to_image(game->mlx, "./pillar.xpm", &game->sprites[0].texture.width, &game->sprites[0].texture.height);
	game->sprites[0].texture.addr = mlx_get_data_addr(game->sprites[0].texture.img, &game->sprites[0].texture.bits_per_pixel,
		&game->sprites[0].texture.line_length, &game->sprites[0].texture.endian);
	game->sprites[0].pos.x = 4.5;
	game->sprites[0].pos.y = 4.5;
	// game->sprites[1].texture.img = mlx_xpm_file_to_image(game->mlx, "./barrel.xpm", &size, &size);
	// game->sprites[1].texture.addr = mlx_get_data_addr(game->sprites[1].texture.img, &game->sprites[1].texture.bits_per_pixel,
	// 	&game->sprites[1].texture.line_length, &game->sprites[1].texture.endian);
	// game->sprites[1].pos.x = 4.7;
	// game->sprites[1].pos.y = 4.7;
	game->sprites[0].is_visible = false;
	game->sprites[0].alpha = get_texture_color(&game->sprites[0].texture, &(t_pos){0, 0});
	// game->sprites[1].is_visible = false;
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
		{'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '1', '0', '0', '1', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '1', '1', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '1', '1', '1', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};
	memcpy(game->map, map, sizeof(char) * MAP_WIDTH * MAP_HEIGHT);
}

void init_player(t_game *game)
{
	game->player.pos.x = 4.5f;
	game->player.pos.y = 4.5f;
	game->player.current_direction = 0;
	game->player.current_rotation = 0;
	game->player.facing_angle = M_PI / 2;
	game->player.move_speed = 0.1;
	game->player.rotate_speed = 1.5 * (M_PI / 180);

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

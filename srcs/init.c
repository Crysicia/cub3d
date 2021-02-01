/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:43:44 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/01 16:34:09 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

#include "../includes/init.h"
#include "../includes/shapes.h"
#include "../includes/cub3d.h"

void ps(t_game *game)
{
	int i;

	i = 0;
	while (i < game->map.sprites_count)
	{
		printf("Sprites[%02i], pos(%f, %f)\n",
			i,
			game->map.sprites[i].pos.x,
			game->map.sprites[i].pos.y
		);
		i++;
	}
}

void init(t_game *game)
{
	// game->mlx = mlx_init();
	// game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "OOPS");
	// game->projection_plane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
	// if (!load_texture(game->mlx, &game->sprite_texture, "./pillar.xpm"))
	// 	return (false);
	// game->sprite_texture.img = mlx_xpm_file_to_image(game->mlx, "./textures/barrel.xpm", &game->sprite_texture.width, &game->sprite_texture.height);
	// game->sprite_texture.addr = mlx_get_data_addr(game->sprite_texture.img, &game->sprite_texture.bits_per_pixel,
	// 	&game->sprite_texture.line_length, &game->sprite_texture.endian);
	game->img.img = mlx_new_image(game->mlx, game->resolution.width, game->resolution.height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
		&game->img.line_length, &game->img.endian);
	game->img.width = 42;
	game->img.height = 42;
	// game->texture[0].img = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", &game->texture[0].width, &game->texture[0].height);
	// game->texture[0].addr = mlx_get_data_addr(game->texture[0].img, &game->texture[0].bits_per_pixel,
	// 	&game->texture[0].line_length, &game->texture[0].endian);
	// game->texture[1].img = mlx_xpm_file_to_image(game->mlx, "./textures/wood.xpm", &game->texture[1].width, &game->texture[1].height);
	// game->texture[1].addr = mlx_get_data_addr(game->texture[1].img, &game->texture[1].bits_per_pixel,
	// 	&game->texture[1].line_length, &game->texture[1].endian);

	// init_map(game);
	// init_player(game);
	// init_all_sprites(game);
	// ps(game);
	// game->sprite_alpha = get_texture_color(&game->sprite_texture, &(t_pos){0, 0});
}

void init_player(t_game *game)
{
	game->map.player.pos.x = -1;
	game->map.player.pos.y = -1;
	game->map.player.current_direction = 0;
	game->map.player.current_rotation = 0;
	game->map.player.facing_angle = M_PI / 2;
	game->map.player.move_speed = 0.1;
	game->map.player.rotate_speed = 1.5 * (M_PI / 180);

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

t_bool init_rays(t_game *game)
{
	game->rays = malloc(sizeof(t_ray) * game->resolution.width);
	if (!game->rays)
		return (false);
	return (true);
}

void init_sprite(t_sprite *sprite, float x, float y)
{
	set_pos(&sprite->pos, x, y);
	sprite->is_visible = true;
	sprite->distance = 0;
	sprite->angle = 0;
}

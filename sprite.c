/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:02:52 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/20 16:49:27 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "cub3d.h"
#include "shapes.h"

t_bool is_in_fov(double player_angle, double angle)
{
	float fov_start;
	float fov_end;

	fov_start = player_angle - ( 80 * (M_PI / 180) / 2); 
	fov_end = player_angle + (80 *  (M_PI / 180) / 2); 
	if (fov_start <= angle && fov_end >= angle)
		return (true);
	return (false);
}

void update_sprite_visibility(t_player *player, t_sprite *sprite)
{
	double sprite_angle;
	t_pos relative_pos;

	set_pos(&relative_pos, sprite->pos.x - player->pos.x, sprite->pos.y - player->pos.y);
	sprite_angle = normalize_angle(atan2(relative_pos.y, relative_pos.x));
	sprite->angle = sprite_angle;
	sprite->distance = sqrt(pow(sprite->pos.x - player->pos.x, 2) + pow(sprite->pos.y - player->pos.y, 2));
	if (is_in_fov(player->facing_angle, sprite_angle))
		sprite->is_visible = true;
	else
		sprite->is_visible = false;
}

void render_sprite(t_game *game, t_sprite *sprite)
{
	// int height;
	// int top;
	// int bottom;
	// int x;

	// int draw_x;
	// int draw_y;
	// t_pos offset;

	// height = game->projection_plane / cos(sprite->angle) * sprite->distance;
	// top = (SCREEN_HEIGHT / 2) - (height / 2);
	// if (top < 0)
	// 	top = 0;
	// bottom = (SCREEN_HEIGHT / 2) + (height / 2);
	// if (bottom > SCREEN_HEIGHT)
	// 	bottom = SCREEN_HEIGHT;
	// x = game->projection_plane * tan(sprite->angle) + (SCREEN_WIDTH / 2.0) - (height / 2);
	// int y = top;
	// while (x < height / 2)
	// {
	// 	offset.x = fmod(x, 1.0f) * 64.0;
	// 	while (y < bottom)
	// 	{
	// 		int distance_from_top = y + (height / 2) - (SCREEN_HEIGHT / 2);
	// 		offset.y = distance_from_top * (64.0f / height);
	// 		my_mlx_pixel_put(&game->img, x, y, get_texture_color(&sprite->texture, &offset));
	// 		y++;
	// 	}
	// 	x++;
	// }

	int height;
	int top;
	int bottom;
	int x;
	int y;
	int draw_x;
	int draw_y;

	t_pos offset;

	height = game->projection_plane / (cos(sprite->angle - game->player.facing_angle) * sprite->distance);
	top = (SCREEN_HEIGHT / 2) - (height / 2);
	if (top < 0)
		top = 0;
	bottom = (SCREEN_HEIGHT / 2) + (height / 2);
	if (bottom > SCREEN_HEIGHT)
		bottom = SCREEN_HEIGHT;
	x = game->projection_plane * tan(sprite->angle - game->player.facing_angle) + ((SCREEN_WIDTH / 2.0) - (height / 2));
	if (x < 0)
		x = 0;
	if (x > SCREEN_WIDTH)
		x = 0;

	y = top;
	printf("Sprite: x:%i, y:%i, distance:%f, height:%i, angle:%f\n", x, y, sprite->distance, height, sprite->angle);
	draw_x = 0;
	while (draw_x < height && draw_x + x < SCREEN_WIDTH)
	{
		draw_y = 0;
		while (draw_y < height && draw_y + y < SCREEN_HEIGHT)
		{
			if (draw_y == 0 || draw_x == 0 || draw_y == height - 1 || draw_x == height - 1)
				my_mlx_pixel_put(&game->img, draw_x + x, draw_y + y, WHITE);
			draw_y++;
		}
		draw_x++;
	}
}

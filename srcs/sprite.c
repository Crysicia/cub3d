/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:02:52 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/30 00:37:41 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "../includes/cub3d.h"
#include "../includes/shapes.h"

t_bool is_in_fov(double player_angle, double angle)
{
	float fov_start;
	float fov_end;

	fov_start = player_angle - (80 * (M_PI / 180) / 2);
	fov_end = player_angle + (80 *  (M_PI / 180) / 2);
	// printf("Fov: %f-%f, Sprite angle: %f\n", fov_start, fov_end, angle);
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
	sprite->distance = pos_distance(&player->pos, &sprite->pos);
	if (is_in_fov(player->facing_angle, sprite_angle))
		sprite->is_visible = true;
	else
		sprite->is_visible = false;
}

void sort_sprites(t_game *game)
{
	t_sprite temp;
	t_bool sorted;
	int i;

	sorted = false;
	while (!sorted)
	{
		sorted = true;
		i = 0;
		while (i < game->map2.sprites_count - 1)
		{
			if (game->map2.sprites[i].distance < game->map2.sprites[i + 1].distance)
			{
				temp = game->map2.sprites[i];
				game->map2.sprites[i] = game->map2.sprites[i + 1];
				game->map2.sprites[i + 1] = temp;
				sorted = false;
			}
			i++;
		}
	}
}

void render_sprite(t_game *game, t_sprite *sprite)
{
	int height;
	int top;
	int bottom;
	int x;
	int y;
	int draw_x;
	int draw_y;

	t_pos offset;

	height = game->projection_plane / (cos(sprite->angle - game->map2.player.facing_angle) * sprite->distance);
	top = (game->resolution.height / 2) - (height / 2);
	if (top < 0)
		top = 0;
	bottom = (game->resolution.height / 2) + (height / 2);
	if (bottom > game->resolution.height)
		bottom = game->resolution.height;
	x = game->projection_plane * tan(sprite->angle - game->map2.player.facing_angle) + ((game->resolution.width / 2.0) - (height / 2));
	if (x > game->resolution.width)
		x = game->resolution.width;
	y = top;
	// printf("Sprite: x:%i, y:%i, distance:%f, height:%i, angle:%f\n", x, y, sprite->distance, height, sprite->angle);
	draw_x = x < 0 ? -x : 0;
	while (draw_x < height && draw_x + x < game->resolution.width)
	{
		offset.x = draw_x * (float)game->sprite_texture.width / height;
		draw_y = 0;
		while (draw_y < height && draw_y + y < game->resolution.height)
		{
			offset.y = (draw_y + y + (height / 2) - (game->resolution.height / 2)) * ((float)game->sprite_texture.height / height);
			int color = get_texture_color(&game->sprite_texture, &offset);
			if (game->rays[draw_x + x].distance > sprite->distance && color != game->sprite_alpha)
				my_mlx_pixel_put(&game->img, draw_x + x, draw_y + y, color);
			draw_y++;
		}
		draw_x++;
	}
}

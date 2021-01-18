/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:02:52 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/18 15:42:48 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

t_bool is_in_fov(double player_angle, double angle)
{
	float fov_start;
	float fov_end;

	fov_start = player_angle - (FOV / 2); 
	fov_end = player_angle + (FOV / 2); 
	if (fov_start <= angle && fov_end >= angle)
		return (true);
	return (false);
}

void update_sprite_visibility(t_player *player, t_sprite *sprite)
{
	double sprite_angle;
	t_pos relative_pos;

	set_pos(&relative_pos, sprite->pos.x - pixel2coord(player->pos.x),
			sprite->pos.y - pixel2coord(player->pos.y));
	sprite_angle = normalize_angle(atan2(relative_pos.y, relative_pos.x));
	sprite->angle = sprite_angle;
	sprite->distance = sqrt(pow(sprite->pos.x - (player->pos.x / 64.0), 2)
		+ pow(sprite->pos.y - (player->pos.y / 64.0), 2));
	if (is_in_fov(player->facing_angle, sprite_angle))
		sprite->is_visible = true;
	else
		sprite->is_visible = false;
}

void render_sprite(t_game *game, t_sprite *sprite)
{
	int height;
	int top;
	int bottom;

	height = sprite->distance * cos(sprite->angle, - game->player.facing_angle) * game->projection_plane;
	top = (SCREEN_HEIGHT / 2) - (height / 2);
	if (top < 0)
		top = 0;
	bottom = (SCREEN_HEIGHT / 2) + (height / 2);
	if (bottom > SCREEN_HEIGHT)
		bottom = SCREEN_HEIGHT;

}

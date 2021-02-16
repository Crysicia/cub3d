/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:02:52 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/16 10:45:11 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_all_sprites(t_game *game)
{
	int i;

	i = -1;
	if (game->map.sprites_count <= 0)
		return ;
	while (++i < game->map.sprites_count)
		update_sprite_visibility(&game->map.player, &game->map.sprites[i]);
	sort_sprites(game);
	i = -1;
	while (++i < game->map.sprites_count)
		if (game->map.sprites[i].is_visible
			&& game->map.sprites[i].distance > 0.2f)
			render_sprite(game, &game->map.sprites[i]);
}

t_bool	is_in_fov(double player_angle, double angle)
{
	angle = angle - player_angle;
	if (angle < -M_PI)
		angle += 2 * M_PI;
	if (angle >= M_PI)
		angle -= 2 * M_PI;
	if (fabs(angle) < FOV / 1.5)
		return (true);
	return (false);
}

void	update_sprite_visibility(t_player *player, t_sprite *sprite)
{
	double	sprite_angle;
	t_pos	relative_pos;

	set_pos(&relative_pos, sprite->pos.x - player->pos.x,
							sprite->pos.y - player->pos.y);
	sprite_angle = normalize_angle(atan2(relative_pos.y, relative_pos.x));
	sprite->angle = sprite_angle;
	sprite->distance = pos_distance(&player->pos, &sprite->pos);
	if (is_in_fov(player->facing_angle, sprite_angle))
		sprite->is_visible = true;
	else
		sprite->is_visible = false;
}

void	render_sprite(t_game *game, t_sprite *sprite)
{
	t_point			c;
	t_point			d;
	t_bounds		bounds;
	int				color;
	t_pos			offset;

	compute_boundaries(game, sprite->angle, sprite->distance, &bounds);
	set_sprite_coords(game, sprite, &c, &bounds);
	set_sprite_draw(&d, &c);
	while (++d.x < bounds.height && d.x + c.x < game->resolution.width)
	{
		offset.x = d.x * (float)game->sprite_texture.width / bounds.height;
		d.y = -1;
		while (++d.y < bounds.height && d.y + c.y < game->resolution.height)
		{
			offset.y = (d.y + c.y + (bounds.height / 2)
				- (game->resolution.height / 2))
				* ((float)game->sprite_texture.height / bounds.height);
			color = get_texture_color(&game->sprite_texture, &offset);
			if (game->rays[d.x + c.x].distance > sprite->distance
										&& color != game->sprite_alpha)
				my_mlx_pixel_put(&game->img, d.x + c.x, d.y + c.y, color);
		}
	}
}

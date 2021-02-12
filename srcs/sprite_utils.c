/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:40:43 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/12 16:42:58 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sort_sprites(t_game *game)
{
	t_sprite	current_sprite;
	t_bool		sorted;
	int			i;

	sorted = false;
	while (!sorted)
	{
		sorted = true;
		i = 0;
		while (i < game->map.sprites_count - 1)
		{
			current_sprite = game->map.sprites[i];
			if (current_sprite.distance < game->map.sprites[i + 1].distance)
			{
				game->map.sprites[i] = game->map.sprites[i + 1];
				game->map.sprites[i + 1] = current_sprite;
				sorted = false;
			}
			i++;
		}
	}
}

void	set_sprite_coords(t_game *game, t_sprite *sprite,
						t_point *coords, t_bounds *bounds)
{
	coords->x = game->projection_plane
				* tan(sprite->angle - game->map.player.facing_angle)
				+ ((game->resolution.width / 2.0) - (bounds->height / 2));
	if (coords->x > game->resolution.width)
		coords->x = game->resolution.width;
	coords->y = bounds->top;
}

void	set_sprite_draw(t_point *draw, t_point *coords)
{
	draw->x = -1;
	if (coords->x < 0)
		draw->x = -coords->x - 1;
}

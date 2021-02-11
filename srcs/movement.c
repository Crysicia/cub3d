/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:57:42 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/11 17:01:32 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_bool	has_wall_at(t_game *game, float x, float y)
{
	int ix;
	int iy;

	ix = floor(x);
	iy = floor(y);
	if (ix < 0 || iy < 0 || iy >= game->map.height
		|| (unsigned int)ix >= ft_strlen(game->map.matrix[iy]))
		return (true);
	return (game->map.matrix[iy][ix] == '1');
}

void	move_collisions(t_game *game, t_pos *coords)
{
	if (!has_wall_at(game, coords->x, game->map.player.pos.y))
		set_pos(&game->map.player.pos, coords->x, game->map.player.pos.y);
	if (!has_wall_at(game, game->map.player.pos.x, coords->y))
		set_pos(&game->map.player.pos, game->map.player.pos.x, coords->y);
}

void	get_next_player_pos(t_game *game, t_bool strafing, t_pos *coords)
{
	float strafing_angle;
	float distance;

	strafing_angle = M_PI / 2;
	if (!strafing)
	{
		game->map.player.facing_angle = normalize_angle(
			game->map.player.facing_angle + game->map.player.current_rotation
			* game->map.player.rotate_speed);
		distance = game->map.player.current_direction
					* game->map.player.move_speed;
		strafing_angle = 0;
	}
	else
		distance = game->map.player.current_strafing
					* game->map.player.move_speed;
	coords->x = game->map.player.pos.x + cos(game->map.player.facing_angle
					+ strafing_angle) * distance;
	coords->y = game->map.player.pos.y + sin(game->map.player.facing_angle
					+ strafing_angle) * distance;
}

void	move_player(t_game *game)
{
	t_pos coords;

	get_next_player_pos(game, true, &coords);
	move_collisions(game, &coords);
	get_next_player_pos(game, false, &coords);
	move_collisions(game, &coords);
}

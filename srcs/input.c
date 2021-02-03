/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:19:40 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/03 12:07:22 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../mlx/mlx.h"
#include "../includes/input.h"
#include "../includes/debug.h"
#include "../includes/cub3d.h"

int key_released(int keycode, t_game *game)
{
	if (keycode == UP || keycode == W)
		game->map.player.current_direction = 0;
	else if (keycode == DOWN || keycode == S)
		game->map.player.current_direction = 0;
	else if (keycode == RIGHT)
		game->map.player.current_rotation = 0;
	else if (keycode == LEFT)
		game->map.player.current_rotation = 0;
	else if (keycode == A)
		game->map.player.current_strafing = 0;
	else if (keycode == D)
		game->map.player.current_strafing = 0;
}


int key_pressed(int keycode, t_game *game)
{
	if (keycode == ESC)
		clean_exit(game, SUCCESS);
	else if (keycode == UP || keycode == W)
		game->map.player.current_direction = 1;
	else if (keycode == DOWN || keycode == S)
		game->map.player.current_direction = -1;
	else if (keycode == A)
		game->map.player.current_strafing = -1;
	else if (keycode == D)
		game->map.player.current_strafing = 1;
	else if (keycode == RIGHT)
		game->map.player.current_rotation = -1;
	else if (keycode == LEFT)
		game->map.player.current_rotation = 1;
}

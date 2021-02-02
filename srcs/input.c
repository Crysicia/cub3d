/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:19:40 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/02 16:04:38 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../mlx/mlx.h"
#include "../includes/input.h"
#include "../includes/debug.h"
#include "../includes/cub3d.h"

int key_released(int keycode, t_game *game)
{
	if (keycode == UP)
		game->map.player.current_direction = 0;
	else if (keycode == DOWN)
		game->map.player.current_direction = 0;
	else if (keycode == RIGHT)
		game->map.player.current_rotation = 0;
	else if (keycode == LEFT)
		game->map.player.current_rotation = 0;
}


int key_pressed(int keycode, t_game *game)
{
	if (keycode == ESC)
		clean_exit(game, SUCCESS);
	else if (keycode == UP)
		game->map.player.current_direction = 1;
	else if (keycode == DOWN)
		game->map.player.current_direction = -1;
	else if (keycode == RIGHT)
		game->map.player.current_rotation = -1;
	else if (keycode == LEFT)
		game->map.player.current_rotation = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:19:40 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/18 14:57:52 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "input.h"
#include "debug.h"
#include "mlx/mlx.h"
#include "cub3d.h"

int key_released(int keycode, t_game *game)
{
	if (keycode == UP)
		game->player.current_direction = 0;
	else if (keycode == DOWN)
		game->player.current_direction = 0;
	else if (keycode == RIGHT)
		game->player.current_rotation = 0;
	else if (keycode == LEFT)
		game->player.current_rotation = 0;
}


int key_pressed(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(game->mlx, game->img.img);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(0);
	}
	else if (keycode == UP)
		game->player.current_direction = 1;
	else if (keycode == DOWN)
		game->player.current_direction = -1;
	else if (keycode == RIGHT)
		game->player.current_rotation = -1;
	else if (keycode == LEFT)
		game->player.current_rotation = 1;
	else if (keycode == 'a')
		printf("Angle: %f\n", game->player.facing_angle);
	else if (keycode == 's')
		printf("-----\nSprite at %f:%f: %s\nFOV: %f-%f\nANGLE: %f\nDistance: %f\n",
			game->sprite.pos.x,
			game->sprite.pos.y,
			game->sprite.is_visible ? "VISIBLE" : "HIDDEN",
			game->player.facing_angle - (FOV / 2),
			game->player.facing_angle + (FOV / 2),
			game->sprite.angle,
			game->sprite.distance
		);
	else
		print_infos(game);
}

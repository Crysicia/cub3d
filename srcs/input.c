/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:19:40 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/30 00:05:44 by lpassera         ###   ########.fr       */
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
		game->map2.player.current_direction = 0;
	else if (keycode == DOWN)
		game->map2.player.current_direction = 0;
	else if (keycode == RIGHT)
		game->map2.player.current_rotation = 0;
	else if (keycode == LEFT)
		game->map2.player.current_rotation = 0;
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
		game->map2.player.current_direction = 1;
	else if (keycode == DOWN)
		game->map2.player.current_direction = -1;
	else if (keycode == RIGHT)
		game->map2.player.current_rotation = -1;
	else if (keycode == LEFT)
		game->map2.player.current_rotation = 1;
	// else if (keycode == 'a')
	// 	printf("Angle: %f\n", game->map2.player.facing_angle);
	// else
	// 	print_infos(game);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:19:40 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/12 12:00:04 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_released(int keycode, t_game *game)
{
	if (keycode == UP || keycode == W || keycode == DOWN || keycode == S)
		game->map.player.current_direction = 0;
	else if (keycode == RIGHT || keycode == LEFT)
		game->map.player.current_rotation = 0;
	else if (keycode == A || keycode == D)
		game->map.player.current_strafing = 0;
	return (1);
}

int		key_pressed(int keycode, t_game *game)
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
	return (1);
}

int		close_window(t_game *game)
{
	clean_exit(game, SUCCESS);
	return (1);
}

void	bind_hooks(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, key_pressed, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_released, game);
	mlx_hook(game->win, ClientMessage, StructureNotifyMask, close_window, game);
	mlx_loop_hook(game->mlx, main_loop, game);
	mlx_loop(game->mlx);
}

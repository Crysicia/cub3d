/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 10:37:29 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/13 10:39:06 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_bool	init_rays(t_game *game)
{
	game->rays = malloc(sizeof(t_ray) * game->resolution.width);
	if (!game->rays)
		return (false);
	return (true);
}

void	nullify_texture(t_data *texture)
{
	texture->img = NULL;
	texture->addr = NULL;
}

void	nullify_settings(t_game *game)
{
	nullify_texture(&game->img);
	nullify_texture(&game->texture[0]);
	nullify_texture(&game->texture[1]);
	nullify_texture(&game->texture[2]);
	nullify_texture(&game->texture[3]);
	nullify_texture(&game->sprite_texture);
	game->floor_color = NOT_SET;
	game->ceiling_color = NOT_SET;
	game->resolution.width = NOT_SET;
	game->resolution.height = NOT_SET;
	game->map.matrix = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.sprites_count = 0;
	game->map.sprites = NULL;
	game->win = NULL;
	game->rays = NULL;
	game->gnl_remaining = NULL;
}

void	adjust_screen_size(t_game *game, int save_flag)
{
	t_resolution screen_size;

	mlx_get_screen_size(game->mlx, &screen_size.width, &screen_size.height);
	if (!save_flag)
	{
		if (screen_size.width < game->resolution.width)
			game->resolution.width = screen_size.width;
		if (screen_size.height < game->resolution.height)
			game->resolution.height = screen_size.height;
	}
	else
	{
		if (game->resolution.width > X11_MAX_SIZE)
			game->resolution.width = X11_MAX_SIZE;
		if (game->resolution.height > X11_MAX_SIZE)
			game->resolution.height = X11_MAX_SIZE;
	}
}

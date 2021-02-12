/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:06:19 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/12 11:52:04 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

#include "../includes/init.h"
#include "../includes/debug.h"
#include "../includes/input.h"
#include "../includes/cub3d.h"

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

t_bool	init_settings(t_game *game)
{
	nullify_settings(game);
	init_player(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	return (true);
}

void	draw_column(t_data *img, int color, int column, int start, int end)
{
	while (start <= end)
	{
		my_mlx_pixel_put(img, column, start, color);
		start++;
	}
}

void	render_3d_walls(t_game *game)
{
	t_wall	wall;
	t_ray	ray;
	int		i;
	t_data *texture;

	i = 0;
	while (i < game->resolution.width)
	{
		ray = game->rays[i];
		texture = get_texture(game, &ray);
		compute_wall_boundaries(game, &ray, &wall);
		draw_column(&game->img, game->ceiling_color, i, 0, wall.top);
		render_texture_strip(game, texture, &wall, i);
		draw_column(&game->img, game->floor_color, i, wall.bottom, game->resolution.height);
		i++;
	}
}

int		main_loop(t_game *game)
{
	move_player(game);
	cast_rays(game);
	render_3d_walls(game);
	render_all_sprites(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (1);
}


int		main(int argc, char *argv[])
{
	t_game	game;
	int		ret;
	int		save;

	save = 0;
	if (argc == 2 || argc == 3)
	{
		if (argc == 3)
		{
			if (ft_strncmp(argv[1], "--save", 6) == 0)
				save = 1;
			else
			{
				print_error(ARG_ERROR);
				exit(0);
			}
		}
		if (!init_settings(&game)
			|| parse_file(&game, argv[1 + save], &ret) != SUCCESS
			|| init(&game, &ret, save) != SUCCESS)
			clean_exit(&game, ret);
		if (save)
			clean_exit(&game, save_image(&game));
		bind_hooks(&game);
	}
	else
		print_error(ARG_ERROR);
	exit(0);
}

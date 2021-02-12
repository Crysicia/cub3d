/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:06:19 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/12 17:05:20 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

#include "../includes/input.h"
#include "../includes/cub3d.h"

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
	t_bounds	wall;
	t_ray		ray;
	int			i;
	t_data		*texture;

	i = 0;
	while (i < game->resolution.width)
	{
		ray = game->rays[i];
		texture = get_texture(game, &ray);
		compute_boundaries(game, ray.angle, ray.distance, &wall);
		draw_column(&game->img, game->ceiling_color, i, 0, wall.top);
		render_texture_strip(game, texture, &wall, i);
		draw_column(&game->img, game->floor_color, i,
				wall.bottom, game->resolution.height);
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

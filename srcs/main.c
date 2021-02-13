/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:06:19 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/13 14:46:39 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_3d_walls(t_game *game)
{
	t_bounds	wall;
	t_ray		ray;
	int			i;
	t_data		*texture;
	int			x;

	i = 0;
	while (i < game->resolution.width)
	{
		x = -1;
		ray = game->rays[i];
		texture = get_texture(game, &ray);
		compute_boundaries(game, ray.angle, ray.distance, &wall);
		while (++x <= wall.top)
			my_mlx_pixel_put(&game->img, i, x, game->ceiling_color);
		render_texture_strip(game, texture, &wall, i);
		x = wall.bottom - 1;
		while (++x < game->resolution.height)
			my_mlx_pixel_put(&game->img, i, x, game->floor_color);
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
			save = (ft_strncmp(argv[1], "--save", 6) == 0);
		if (argc == 3 && !save)
		{
			printf("Error\
				\nInvalid arguments\nUsage: ./Cub3D [--save] path_to_map\n");
			exit(0);
		}
		if (!init_settings(&game)
			|| parse_file(&game, argv[1 + save], &ret) != SUCCESS
			|| init(&game, &ret, save) != SUCCESS)
			clean_exit(&game, ret);
		if (save)
			clean_exit(&game, save_image(&game));
		bind_hooks(&game);
	}
	printf("Error\nInvalid arguments\nUsage: ./Cub3D [--save] path_to_map\n");
	exit(0);
}

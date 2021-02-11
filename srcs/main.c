#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <X11/X.h>

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
	t_pos	offset;
	t_wall	wall;
	t_ray	ray;
	int		i;
	int		t;

	i = 0;
	while (i < game->resolution.width)
	{
		ray = game->rays[i];
		compute_wall_boundaries(game, &ray, &wall);
		if (ray.hit_north)
		{
			t = 0;
			offset.x = fmod(ray.wall_hit.x, 1.0f) * (float)game->texture[t].width;
		}
		else if (ray.hit_east)
		{
			t = 1;
			offset.x = fmod(ray.wall_hit.y, 1.0f) * (float)game->texture[t].width;
		}
		else if (ray.hit_south)
		{
			t = 2;
			offset.x = fmod(ray.wall_hit.x, 1.0f) * (float)game->texture[t].width;
		}
		else
		{
			t = 3;
			offset.x = fmod(ray.wall_hit.y, 1.0f) * (float)game->texture[t].width;
		}
		draw_column(&game->img, game->ceiling_color, i, 0, wall.top);
		render_texture_strip(game, &game->texture[t], &wall, &offset, i);
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

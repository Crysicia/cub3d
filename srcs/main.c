#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <X11/X.h>

#include "../includes/shapes.h"
#include "../includes/init.h"
#include "../includes/debug.h"
#include "../includes/input.h"
#include "../includes/cub3d.h"

void nullify_texture(t_data *texture)
{
	texture->img = NULL;
	texture->addr = NULL;
}

void nullify_settings(t_game *game)
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

t_bool init_settings(t_game *game)
{
	nullify_settings(game);
	init_player(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	return (true);
}

int draw_map(t_game *game)
{
	int x;
	int y;
	int color;

	x = 0;
	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{
			color = (game->map.matrix[x][y] == '1') ? BLACK : WHITE;
			draw_square(&game->img, color, TILE_SIZE, y * TILE_SIZE, x * TILE_SIZE);
			y++;
		}
		x++;
	}
}

int draw_player(t_game *game)
{
	draw_circle(&game->img, 10, game->map.player.pos.x, game->map.player.pos.y);
	draw_line(&game->img, 0x0000FF00, game->map.player.pos.x,
		game->map.player.pos.y,
		game->map.player.pos.x + cos(game->map.player.facing_angle) * 20,
		game->map.player.pos.y + sin(game->map.player.facing_angle) * 20);
}

void render_rays(t_game *game)
{
	int i;

	i = 0;
	while (i < game->resolution.width)
	{
		draw_line(
			&game->img,
			0x000000FF,
			game->map.player.pos.x,
			game->map.player.pos.y,
			game->rays[i].wall_hit.x,
			game->rays[i].wall_hit.y
		);
		i++;
	}
}

void render_3d_walls(t_game *game)
{
	t_pos offset;
	t_wall wall;
	t_ray ray;
	int i;
	int t;

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
		draw_line(&game->img, BLUE, i, 0, i, wall.top);
		render_texture_strip(game, &game->texture[t], &wall, &offset, i);
		draw_line(&game->img, BLACK, i, wall.bottom, i, game->resolution.height);
		i++;
	}
}

t_bool has_wall_at(t_game *game, float x, float y)
{
	int ix;
	int iy;

	ix = floor(x);
	iy = floor(y);
	if (ix < 0 || iy < 0 || iy >= game->map.height || ix >= ft_strlen(game->map.matrix[iy]))
		return (true);
	return (game->map.matrix[iy][ix] == '1');
}

int main_loop(t_game *game)
{
	float hypotenus;
	float x;
	float y;
	int i;

	game->map.player.facing_angle = normalize_angle(game->map.player.facing_angle + game->map.player.current_rotation * game->map.player.rotate_speed);
	hypotenus = game->map.player.current_direction * game->map.player.move_speed;
	x = game->map.player.pos.x + cos(game->map.player.facing_angle) * hypotenus;
	y = game->map.player.pos.y + sin(game->map.player.facing_angle) * hypotenus;
	if (!has_wall_at(game, x, game->map.player.pos.y))
		set_pos(&game->map.player.pos, x, game->map.player.pos.y);
	if (!has_wall_at(game, game->map.player.pos.x, y))
		set_pos(&game->map.player.pos, game->map.player.pos.x, y);
	cast_rays(game);
	// draw_map(game);
	// render_rays(game);
	// draw_player(game);
	render_3d_walls(game);
	i = 0;
	while (i < game->map.sprites_count)
	{
		update_sprite_visibility(&game->map.player, &game->map.sprites[i]);
		i++;
	}
	if (game->map.sprites_count > 0)
		sort_sprites(game);
	i = 0;
	while (i < game->map.sprites_count)
	{
		if (game->map.sprites[i].is_visible)
			render_sprite(game, &game->map.sprites[i]);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int             main(int argc, char *argv[])
{
	(void)	argc;
	(void)	argv;
	t_game  game;
	int ret;

	if (!init_settings(&game)
		|| parse_file(&game, argv[1], &ret) != SUCCESS
		|| init(&game, &ret) != SUCCESS)
		clean_exit(&game, ret);
	else
	{
		printf(
			"Settings:\n- Resolution [%i, %i]\n- Ceiling [%i]\n- Floor [%i]\n",
			game.resolution.width,
			game.resolution.height,
			game.ceiling_color,
			game.floor_color
		);
		display_map(&game.map);
	}
	mlx_hook(game.win, KeyPress, KeyPressMask, key_pressed, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_released, &game);
	mlx_loop_hook(game.mlx, main_loop, &game);
	mlx_loop(game.mlx);
}

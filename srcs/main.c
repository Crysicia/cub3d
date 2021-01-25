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
			color = (game->map[x][y] == '1') ? BLACK : WHITE;
			draw_square(&game->img, color, TILE_SIZE, y * TILE_SIZE, x * TILE_SIZE);
			y++;
		}
		x++;
	}
}

int draw_player(t_game *game)
{
	draw_circle(&game->img, 10, game->player.pos.x, game->player.pos.y);
	draw_line(&game->img, 0x0000FF00, game->player.pos.x,
		game->player.pos.y,
		game->player.pos.x + cos(game->player.facing_angle) * 20,
		game->player.pos.y + sin(game->player.facing_angle) * 20);
}

void render_rays(t_game *game)
{
	int i;

	i = 0;
	while (i < NUM_RAYS)
	{
		draw_line(
			&game->img,
			0x000000FF,
			game->player.pos.x,
			game->player.pos.y,
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
	while (i < NUM_RAYS)
	{
		ray = game->rays[i];
		compute_wall_boundaries(game, &ray, &wall);
		if (ray.hit_east || ray.hit_west)
		{
			t = 0;
			offset.x = fmod(ray.wall_hit.y, 1.0f) * (float)game->texture[t].width;
		}
		else
		{
			t = 1;
			offset.x = fmod(ray.wall_hit.x, 1.0f) * (float)game->texture[t].width;
		}
		draw_line(&game->img, BLUE, i, 0, i, wall.top);
		render_texture_strip(&game->img, &game->texture[t], &wall, &offset, i);
		draw_line(&game->img, BLACK, i, wall.bottom, i, SCREEN_HEIGHT);
		i++;
	}
}

t_bool has_wall_at(t_game *game, float x, float y)
{
	int ix;
	int iy;

	ix = floor(x);
	iy = floor(y);
	if (ix < 0 || iy < 0 || ix > MAP_WIDTH || iy > MAP_HEIGHT)
		return (true);
	return (game->map[iy][ix] == '1');
}

int main_loop(t_game *game)
{
	float hypotenus;
	float x;
	float y;
	int i;

	game->player.facing_angle = normalize_angle(game->player.facing_angle + game->player.current_rotation * game->player.rotate_speed);
	hypotenus = game->player.current_direction * game->player.move_speed;
	x = game->player.pos.x + cos(game->player.facing_angle) * hypotenus;
	y = game->player.pos.y + sin(game->player.facing_angle) * hypotenus;
	if (!has_wall_at(game, x, game->player.pos.y))
		set_pos(&game->player.pos, x, game->player.pos.y);
	if (!has_wall_at(game, game->player.pos.x, y))
		set_pos(&game->player.pos, game->player.pos.x, y);
	cast_rays(game);
	// draw_map(game);
	// render_rays(game);
	// draw_player(game);
	render_3d_walls(game);
	i = 0;
	while (i < game->num_sprites)
	{
		update_sprite_visibility(&game->player, &game->sprites[i]);
		i++;
	}
	if (game->num_sprites > 0)
		sort_sprites(game);
	i = 0;
	while (i < game->num_sprites)
	{
		if (game->sprites[i].is_visible)
			render_sprite(game, &game->sprites[i]);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	display_infos(game);
}

int             main(int argc, char *argv[])
{
	(void)	argc;
	(void)	argv;
	t_game  game;
	char **split;

	split = ft_split_set("    125,      452,,,,,, 12", ", ");
	int i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	init(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_pressed, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_released, &game);
	mlx_loop_hook(game.mlx, main_loop, &game);
	mlx_loop(game.mlx);
}

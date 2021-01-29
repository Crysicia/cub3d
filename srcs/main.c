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
	draw_circle(&game->img, 10, game->map2.player.pos.x, game->map2.player.pos.y);
	draw_line(&game->img, 0x0000FF00, game->map2.player.pos.x,
		game->map2.player.pos.y,
		game->map2.player.pos.x + cos(game->map2.player.facing_angle) * 20,
		game->map2.player.pos.y + sin(game->map2.player.facing_angle) * 20);
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
			game->map2.player.pos.x,
			game->map2.player.pos.y,
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
		render_texture_strip(&game, &game->texture[t], &wall, &offset, i);
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
	if (ix < 0 || iy < 0 || iy > game->map2.height || ix > ft_strlen(game->map2.matrix[iy]))
		return (true);
	return (game->map2.matrix[iy][ix] == '1');
}

int main_loop(t_game *game)
{
	float hypotenus;
	float x;
	float y;
	int i;

	game->map2.player.facing_angle = normalize_angle(game->map2.player.facing_angle + game->map2.player.current_rotation * game->map2.player.rotate_speed);
	hypotenus = game->map2.player.current_direction * game->map2.player.move_speed;
	x = game->map2.player.pos.x + cos(game->map2.player.facing_angle) * hypotenus;
	y = game->map2.player.pos.y + sin(game->map2.player.facing_angle) * hypotenus;
	if (!has_wall_at(game, x, game->map2.player.pos.y))
		set_pos(&game->map2.player.pos, x, game->map2.player.pos.y);
	if (!has_wall_at(game, game->map2.player.pos.x, y))
		set_pos(&game->map2.player.pos, game->map2.player.pos.x, y);
	cast_rays(game);
	// draw_map(game);
	// render_rays(game);
	// draw_player(game);
	render_3d_walls(game);
	i = 0;
	while (i < game->map2.sprites_count)
	{
		update_sprite_visibility(&game->map2.player, &game->map2.sprites[i]);
		i++;
	}
	if (game->map2.sprites_count > 0)
		sort_sprites(game);
	i = 0;
	while (i < game->map2.sprites_count)
	{
		if (game->map2.sprites[i].is_visible)
			render_sprite(game, &game->map2.sprites[i]);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void init_settings(t_game *game)
{
	game->texture[0].img = NULL;
	game->texture[0].addr = NULL;
	game->texture[1].img = NULL;
	game->texture[1].addr = NULL;
	game->texture[2].img = NULL;
	game->texture[2].addr = NULL;
	game->texture[3].img = NULL;
	game->texture[3].addr = NULL;
	game->sprite_texture.addr = NULL;
	game->floor_color = NOT_SET;
	game->ceiling_color = NOT_SET;
	game->resolution.width = NOT_SET;
	game->resolution.height = NOT_SET;

	game->map2.matrix = NULL;
	game->map2.width = 0;
	game->map2.height = 0;
	game->map2.sprites_count = 0;
	game->map2.sprites = NULL;
	game->mlx = mlx_init();
	set_pos(&game->map2.player.pos, -1, -1);
}

void display_map(t_map *map)
{
	int i;

	i = 0;
	printf("\n");
	while (i < map->height)
	{
		printf("%s\n", map->matrix[i]);
		i++;
	}
}

int             main(int argc, char *argv[])
{
	(void)	argc;
	(void)	argv;
	t_game  game;

	init_settings(&game);
	int ret = parse_file(&game, argv[1]);
	if (ret == SUCCESS)
	{
		printf(
			"Settings:\n- Resolution [%i, %i]\n- Ceiling [%i]\n- Floor [%i]\n",
			game.resolution.width,
			game.resolution.height,
			game.ceiling_color,
			game.floor_color
		);
		display_map(&game.map2);
	}
	else
		printf("Cannot parse, ERROR: %i\n", ret);
	game.win = mlx_new_window(game.mlx, game.resolution.width, game.resolution.height, "OOPS");
	game.projection_plane = (game.resolution.width / 2) / tan(FOV / 2);
	game.sprite_alpha = get_texture_color(&game.sprite_texture, &(t_pos){0, 0});
	game.map2.player.current_direction = 0;
	game.map2.player.current_rotation = 0;
	game.map2.player.move_speed = 0.1;
	game.map2.player.rotate_speed = 1.5 * (M_PI / 180);
	//init(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_pressed, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_released, &game);
	mlx_loop_hook(game.mlx, main_loop, &game);
	mlx_loop(game.mlx);
}

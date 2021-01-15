#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <X11/X.h>

#include "shapes.h"
#include "init.h"
#include "debug.h"
#include "input.h"
#include "cub3d.h"

double normalize_angle(double angle)
{
	angle = fmod(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

int pixel2coord(double n)
{
	return (floor(n / TILE_SIZE));
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
			color = (game->map[x][y] == '1') ? BLACK : WHITE;
			draw_square(&game->img, color, TILE_SIZE, y * TILE_SIZE, x * TILE_SIZE);
			y++;
		}
		x++;
	}
}

int draw_player(t_game *game)
{
	draw_circle(&game->img, 10, game->player.x, game->player.y);
	draw_line(&game->img, 0x0000FF00, game->player.x,
		game->player.y,
		game->player.x + cos(game->player.facing_angle) * 20,
		game->player.y + sin(game->player.facing_angle) * 20);
}

float line_len(float x0, float y0, float x1, float y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

void render_rays(t_game *game)
{
	int i;

	i = 0;
	while (i < NUM_RAYS)
	{
		// draw_line(
		// 	&game->img,
		// 	0x000000FF,
		// 	game->player.x,
		// 	game->player.y,
		// 	game->player.x + cos(game->rays[i].angle) * 30,
		// 	game->player.y + sin(game->rays[i].angle) * 30
		// );
		draw_line(
			&game->img,
			0x000000FF,
			game->player.x,
			game->player.y,
			game->rays[i].wall_x,
			game->rays[i].wall_y
		);
		i++;
	}
}

void render_3d_walls(t_game *game)
{
	int i;
	int wall_height;
	double projection_plane;
	int offsetX;
	int offsetY;
	// int color;
	i = 0;
	int t;
	while (i < NUM_RAYS)
	{
		projection_plane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
		wall_height = (TILE_SIZE / (game->rays[i].distance * cos(game->rays[i].angle - game->player.facing_angle))) * projection_plane;
		int wall_top = (SCREEN_HEIGHT / 2) - (wall_height / 2);
		wall_top = (wall_top < 0) ? 0 : wall_top;
		int wall_bottom = (SCREEN_HEIGHT / 2) + (wall_height / 2);
		wall_bottom = (wall_bottom > SCREEN_HEIGHT) ? SCREEN_HEIGHT : wall_bottom;
		// if (game->rays[i].hit_south)
		// 	color = YELLOW;
		// else if (game->rays[i].hit_north)
		// 	color = WHITE;
		// else if (game->rays[i].hit_west)
		// 	color = GREEN;
		// else if (game->rays[i].hit_east)
		// 	color = RED;
		if (game->rays[i].hit_east || game->rays[i].hit_west)
		{
			t = 0;
			offsetX = (int)game->rays[i].wall_y % TILE_SIZE;
		}
		else
		{
			t = 1;
			offsetX = (int)game->rays[i].wall_x % TILE_SIZE;
		}
		draw_line(&game->img, BLUE, i, 0, i, wall_top);
		int y = wall_top;
		while (y < wall_bottom)
		{
			int distance_from_top = y + (wall_height / 2) - (SCREEN_HEIGHT / 2);
			offsetY = distance_from_top * (64.0 / wall_height);
			my_mlx_pixel_put(&game->img, i, y, *(unsigned int *)(game->texture[t].addr + (offsetY * game->texture[t].line_length) + offsetX * game->texture[t].bits_per_pixel / 8));
			y++;
		}
		// draw_line(&game->img, color, i, wall_top, i, wall_bottom);	
		draw_line(&game->img, BLACK, i, wall_bottom, i, SCREEN_HEIGHT);
		i++;
	}
}

t_bool has_wall_at(t_game *game, double x, double y)
{
	int ix;
	int iy;

	ix = pixel2coord(x);
	iy = pixel2coord(y);
	return (!!(game->map[iy][ix] == '1'));
}

int main_loop(t_game *game)
{
	int hypotenus;
	float x;
	float y;

	game->player.facing_angle = normalize_angle(game->player.facing_angle + game->player.current_rotation * game->player.rotate_speed);
	hypotenus = game->player.current_direction * game->player.move_speed;
	x = game->player.x + cos(game->player.facing_angle) * hypotenus;
	y = game->player.y + sin(game->player.facing_angle) * hypotenus;
	if (!has_wall_at(game, x, y))
	{
		game->player.x = x;
		game->player.y = y;
	}
	cast_rays(game);
	// draw_map(game);
	// render_rays(game);
	// draw_player(game);
	render_3d_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);

	char buffer[400];
	sprintf(buffer, "X: %f Y: %f Angle: %f", game->player.x, game->player.y, game->player.facing_angle);
	mlx_string_put(game->mlx, game->win, 5, 15, WHITE, buffer);
}

int             main(int argc, char *argv[])
{
	(void)	argc;
	(void)	argv;
	t_game  game;

	init(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_pressed, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_released, &game);
	mlx_loop_hook(game.mlx, main_loop, &game);
	mlx_loop(game.mlx);
}

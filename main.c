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

double normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
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

int ray_vertical_direction(t_ray *ray)
{
	if (ray->angle > 0 && ray->angle < M_PI)
		return (DOWN);
	return (UP);
}

int ray_horizontal_direction(t_ray *ray)
{
	if (ray->angle < 0.5 * M_PI || ray->angle > 1.5 * M_PI)
		return (RIGHT);
	return (LEFT);
}

float line_len(int x0, int y0, int x1, int y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

void cast_ray(t_game *game, t_ray *ray)
{
	float x_intercept;
	float y_intercept;
	float x_step;
	float y_step;

	ray->wall_x = 800;
	ray->wall_y = 800;
	////////////////
	// HORIZONTAL //
	///////////////
	y_intercept = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	y_intercept += ray_vertical_direction(ray) == DOWN ? TILE_SIZE : 0;
	x_intercept = game->player.x + (y_intercept - game->player.y) / tan(ray->angle);

	y_step = TILE_SIZE;
	y_step *= ray_vertical_direction(ray) == UP ? -1 : 1;
	x_step = TILE_SIZE / tan(ray->angle);
	x_step *= (ray_horizontal_direction(ray) == LEFT && x_step > 0) ? -1 : 1;
	x_step *= (ray_horizontal_direction(ray) == RIGHT && x_step < 0) ? -1 : 1;

	while (x_intercept >= 0 && x_intercept <= SCREEN_WIDTH && y_intercept >= 0 && y_intercept <= SCREEN_HEIGHT)
	{
		if (has_wall_at(game, x_intercept, y_intercept - (ray_vertical_direction(ray) == UP)))
		{
			ray->wall_x = x_intercept;
			ray->wall_y = y_intercept;
			break;
		}
		else
		{
			x_intercept += x_step;
			y_intercept += y_step;
		}
	}

	x_intercept = 0;
	y_intercept = 0;
	x_step = 0;
	y_step = 0;
	////////////////
	//  VERTICAL //
	///////////////
	x_intercept = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	x_intercept += ray_horizontal_direction(ray) == RIGHT ? TILE_SIZE : 0;
	y_intercept = game->player.y + (x_intercept - game->player.x) * tan(ray->angle);

	x_step = TILE_SIZE;
	x_step *= ray_horizontal_direction(ray) == LEFT ? -1 : 1;

	y_step = TILE_SIZE * tan(ray->angle);
	y_step *= (ray_vertical_direction(ray) == UP && y_step > 0) ? -1 : 1;
	y_step *= (ray_vertical_direction(ray) == DOWN && y_step < 0) ? -1 : 1;

	while (x_intercept >= 0 && x_intercept <= SCREEN_WIDTH && y_intercept >= 0 && y_intercept <= SCREEN_HEIGHT)
	{
		if (has_wall_at(game, x_intercept - (ray_horizontal_direction(ray) == LEFT), y_intercept))
		{
			if (line_len(game->player.x, game->player.y, ray->wall_x, ray->wall_y) >
				line_len(game->player.x, game->player.y, x_intercept, y_intercept))
			{
				ray->wall_x = x_intercept;
				ray->wall_y = y_intercept;
			}
			break;
		}
		else
		{
			x_intercept += x_step;
			y_intercept += y_step;
		}
	}
	// print_ray(ray);
}

void cast_rays(t_game *game)
{
	int i;
	float angle;

	i = 0;
	angle = game->player.facing_angle - (FOV / 2);
	while (i < NUM_RAYS)
	{
		game->rays[i].angle = normalize_angle(angle);
		cast_ray(game, &game->rays[i]);
		angle += FOV / NUM_RAYS;
		i++;
	}
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
	float projection_plane;

	i = 0;

}

int has_wall_at(t_game *game, double x, double y)
{
	int ix;
	int iy;

	ix = pixel2coord(x);
	iy = pixel2coord(y);
	return (game->map[iy][ix] == '1');
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
	draw_map(game);
	render_rays(game);
	draw_player(game);
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

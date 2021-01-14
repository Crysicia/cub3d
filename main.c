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

float line_len(float x0, float y0, float x1, float y1)
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
	y_intercept += !ray->facing_up ? TILE_SIZE : 0;
	x_intercept = game->player.x + (y_intercept - game->player.y) / tan(ray->angle);

	y_step = TILE_SIZE;
	y_step *= ray->facing_up ? -1 : 1;
	x_step = TILE_SIZE / tan(ray->angle);
	x_step *= (ray->facing_left && x_step > 0) ? -1 : 1;
	x_step *= (!ray->facing_left && x_step < 0) ? -1 : 1;

	while (x_intercept >= 0 && x_intercept <= SCREEN_WIDTH && y_intercept >= 0 && y_intercept <= SCREEN_HEIGHT)
	{
		if (has_wall_at(game, x_intercept, y_intercept - ray->facing_up))
		{
			ray->wall_x = x_intercept;
			ray->wall_y = y_intercept;
			ray->distance = line_len(game->player.x, game->player.y, ray->wall_x, ray->wall_y);
			ray->hit_south = ray->facing_up;
			ray->hit_north = !ray->hit_south;
			break;
		}
		else
		{
			x_intercept += x_step;
			y_intercept += y_step;
		}
	}

	////////////////
	//  VERTICAL //
	///////////////
	x_intercept = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	x_intercept += !ray->facing_left ? TILE_SIZE : 0;
	y_intercept = game->player.y + (x_intercept - game->player.x) * tan(ray->angle);

	x_step = TILE_SIZE;
	x_step *= ray->facing_left ? -1 : 1;

	y_step = TILE_SIZE * tan(ray->angle);
	y_step *= (ray->facing_up && y_step > 0) ? -1 : 1;
	y_step *= (!ray->facing_up && y_step < 0) ? -1 : 1;

	while (x_intercept >= 0 && x_intercept <= SCREEN_WIDTH && y_intercept >= 0 && y_intercept <= SCREEN_HEIGHT)
	{
		if (has_wall_at(game, x_intercept - ray->facing_left, y_intercept))
		{
			if (line_len(game->player.x, game->player.y, ray->wall_x, ray->wall_y) >
				line_len(game->player.x, game->player.y, x_intercept, y_intercept))
			{
				ray->wall_x = x_intercept;
				ray->wall_y = y_intercept;
				ray->distance = line_len(game->player.x, game->player.y, x_intercept, y_intercept);
				ray->hit_north = 0;
				ray->hit_south = 0;
				ray->hit_east = ray->facing_left;
				ray->hit_west = !ray->hit_east;
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

void set_ray_direction(t_ray *ray)
{
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->facing_up = 0;
	else
		ray->facing_up = 1;
	if (ray->angle < 0.5 * M_PI || ray->angle > 1.5 * M_PI)
		ray->facing_left = 0;
	else
		ray->facing_left = 1;
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
		set_ray_direction(&game->rays[i]);
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
	double wall_height;
	double projection_plane;
	int color;
	i = 0;
	while (i < NUM_RAYS)
	{
		projection_plane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
		wall_height = (TILE_SIZE / (game->rays[i].distance * cos(game->rays[i].angle - game->player.facing_angle))) * projection_plane;
		int wall_top = (SCREEN_HEIGHT / 2) - (wall_height / 2);
		wall_top = (wall_top < 0) ? 0 : wall_top;
		int wall_bottom = (SCREEN_HEIGHT / 2) + (wall_height / 2);
		wall_bottom = (wall_bottom > SCREEN_HEIGHT) ? SCREEN_HEIGHT : wall_bottom;
		if (game->rays[i].hit_south)
			color = YELLOW;
		else if (game->rays[i].hit_north)
			color = WHITE;
		else if (game->rays[i].hit_west)
			color = GREEN;
		else if (game->rays[i].hit_east)
			color = RED;
		//printf("RENDER: i=%i, wall_height=%f\n", i, wall_height);
		draw_line(&game->img, color, i, wall_top, i, wall_bottom);
		i++;
	}
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
	draw_rectangle(&game->img, BLACK, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	draw_rectangle(&game->img, 0x000000FF, SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0, 0);
	//draw_rectangle(&game->img, 0x00FFFFFF, SCREEN_WIDTH, SCREEN_HEIGHT / 2 - 1, 0, SCREEN_HEIGHT / 2);
	// draw_rectangle(&game->img, RED, 100, 200, 0, 0);
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

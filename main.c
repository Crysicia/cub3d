#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <X11/X.h>

#include "shapes.h"

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

void init_map(t_game *game)
{
	char map[MAP_HEIGHT][MAP_WIDTH] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '1', '0', '0', '0', '0', '1', '1', '1'},
		{'1', '0', '1', '1', '0', '1', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};
	memcpy(game->map, map, sizeof(char) * MAP_WIDTH * MAP_HEIGHT);
}

void init_player(t_game *game)
{
	game->player.x = 200;
	game->player.y = 200;
	game->player.current_direction = 0;
	game->player.current_rotation = 0;
	game->player.facing_angle = M_PI / 2;
	game->player.move_speed = 2.0;
	game->player.rotate_speed = 0.4 * (M_PI / 180); 
}

void init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	game->img.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
		&game->img.line_length, &game->img.endian);
	game->player.x = SCREEN_WIDTH / 2;
	game->player.y = SCREEN_WIDTH / 2;
	init_map(game);
	init_player(game);
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

void print_ray(t_ray *ray)
{
	int ver;
	int hor;

	ver = ray_vertical_direction(ray);
	hor = ray_horizontal_direction(ray);
	printf("Ray direction: ");
	if (ver == DOWN)
		printf("DOWN ");
	else if (ver == UP)
		printf("UP ");
	if (hor == RIGHT)
		printf("RIGHT\n");
	else if (hor == LEFT)
		printf("LEFT\n");
	printf("Ray X: %i\n", ray->wall_x);
	printf("Ray Y: %i\n", ray->wall_y);
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

	ray->wall_x = 400;
	ray->wall_y = 400;
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
	// print_ray(ray);

	if (ray_vertical_direction(ray) == UP)
		y_intercept--;

	while (x_intercept >= 0 && x_intercept <= SCREEN_WIDTH && y_intercept >= 0 && y_intercept <= SCREEN_HEIGHT)
	{
		if (game->map[pixel2coord(y_intercept)][pixel2coord(x_intercept)] == '1')
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
	// print_ray(ray);

	if (ray_horizontal_direction(ray) == LEFT)
		x_intercept--;
	while (x_intercept >= 0 && x_intercept <= SCREEN_WIDTH && y_intercept >= 0 && y_intercept <= SCREEN_HEIGHT)
	{
		if (game->map[pixel2coord(y_intercept)][pixel2coord(x_intercept)] == '1')
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

int will_collide(t_game *game)
{
	int x;
	int y;
	int hypotenus;

	hypotenus = game->player.current_direction * game->player.move_speed;
	x = game->player.x + cos(game->player.facing_angle) * hypotenus;
	y = game->player.y + sin(game->player.facing_angle) * hypotenus;
	if (game->map[pixel2coord(y)][pixel2coord(x)] == '1')
		return (1);
	return (0);
}

int main_loop(t_game *game)
{
	int hypotenus;

	game->player.facing_angle = game->player.facing_angle + game->player.current_rotation * game->player.rotate_speed;
	hypotenus = game->player.current_direction * game->player.move_speed;
	if (!will_collide(game))
	{
		game->player.x += cos(game->player.facing_angle) * hypotenus;
		game->player.y += sin(game->player.facing_angle) * hypotenus;
	}
	cast_rays(game);
	draw_map(game);
	render_rays(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int key_released(int keycode, t_game *game)
{
	if (keycode == UP)
		game->player.current_direction = 0;
	else if (keycode == DOWN)
		game->player.current_direction = 0;
	else if (keycode == RIGHT)
		game->player.current_rotation = 0;
	else if (keycode == LEFT)
		game->player.current_rotation = 0;
}

int key_pressed(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(game->mlx, game->img.img);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(0);
	}
	else if (keycode == UP)
		game->player.current_direction = 1;
	else if (keycode == DOWN)
		game->player.current_direction = -1;
	else if (keycode == RIGHT)
		game->player.current_rotation = 1;
	else if (keycode == LEFT)
		game->player.current_rotation = -1;
	else
		printf("Angle: %f\n", game->player.facing_angle);
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

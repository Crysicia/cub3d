#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/X.h>

#define UP 65362
#define DOWN 65364
#define RIGHT 65361
#define LEFT 65363
#define ESC 65307

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

#define WHITE 0x00FFFFFF
#define BLACK 0x00000000
#define GREEN 0x0000FF00
#define RED 0x00FF0000

#define TILE_SIZE 40
#define NUM_RAYS 1
#define FOV 60 * (M_PI / 180)

typedef struct s_ray
{
	float length;
	float wall_x;
	float wall_y;
	double angle;
}				t_ray;

typedef struct s_player
{
	float x;
	float y;
	int current_direction;
	int current_rotation;
	double facing_angle;
	double move_speed;
	double rotate_speed;
}			t_player;

typedef struct  s_pos
{
	int x;
	int y;
}				t_pos;

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_data		img;
	char		map[MAP_HEIGHT][MAP_WIDTH];
	t_player	player;
	t_ray rays[NUM_RAYS];
}				t_game;

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

int max(int a, int b)
{
	return ((a > b) ? a : b);
}

int abs(int i)
{
	return ((i > 0) ? i : -i);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_octants(t_data *img, int xc, int yc, int x, int y)
{
	my_mlx_pixel_put(img, xc+x, yc+y, RED); 
    my_mlx_pixel_put(img, xc-x, yc+y, RED); 
    my_mlx_pixel_put(img, xc+x, yc-y, RED); 
    my_mlx_pixel_put(img, xc-x, yc-y, RED); 
    my_mlx_pixel_put(img, xc+y, yc+x, RED); 
    my_mlx_pixel_put(img, xc-y, yc+x, RED);
    my_mlx_pixel_put(img, xc+y, yc-x, RED);
    my_mlx_pixel_put(img, xc-y, yc-x, RED);
}

void draw_circle(t_data *img, int radius, int xc, int yc)
{
	int x;
	int y;
	int delta;

	x = 0;
	y = radius;
	delta = 3 - 2 * radius; 
	draw_octants(img, xc, yc, x, y); 
	while (y >= x) 
	{
		x++; 
		if (delta > 0) 
		{ 
			y--;  
			delta = delta + 4 * (x - y) + 10; 
		} 
		else
			delta = delta + 4 * x + 6; 
		draw_octants(img, xc, yc, x, y); 
	}
}

void draw_square(t_data *img, int color, int size, int x, int y)
{
	int i = 0;
	int j;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			if (i == 0 || i == size || j== 0 || j == size)
				my_mlx_pixel_put(img, x + i, y + j, BLACK);
			else
				my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}


void draw_line(t_data *img, int color, int x0, int y0, int x1, int y1)
{
	int dx;
	int dy;
	float x_inc;
	float y_inc;
	float x;
	float y;
	int steps;
	int i;

	dx = x1 - x0;
	dy = y1 - y0;
	steps = max(abs(dx), abs(dy));
	x_inc = dx / (float) steps;
	y_inc = dy / (float) steps;
	x = x0;
	y = y0;
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(img, x, y, color);
		x += x_inc;
		y += y_inc;
		i++;
	}
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
}

void cast_ray(t_game *game, t_ray *ray)
{
	int x_intercept;
	int y_intercept;
	int x_step;
	int y_step;

	y_intercept = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	y_intercept += ray_vertical_direction(ray) == DOWN ? TILE_SIZE : 0;
	x_intercept = game->player.x + (game->player.y - y_intercept) / tan(ray->angle);

	y_step = TILE_SIZE;
	y_step *= ray_vertical_direction(ray) == UP ? -1 : 1;
	x_step = TILE_SIZE / tan(ray->angle);
	x_step *= (ray_horizontal_direction(ray) == LEFT && x_step > 0) ? -1 : 1;
	x_step *= (ray_horizontal_direction(ray) == RIGHT && x_step < 0) ? -1 : 1;
	print_ray(ray);
}

void cast_rays(t_game *game)
{
	int i;
	float angle;

	i = 0;
	angle = game->player.facing_angle - (FOV / 2);
	while (i < NUM_RAYS)
	{
		game->rays[i].angle = angle;
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
		draw_line(
			&game->img,
			0x000000FF,
			game->player.x,
			game->player.y,
			game->player.x + cos(game->rays[i].angle) * 30,
			game->player.y + sin(game->rays[i].angle) * 30
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

	game->player.facing_angle = normalize_angle(game->player.facing_angle + game->player.current_rotation * game->player.rotate_speed);
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

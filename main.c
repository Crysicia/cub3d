#include <mlx.h>
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
	t_pos		player;
	int			current_key;
}				t_game;

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

void draw_square(t_data *img, int color, int size, int x, int y)
{
	int i = 0;
	int j;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}


void draw_line(t_data *img, int x0, int y0, int x1, int y1)
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
		my_mlx_pixel_put(img, x, y, 0x00FFFFFF);
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
		{'1', '0', '1', '0', '0', '1', '0', '1', '0', '1'},
		{'1', '0', '1', '0', '0', '1', '0', '1', '0', '1'},
		{'1', '0', '1', '0', '0', '1', '0', '1', '0', '1'},
		{'1', '0', '1', '0', '0', '1', '0', '1', '0', '1'},
		{'1', '0', '1', '1', '0', '1', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};
	memcpy(game->map, map, sizeof(char) * MAP_WIDTH * MAP_HEIGHT);
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
	game->current_key = 0;
	init_map(game);
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
			color = (game->map[x][y] == '1') ? 0x00FFFFFF : 0x00000000;
			draw_square(&game->img, color, SCREEN_WIDTH / MAP_WIDTH, y * (SCREEN_WIDTH / MAP_WIDTH), x * (SCREEN_HEIGHT / MAP_HEIGHT));
			y++;
		}
		x++;
	}
}

int draw_player(t_game *game)
{
	draw_square(&game->img, 0x00FF0000, 15, game->player.x, game->player.y);
}

void move_player(t_game *game, int x, int y)
{
	if (game->map[x / (SCREEN_WIDTH / MAP_WIDTH)][y / (SCREEN_HEIGHT / MAP_HEIGHT)] == '0')
	{
		game->player.x = x;
		game->player.y = y;
	}
}

int main_loop(t_game *game)
{
	if (game->current_key == UP)
		move_player(game, game->player.x, game->player.y - 1);
	else if (game->current_key == DOWN)
		move_player(game, game->player.x, game->player.y + 1);
	else if (game->current_key == RIGHT)
		game->player.x--;
	else if (game->current_key == LEFT)
		game->player.x++;
	draw_map(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int key_released(int keycode, t_game *game)
{
	game->current_key = 0;
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
	else
		game->current_key = keycode;
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

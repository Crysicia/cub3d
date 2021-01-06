#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct s_vars {
    void *mlx;
    void *win;
    t_data *data;
}               t_vars;

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
            //if (j == 0 || j == size || i == 0 || i == size)
                my_mlx_pixel_put(img, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void draw_circle(t_data *img, int color, int radius, int x_center, int y_center)
{
    int p;
    int x;
    int y;

    x = radius;
    y = 0;


    my_mlx_pixel_put(img, x + x_center, y + y_center, color);
    if (radius > 0)
    {
        my_mlx_pixel_put(img, x + x_center, -y + y_center, color);
        my_mlx_pixel_put(img, y + x_center, x + y_center, color);
        my_mlx_pixel_put(img, -y + x_center, x + y_center, color);
    }
    p = 1 - radius;
    while (x > y)
    {
        y++;

        if (p <= 0)
            p = p + 2 * y + 1;
        else
        {
            x--;
            p = p + 2 * y - 2 * x + 1;
        }

        if (x < y)
            break;

        my_mlx_pixel_put(img, x + x_center, y + y_center, color);
        my_mlx_pixel_put(img, -x + x_center, y + y_center, color);
        my_mlx_pixel_put(img, x + x_center, -y + y_center, color);
        my_mlx_pixel_put(img, -x + x_center, -y + y_center, color);
        if (x != y)
        {
            my_mlx_pixel_put(img, y + x_center, x + y_center, color);
            my_mlx_pixel_put(img, -y + x_center, x + y_center, color);
            my_mlx_pixel_put(img, y + x_center, -x + y_center, color);
            my_mlx_pixel_put(img, -y + x_center, -x + y_center, color);
        }
    }
}

int max(int a, int b)
{
    return ((a > b) ? a : b);
}

int abs(int i)
{
    return ((i > 0) ? i : -i);
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

#define UP 65362
#define DOWN 65364
#define RIGHT 65361
#define LEFT 65363
#define ESC 65307

int g_x = 0;
int g_y = 0;

int draw_render(int x, int y, t_vars *vars)
{
    mlx_clear_window(vars->mlx, vars->win);
    //mlx_destroy_image(vars->data->img);
    draw_square(vars->data->img, 0x00FFFFFF, 25, x, y);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}

int key_pressed(int keycode, t_vars *vars)
{
    // ENTER: 65293
    // UP: 65362
    // DOWN: 65364
    // RIGHT: 65361
    // LEFT: 65363
    printf("Key pressed: %i\n", keycode);
    if (keycode == ESC)
        mlx_destroy_window(vars->mlx, vars->win);
}

int close(int keycode, t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
}

int red_cross(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
}

int visible(t_vars *vars)
{
    printf("Visibility changed!\n");
}

int mouse_enter(int x, int y, void *params)
{
    printf("Position: [X: %i, Y: %i]\n", x, y);
}

int render_next_frame(t_data *img)
{
    static int count = 0;
    printf("Frame number: %i\n", ++count);
}

int             main(int argc, char *argv[])
{
    (void)argc;
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    t_vars  vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 300, 300, "Hello world!");
    img.img = mlx_new_image(vars.mlx, 300, 300);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

    vars.data = &img;
    draw_square(&img, 0x00d52f0b, 42, 42, 42);
    draw_circle(&img, 0x00FFFFFF, 100, 150, 150);
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    draw_line(&img, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));

    mlx_key_hook(vars.win, key_pressed, &vars);

    //mlx_hook(vars.win, KeyPress, KeyPressMask, close, &vars);
    mlx_hook(vars.win, MotionNotify, PointerMotionMask, mouse_enter, &vars);
    mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, red_cross, &vars);
    mlx_hook(vars.win, FocusIn, FocusChangeMask, visible, &vars);

    mlx_loop_hook(vars.mlx, render_next_frame, &img);
    mlx_loop(vars.mlx);
}

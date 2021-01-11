/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:38:47 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/11 17:59:37 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	// SEGFAULT ON RAY ANGLE 6.214896
	// Player angle 0455310
	// WallX FLT_MAX
	// WallY FLT_MAX
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

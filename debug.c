/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:50:18 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/12 10:51:00 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void print_infos(t_game *game)
{
	int i;

	i = 0;
	while (i < NUM_RAYS)
	{
		printf("\n---- %i ----\n| WallX: %f\n| WallY: %f\n| Angle: %f\n",  i, game->rays[i].wall_x, game->rays[i].wall_y, game->rays[i].angle);
		i++;
	}
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
	printf("Ray X: %f\n", ray->wall_x);
	printf("Ray Y: %f\n", ray->wall_y);
}

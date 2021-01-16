/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:50:18 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/16 11:49:12 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void print_infos(t_game *game)
{
	int i;
	float langle;

	i = 0;
	langle = 0;
	printf("num,x,y,angle,delta\n");
	while (i < NUM_RAYS)
	{
		// printf("\n---- %i ----\n| WallX: %f\n| WallY: %f\n| Angle: %f\n",  i, game->rays[i].wall_hit.x, game->rays[i].wall_hit.y, game->rays[i].angle);
		printf("%i,%f,%f,%f,%f\n", i, game->rays[i].wall_hit.x, game->rays[i].wall_hit.y, game->rays[i].angle, game->rays[i].angle - langle);
		langle = game->rays[i].angle;
		i++;
	}
}

void print_ray(t_ray *ray)
{
	int ver;
	int hor;

	printf("Ray direction: ");
	if (ray->facing_up)
		printf("UP ");
	else
		printf("DOWN ");
	if (ray->facing_left)
		printf("LEFT\n");
	else
		printf("RIGHT\n");
	printf("Ray X: %f\n", ray->wall_hit.x);
	printf("Ray Y: %f\n", ray->wall_hit.y);
}

void display_infos(t_game *game)
{
	char buffer[400];
	sprintf(buffer, "X: %f Y: %f Angle: %f", game->player.pos.x, game->player.pos.y, game->player.facing_angle);
	mlx_string_put(game->mlx, game->win, 5, 15, WHITE, buffer);
}

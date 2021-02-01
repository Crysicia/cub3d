/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:50:18 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/01 16:16:55 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/debug.h"
#include "../includes/cub3d.h"

void print_infos(t_game *game)
{
	int i;
	float langle;

	i = 0;
	langle = 0;
	printf("num,x,y,angle,delta\n");
	while (i < game->resolution.width)
	{
		// printf("\n---- %i ----\n| WallX: %f\n| WallY: %f\n| Angle: %f\n",  i, game->rays[i].wall_hit.x, game->rays[i].wall_hit.y, game->rays[i].angle);
		printf("%i,%f,%f,%f,%f\n", i, game->rays[i].wall_hit.x, game->rays[i].wall_hit.y, game->rays[i].angle, game->rays[i].angle - langle);
		langle = game->rays[i].angle;
		i++;
	}
}

void print_ray(t_ray *ray)
{
	printf("--- Ray ---\n| Direction: ");
	if (ray->facing_up)
		printf("UP ");
	else
		printf("DOWN ");
	if (ray->facing_left)
		printf("LEFT\n");
	else
		printf("RIGHT\n");
	printf("| Wall hit X: %f\n", ray->wall_hit.x);
	printf("| Wall hit Y: %f\n", ray->wall_hit.y);
	printf("| Angle: %f\n", ray->angle);
	printf("| Distance: %f\n", ray->distance);
}

void print_wall(t_wall *wall)
{
	printf("--- Wall ---\n| Height: %f\n| Top: %f\n| Bottom: %f\n",
		wall->height,
		wall->top,
		wall->bottom
	);
}

void print_texture(t_data *text, char *name)
{
	printf("--- Texture [%s] ---\n| Width: %i\n| Height: %i\n| BPS: %i\n| Line length: %i\n| Addr: %p\n| Img: %p\n",
		name,
		text->width,
		text->height,
		text->bits_per_pixel,
		text->line_length,
		text->addr,
		text->img
	);
}

void print_resolution(t_resolution *reso)
{
	printf("--- Resolution ---\n| Width: %i\n| Height: %i\n", reso->width, reso->height);
}

void print_player(t_player *player)
{
	printf("--- Player ---\n| Pos: [%f, %f]\n| Angle: %f\n", player->pos.x, player->pos.y, player->facing_angle);
}

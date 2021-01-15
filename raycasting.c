/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:41:20 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/15 17:43:47 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <math.h>
#include "cub3d.h"
#include "init.h"

t_bool is_in_screen(float x, float y)
{
	return (x >= 0 && x <= SCREEN_WIDTH && y >= 0 && y <= SCREEN_HEIGHT);
}

void horizontal_intercept_loop(t_game *game, t_ray *ray, t_pos *intercept, t_pos *step)
{
	while (is_in_screen(intercept->x, intercept->y))
	{
		if (has_wall_at(game, intercept->x, intercept->y - ray->facing_up))
		{
			ray->wall_x = intercept->x;
			ray->wall_y = intercept->y;
			ray->distance = line_len(game->player.x, game->player.y, ray->wall_x, ray->wall_y);
			ray->hit_south = ray->facing_up;
			ray->hit_north = !ray->hit_south;
			break;
		}
		else
		{
			intercept->x += step->x;
			intercept->y += step->y;
		}
	}
}

void get_horizontal_intercept(t_game *game, t_ray *ray)
{
	t_pos intercept;
	t_pos step;

	intercept.y = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	if (!ray->facing_up)
		intercept.y += TILE_SIZE;
	intercept.x = game->player.x + (intercept.y - game->player.y) / tan(ray->angle);
	step.x = TILE_SIZE / tan(ray->angle);
	step.y = TILE_SIZE;
	if (ray->facing_up)
		step.y *= -1;
	if (ray->facing_left && step.x > 0)
		step.x *= -1;
	if (!ray->facing_left && step.x < 0)
		step.x *= -1;
	horizontal_intercept_loop(game, ray, &intercept, &step);
}

void vertical_intercept_loop(t_game *game, t_ray *ray, t_pos *intercept, t_pos *step)
{
	while (is_in_screen(intercept->x, intercept->y))
	{
		if (has_wall_at(game, intercept->x - ray->facing_left, intercept->y))
		{
			if (line_len(game->player.x, game->player.y, ray->wall_x, ray->wall_y) >
				line_len(game->player.x, game->player.y, intercept->x, intercept->y))
			{
				ray->wall_x = intercept->x;
				ray->wall_y = intercept->y;
				ray->distance = line_len(game->player.x, game->player.y, intercept->x, intercept->y);
				ray->hit_north = 0;
				ray->hit_south = 0;
				ray->hit_east = ray->facing_left;
				ray->hit_west = !ray->hit_east;
			}
			break;
		}
		else
		{
			intercept->x += step->x;
			intercept->y += step->y;
		}
	}
}

void get_vertical_intercept(t_game *game, t_ray *ray)
{
	t_pos intercept;
	t_pos step;

	intercept.x = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	if (!ray->facing_left)
	 	intercept.x += TILE_SIZE;
	intercept.y = game->player.y + (intercept.x - game->player.x) * tan(ray->angle);

	step.x = TILE_SIZE;
	step.y = TILE_SIZE * tan(ray->angle);
	if (ray->facing_left)
		step.x *= -1;
	if (ray->facing_up && step.y > 0)
		step.y *= -1;
	if (!ray->facing_up && step.y < 0)
		step.y *= -1;
	vertical_intercept_loop(game, ray, &intercept, &step);
}

void cast_ray(t_game *game, t_ray *ray)
{
	get_horizontal_intercept(game, ray);
	get_vertical_intercept(game, ray);
}

void cast_rays(t_game *game)
{
	int i;
	float angle;

	i = 0;
	angle = game->player.facing_angle - (FOV / 2);
	while (i < NUM_RAYS)	
	{
		init_ray(&game->rays[i], angle);
		cast_ray(game, &game->rays[i]);
		angle += FOV / NUM_RAYS;
		i++;
	}
}

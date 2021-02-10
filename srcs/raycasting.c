/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:41:20 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/10 14:48:28 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <math.h>
#include "../includes/cub3d.h"
#include "../includes/init.h"

t_bool is_in_screen(t_game *game, float x, float y)
{
	return (x >= 0 && x <= game->resolution.width && y >= 0 && y <= game->resolution.height);
}

void horizontal_intercept_loop(t_game *game, t_ray *ray, t_pos *intercept, t_pos *step)
{
	t_bool has_found_wall;

	has_found_wall = false;
	while (is_in_screen(game, intercept->x, intercept->y) && !has_found_wall)
	{
		if (has_wall_at(game, intercept->x, intercept->y - ray->facing_up))
		{
			set_pos(&ray->wall_hit, intercept->x, intercept->y);
			ray->distance = pos_distance(&game->map.player.pos, &ray->wall_hit);
			ray->hit_south = ray->facing_up;
			ray->hit_north = !ray->hit_south;
			has_found_wall = true;
		}
		else
			set_pos(intercept, intercept->x + step->x, intercept->y + step->y);
	}
}

void vertical_intercept_loop(t_game *game, t_ray *ray, t_pos *intercept, t_pos *step)
{
	t_bool has_found_wall;

	has_found_wall = false;
	while (is_in_screen(game, intercept->x, intercept->y) && !has_found_wall)
	{
		if (has_wall_at(game, intercept->x - ray->facing_left, intercept->y))
		{
			if (pos_distance(&game->map.player.pos, &ray->wall_hit) >
				pos_distance(&game->map.player.pos, intercept))
			{
				set_pos(&ray->wall_hit, intercept->x, intercept->y);
				ray->distance = pos_distance(&game->map.player.pos, &ray->wall_hit);
				ray->hit_north = 0;
				ray->hit_south = 0;
				ray->hit_east = ray->facing_left;
				ray->hit_west = !ray->hit_east;
			}
			has_found_wall = true;
		}
		else
			set_pos(intercept, intercept->x + step->x, intercept->y + step->y);
	}
}

void get_horizontal_intercept(t_game *game, t_ray *ray)
{
	t_pos intercept;
	t_pos step;

	intercept.y = floor(game->map.player.pos.y);
	if (!ray->facing_up)
		intercept.y += 1;
	intercept.x = game->map.player.pos.x + (intercept.y - game->map.player.pos.y) / tan(ray->angle);
	step.x = 1 / tan(ray->angle);
	step.y = 1;
	if (ray->facing_up)
		step.y *= -1;
	if (ray->facing_left && step.x > 0)
		step.x *= -1;
	if (!ray->facing_left && step.x < 0)
		step.x *= -1;
	horizontal_intercept_loop(game, ray, &intercept, &step);
}

void get_vertical_intercept(t_game *game, t_ray *ray)
{
	t_pos intercept;
	t_pos step;

	intercept.x = floor(game->map.player.pos.x);
	if (!ray->facing_left)
	 	intercept.x += 1;
	intercept.y = game->map.player.pos.y + (intercept.x - game->map.player.pos.x) * tan(ray->angle);

	step.x = 1;
	step.y = tan(ray->angle);
	if (ray->facing_left)
		step.x *= -1;
	if (ray->facing_up && step.y > 0)
		step.y *= -1;
	if (!ray->facing_up && step.y < 0)
		step.y *= -1;
	vertical_intercept_loop(game, ray, &intercept, &step);
}

void cast_rays(t_game *game)
{
	int i;
	float angle;

	i = 0;
	while (i < game->resolution.width)	
	{
		angle = game->map.player.facing_angle + atan((i - game->resolution.width / 2) / game->projection_plane);
		init_ray(&game->rays[i], angle);
		get_horizontal_intercept(game, &game->rays[i]);
		get_vertical_intercept(game, &game->rays[i]);
		i++;
	}
}

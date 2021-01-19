/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:46:05 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/19 09:49:30 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void compute_wall_boundaries(t_game *game, t_ray *ray, t_wall *wall)
{
	wall->height = game->projection_plane / (ray->distance * cos(ray->angle - game->player.facing_angle));
	wall->top = (SCREEN_HEIGHT / 2.0) - (wall->height / 2);
	if (wall->top < 0)
		wall->top = 0;
	wall->bottom = (SCREEN_HEIGHT / 2.0) + (wall->height / 2);
	if (wall->bottom > SCREEN_HEIGHT)
		wall->bottom = SCREEN_HEIGHT;
}

unsigned int get_texture_color(t_data *texture, t_pos *offset)
{
	char    *dst;

	dst = texture->addr + ((int)offset->y * texture->line_length
							+ (int)offset->x * (texture->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void get_texture_offset(void)
{

}

void render_texture_strip(t_data *img, t_data *texture, t_wall *wall, t_pos *offset, int x)
{
	int y;
	int distance_from_top;
	int color;

	y = wall->top;
	while (y < wall->bottom)
	{
		distance_from_top = y + (wall->height / 2) - (SCREEN_HEIGHT / 2);
		offset->y = distance_from_top * (64.0f / wall->height);
		color = get_texture_color(texture, offset);
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
}

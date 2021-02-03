/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:46:05 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/01 16:34:07 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/shapes.h"

void compute_wall_boundaries(t_game *game, t_ray *ray, t_wall *wall)
{
	wall->height = game->projection_plane / (ray->distance * cos(ray->angle - game->map.player.facing_angle));
	wall->top = (game->resolution.height / 2.0) - (wall->height / 2);
	if (wall->top < 0)
		wall->top = 0;
	wall->bottom = (game->resolution.height / 2.0) + (wall->height / 2);
	if (wall->bottom > game->resolution.height)
		wall->bottom = game->resolution.height;
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

void render_texture_strip(t_game *game, t_data *texture, t_wall *wall, t_pos *offset, int x)
{
	int y;
	int distance_from_top;
	int color;

	y = wall->top;
	while (y < wall->bottom)
	{
		distance_from_top = y + (wall->height / 2) - (game->resolution.height / 2);
		offset->y = distance_from_top * ((float)texture->height / wall->height);
		color = get_texture_color(texture, offset);
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
}

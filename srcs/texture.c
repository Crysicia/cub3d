/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:46:05 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/12 11:55:05 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			compute_wall_boundaries(t_game *game, t_ray *ray, t_wall *wall)
{
	wall->height = game->projection_plane /
			(ray->distance * cos(ray->angle - game->map.player.facing_angle));
	wall->top = (game->resolution.height / 2.0) - (wall->height / 2);
	if (wall->top < 0)
		wall->top = 0;
	wall->bottom = (game->resolution.height / 2.0) + (wall->height / 2);
	if (wall->bottom > game->resolution.height)
		wall->bottom = game->resolution.height;
}

unsigned int	get_texture_color(t_data *texture, t_pos *offset)
{
	char *dst;

	dst = texture->addr + ((int)offset->y * texture->line_length
							+ (int)offset->x * (texture->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

t_data			*get_texture(t_game *game, t_ray *ray)
{
	if (ray->hit_north)
		return (&game->texture[0]);
	else if (ray->hit_east)
		return (&game->texture[1]);
	else if (ray->hit_south)
		return (&game->texture[2]);
	else
		return (&game->texture[3]);
}

void			get_texture_offset(t_data *texture, t_ray *ray, t_pos *offset)
{
	if (ray->hit_north || ray->hit_south)
		offset->x = fmod(ray->wall_hit.x, 1) * texture->width;
	else
		offset->x = fmod(ray->wall_hit.y, 1) * texture->width;
}

void			render_texture_strip(t_game *game, t_data *texture,
													t_wall *wall, int x)
{
	int		y;
	int		top_distance;
	int		color;
	t_pos	offset;

	get_texture_offset(texture, &game->rays[x], &offset);
	y = wall->top;
	while (y < wall->bottom)
	{
		top_distance = y + (wall->height / 2) - (game->resolution.height / 2);
		offset.y = top_distance * ((float)texture->height / wall->height);
		color = get_texture_color(texture, &offset);
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:43:44 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/16 10:45:26 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		init(t_game *game, int *error, int save_flag)
{
	*error = SUCCESS;
	adjust_screen_size(game, save_flag);
	if (!save_flag)
	{
		game->win = mlx_new_window(game->mlx, game->resolution.width,
									game->resolution.height, WINDOW_TITLE);
		if (!game->win)
			return (set_error(error, ALLOCATION_ERROR));
	}
	game->img.img = mlx_new_image(game->mlx,
							game->resolution.width, game->resolution.height);
	if (!game->img.img)
		return (set_error(error, ALLOCATION_ERROR));
	game->img.addr = mlx_get_data_addr(game->img.img,
		&game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		return (set_error(error, ALLOCATION_ERROR));
	game->projection_plane = (game->resolution.width / 2) / tan(FOV / 2);
	game->sprite_alpha = get_texture_color(&game->sprite_texture,
													&(t_pos){0, 0});
	if (!init_rays(game))
		return (set_error(error, ALLOCATION_ERROR));
	return (SUCCESS);
}

void	init_player(t_game *game)
{
	game->map.player.pos.x = -1;
	game->map.player.pos.y = -1;
	game->map.player.current_direction = 0;
	game->map.player.current_rotation = 0;
	game->map.player.facing_angle = M_PI / 2;
	game->map.player.move_speed = 0.1;
	game->map.player.rotate_speed = 1.5 * (M_PI / 180);
	game->map.player.current_strafing = 0;
}

void	init_ray(t_ray *ray, float angle)
{
	ray->distance = 0;
	set_pos(&ray->wall_hit, INT_MAX, INT_MAX);
	ray->angle = normalize_angle(angle);
	ray->facing_up = 1;
	ray->facing_left = 1;
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->facing_up = 0;
	if (ray->angle < M_PI_2 || ray->angle > ONE_A_HALF_PI)
		ray->facing_left = 0;
	ray->hit_east = 0;
	ray->hit_west = 0;
	ray->hit_north = 0;
	ray->hit_south = 0;
}

void	init_sprite(t_sprite *sprite, float x, float y)
{
	set_pos(&sprite->pos, x, y);
	sprite->is_visible = true;
	sprite->distance = 0;
	sprite->angle = 0;
}

t_bool	init_settings(t_game *game)
{
	nullify_settings(game);
	init_player(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	return (true);
}

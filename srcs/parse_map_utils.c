/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 23:33:18 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/11 14:54:43 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/init.h"

int		set_sprites_pos(t_map *map)
{
	char	tile;
	int		i;
	t_pos	coords;

	set_pos(&coords, 0, 0);
	i = 0;
	map->sprites = malloc(sizeof(t_sprite) * map->sprites_count);
	if (!map->sprites)
		return (ALLOCATION_ERROR);
	while ((int)coords.y < map->height)
	{
		coords.x = 0;
		while (map->matrix[(int)coords.y][(int)coords.x])
		{
			tile = map->matrix[(int)coords.y][(int)coords.x];
			if (tile == SPRITE)
			{
				init_sprite(&map->sprites[i], coords.x + 0.5, coords.y + 0.5);
				i++;
			}
			coords.x++;
		}
		coords.y++;
	}
	return (SUCCESS);
}

void	set_player_pos(t_player *player, t_pos *pos, char angle)
{
	set_pos(&player->pos, pos->x + 0.5, pos->y + 0.5);
	if (angle == 'N')
		player->facing_angle = 270 * (M_PI / 180);
	else if (angle == 'E')
		player->facing_angle = (M_PI / 180);
	else if (angle == 'S')
		player->facing_angle = 90 * (M_PI / 180);
	else if (angle == 'W')
		player->facing_angle = 180 * (M_PI / 180);
}

int		map_get_positions(t_map *map)
{
	t_pos	coords;
	char	tile;

	set_pos(&coords, 0, 0);
	while ((int)coords.y < map->height)
	{
		coords.x = 0;
		while (map->matrix[(int)coords.y][(int)coords.x])
		{
			tile = map->matrix[(int)coords.y][(int)coords.x];
			if (tile == SPRITE)
				map->sprites_count++;
			else if (ft_strchr(PLAYER, tile))
			{
				if (map->player.pos.x != -1)
					return (STARTING_POINT_ERROR);
				set_player_pos(&map->player, &coords, tile);
				map->matrix[(int)coords.y][(int)coords.x] = '0';
			}
			coords.x++;
		}
		coords.y++;
	}
	return (set_sprites_pos(map));
}

t_bool	add_row_to_map(t_map *map, char *row)
{
	char	**new_matrix;
	int		index;

	index = 0;
	new_matrix = malloc(sizeof(char *) * (map->height + 1));
	if (!new_matrix)
		return (false);
	while (index < map->height)
	{
		new_matrix[index] = map->matrix[index];
		index++;
	}
	new_matrix[index] = row;
	free(map->matrix);
	map->matrix = new_matrix;
	map->height++;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:39:46 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/29 12:59:50 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int map_get_positions(t_map *map)
{
	t_pos coords;
	char tile;

	set_pos(&coords, 0, 0);
	while ((int)coords.y < map->height)
	{
		coords.x = 0;
		while (map[(int)coords.y][(int)coords.x])
		{
			tile = map[(int)coords.y][(int)coords.x];
			if (tile == SPRITE)
				map->sprites_count++;
			else if (ft_strchr(player, tile))
			{
				if (map->player.pos.x == -1)
					return (STARTING_POINT_ERROR);
				set_pos(&map->player.pos, coords.x, coords.y);
			}
			coords.x++;
		}
		coords.y++;
	}
	return (SUCCESS);
}

t_bool add_row_to_map(t_map *map, char *row)
{
	char **new_matrix;
	int index;

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

t_bool map_row_is_valid(char *line)
{
	char *charset;
	size_t index;

	charset = "012NSEW ";
	index = -1;
	while (line[++index])
		if (!ft_strchr(charset, line[index]))
			return (false);
	return (true);
}

int parse_map(t_game *game, char *line)
{
	char *row;

	if (!map_row_is_valid(line))
		return (MAP_ERROR);
	row = ft_strdup(line);
	if (!row || !add_row_to_map(&game->map2, row))
		return (ALLOCATION_ERROR);
	return (SUCCESS);
}

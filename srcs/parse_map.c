/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:39:46 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/28 16:20:47 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		// copy shit
	}
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
	if (!map_row_is_valid(line))
		return (MAP_ERROR);
	if (!add_row_to_map(&game->map2, line))
		return (ALLOCATION_ERROR);
	return (SUCCESS);
}

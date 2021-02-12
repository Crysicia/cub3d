/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:39:46 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/12 16:57:48 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_bool	map_row_is_valid(char *line)
{
	char	*charset;
	size_t	index;

	charset = "012NSEW ";
	index = -1;
	while (line[++index])
		if (!ft_strchr(charset, line[index]))
			return (false);
	return (true);
}

int		parse_map(t_game *game, char *line)
{
	char *row;

	if (!map_row_is_valid(line))
		return (MAP_ERROR);
	row = ft_strdup(line);
	if (!row || !add_row_to_map(&game->map, row))
		return (ALLOCATION_ERROR);
	return (SUCCESS);
}

int		validate_map(t_map *map, int *error)
{
	*error = map_get_positions(map);
	if (*error != SUCCESS)
		return (*error);
	*error = floodfill(&map->player.pos, "02", '-', map);
	return (*error);
}

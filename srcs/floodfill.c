/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 12:33:20 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/02 23:55:32 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_bool floodfill(int x, int y, char *targets, char fill, t_map *map)
{
	if (x < 0 || y < 0 || y >= map->height || x >= ft_strlen(map->matrix[y]))
		return (false);
	if (ft_strchr(targets, map->matrix[y][x]))
	{
		map->matrix[y][x] = fill;
		if (!floodfill(x + 1, y, targets, fill, map))
			return (false);
		if (!floodfill(x, y + 1, targets, fill, map))
			return (false);
		if (!floodfill(x - 1, y, targets, fill, map))
			return (false);
		if (!floodfill(x, y - 1, targets, fill, map))
			return (false);
	}
	else if (map->matrix[y][x] != fill && map->matrix[y][x] != WALL)
		return (false);
	return (true);
}

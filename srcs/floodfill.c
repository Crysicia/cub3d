/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 12:33:20 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/03 16:40:37 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


t_pos *new_pos(float x, float y)
{
	t_pos *pos;
	pos = malloc(sizeof(t_pos));
	if (!pos)
		return (NULL);
	set_pos(pos, x, y);
	return (pos);
}

/*
Flood-fill (node):
  1. Set Q to the empty queue or stack.
  2. Add node to the end of Q.
  3. While Q is not empty:
  4.   Set n equal to the first element of Q.
  5.   Remove first element from Q.
  6.   If n is Inside:
         Set the n
         Add the node to the west of n to the end of Q.
         Add the node to the east of n to the end of Q.
         Add the node to the north of n to the end of Q.
         Add the node to the south of n to the end of Q.
  7. Continue looping until Q is exhausted.
  8. Return.
*/

t_bool floodfill(t_pos *pos, char *targets, char fill, t_map *map)
{
	t_list *queue;
	t_list *previous;
	t_pos *pos_n;
	int x;
	int y;

	pos_n = new_pos(pos->x, pos->y);
	queue = ft_lstnew(pos_n);
	while (queue)
	{
		x = (int)((t_pos *)queue->content)->x;
		y = (int)((t_pos *)queue->content)->y;
		if (x < 0 || y < 0 || y >= map->height || x >= ft_strlen(map->matrix[y]))
			return (false);
		if (ft_strchr(targets, map->matrix[y][x]))
		{
			map->matrix[y][x] = fill;
			ft_lstadd_front(&queue, ft_lstnew(new_pos(pos->x + 1, pos->y)));
			ft_lstadd_front(&queue, ft_lstnew(new_pos(pos->x, pos->y + 1)));
			ft_lstadd_front(&queue, ft_lstnew(new_pos(pos->x - 1, pos->y)));
			ft_lstadd_front(&queue, ft_lstnew(new_pos(pos->x, pos->y - 1)));
		}
		previous = queue;
		queue = queue->next;
		ft_lstdelone(previous, free);
	}
	return (true);
}

// t_bool floodfill(int x, int y, char *targets, char fill, t_map *map)
// {
// 	if (x < 0 || y < 0 || y >= map->height || x >= ft_strlen(map->matrix[y]))
// 		return (false);
// 	if (ft_strchr(targets, map->matrix[y][x]))
// 	{
// 		map->matrix[y][x] = fill;
// 		if (!floodfill(x + 1, y, targets, fill, map))
// 			return (false);
// 		if (!floodfill(x, y + 1, targets, fill, map))
// 			return (false);
// 		if (!floodfill(x - 1, y, targets, fill, map))
// 			return (false);
// 		if (!floodfill(x, y - 1, targets, fill, map))
// 			return (false);
// 	}
// 	else if (map->matrix[y][x] != fill && map->matrix[y][x] != WALL)
// 		return (false);
// 	return (true);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 12:33:20 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/11 16:14:59 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_point	*new_point(int x, int y)
{
	t_point *point;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	return (point);
}

int		free_queue(t_list *queue, int error)
{
	ft_lstclear(&queue, free);
	return (error);
}

t_bool	enqueue(t_list **queue, int x, int y)
{
	t_point	*point;
	t_list	*node;

	point = new_point(x, y);
	if (!point)
		return (false);
	node = ft_lstnew(point);
	if (!node)
	{
		free(point);
		return (false);
	}
	ft_lstadd_back(queue, node);
	return (true);
}

void	dequeue(t_list **queue)
{
	t_list *previous;

	previous = *queue;
	*queue = (*queue)->next;
	ft_lstdelone(previous, free);
}

int		floodfill(t_pos *pos, char *targets, char fill, t_map *map)
{
	t_list	*q;
	t_point p;

	q = NULL;
	if (!enqueue(&q, pos->x, pos->y))
		return (free_queue(q, ALLOCATION_ERROR));
	while (q)
	{
		p = *(t_point *)q->content;
		if (p.x < 0 || p.y < 0 || p.y >= map->height
			|| p.x >= (int)ft_strlen(map->matrix[p.y]))
			return (free_queue(q, MALFORMED_MAP_ERROR));
		if (ft_strchr(targets, map->matrix[p.y][p.x]))
		{
			map->matrix[p.y][p.x] = fill;
			if (!enqueue(&q, p.x + 1, p.y) || !enqueue(&q, p.x - 1, p.y)
			|| !enqueue(&q, p.x, p.y + 1) || !enqueue(&q, p.x, p.y - 1))
				return (free_queue(q, ALLOCATION_ERROR));
		}
		else if (map->matrix[p.y][p.x] != fill && map->matrix[p.y][p.x] != WALL)
			return (free_queue(q, MALFORMED_MAP_ERROR));
		dequeue(&q);
	}
	return (SUCCESS);
}

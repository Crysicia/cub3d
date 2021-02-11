/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 12:33:20 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/11 13:38:08 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_pos	*new_pos(float x, float y)
{
	t_pos *pos;

	pos = malloc(sizeof(t_pos));
	if (!pos)
		return (NULL);
	set_pos(pos, x, y);
	return (pos);
}

int		free_queue(t_list *queue, int error)
{
	ft_lstclear(&queue, free);
	return (error);
}

t_bool	enqueue(t_list **queue, int x, int y)
{
	t_pos	*pos;
	t_list	*node;

	pos = new_pos(x, y);
	if (!pos)
		return (false);
	node = ft_lstnew(pos);
	if (!node)
	{
		free(pos);
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
	t_list	*queue;
	int		x;
	int		y;

	queue = NULL;
	if (!enqueue(&queue, (int)pos->x, (int)pos->y))
		return (free_queue(queue, ALLOCATION_ERROR));
	while (queue)
	{
		x = (int)((t_pos *)queue->content)->x;
		y = (int)((t_pos *)queue->content)->y;
		if (x < 0 || y < 0 || y >= map->height || (unsigned int)x >= ft_strlen(map->matrix[y]))
			return (free_queue(queue, MALFORMED_MAP_ERROR));
		if (ft_strchr(targets, map->matrix[y][x]))
		{
			map->matrix[y][x] = fill;
			if (!enqueue(&queue, x + 1, y)
				|| !enqueue(&queue, x - 1, y)
				|| !enqueue(&queue, x, y + 1)
				|| !enqueue(&queue, x, y - 1))
				return (free_queue(queue, ALLOCATION_ERROR));
		}
		else if (map->matrix[y][x] != fill && map->matrix[y][x] != WALL)
			return (free_queue(queue, MALFORMED_MAP_ERROR));
		dequeue(&queue);
	}
	return (SUCCESS);
}

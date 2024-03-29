/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:44:48 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/16 10:47:48 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_bool	is_in_screen(t_game *game, float x, float y)
{
	return (x >= 0 && x <= game->resolution.width
		&& y >= 0 && y <= game->resolution.height);
}

float	normalize_angle(float angle)
{
	angle = fmod(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

void	set_pos(t_pos *pos, float x, float y)
{
	pos->x = x;
	pos->y = y;
}

float	pos_distance(t_pos *p1, t_pos *p2)
{
	return (sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:44:48 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/16 11:51:13 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int pixel2coord(float n)
{
	return (floor(n / TILE_SIZE));
}

float normalize_angle(float angle)
{
	angle = fmod(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

void set_pos(t_pos *pos, float x, float y)
{
	pos->x = x;
	pos->y = y;
}

float pos_distance(t_pos *p1, t_pos *p2)
{
	return (sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2)));
}

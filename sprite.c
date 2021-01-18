/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:02:52 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/18 10:35:19 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool is_in_fov(t_player *player, double angle)
{
	if (player->facing_angle - (FOV / 2) <= angle
		&& player->facing_angle + (FOV / 2) >= angle)
		return (true);
	return (false);
}

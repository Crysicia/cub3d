/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:51:46 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/12 10:52:51 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
#include "types.h"
void print_infos(t_game *game);
void print_ray(t_ray *ray);


int ray_vertical_direction(t_ray *ray);
int ray_horizontal_direction(t_ray *ray);
#endif

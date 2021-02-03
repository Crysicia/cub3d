/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:51:46 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/02 16:09:46 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
#include "types.h"
void print_infos(t_game *game);
void print_ray(t_ray *ray);
void display_infos(t_game *game);
void print_wall(t_wall *wall);
void print_texture(t_data *text, char *name);
void print_resolution(t_resolution *reso);
void print_player(t_player *player);
void display_map(t_map *map);
#endif

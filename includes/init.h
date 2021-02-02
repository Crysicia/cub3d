/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:44:19 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/02 11:21:53 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H
#include "types.h"
t_bool init(t_game *game);
void init_map(t_game *game);
void init_player(t_game *game);
void init_ray(t_ray *ray, float angle);
void init_sprite(t_sprite *sprite, float x, float y);
t_bool init_all_sprites(t_game *game);
t_bool load_texture(void *mlx, t_data *texture, char *filepath);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:44:19 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/15 17:42:01 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H
#include "types.h"
void init(t_game *game);
void init_map(t_game *game);
void init_player(t_game *game);
void init_ray(t_ray *ray, float angle);
#endif

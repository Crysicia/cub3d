/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:06:26 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/15 15:38:59 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "types.h"
double normalize_angle(double angle);
int pixel2coord(double n);
int draw_map(t_game *game);
int draw_player(t_game *game);
float line_len(float x0, float y0, float x1, float y1);
void cast_ray(t_game *game, t_ray *ray);
void set_ray_direction(t_ray *ray);
void cast_rays(t_game *game);
void render_rays(t_game *game);
void render_3d_walls(t_game *game);
t_bool has_wall_at(t_game *game, double x, double y);
int main_loop(t_game *game);

#endif

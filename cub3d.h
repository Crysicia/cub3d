/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:06:26 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/16 11:42:25 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "types.h"
float normalize_angle(float angle);
int pixel2coord(float n);
int draw_map(t_game *game);
int draw_player(t_game *game);
void cast_ray(t_game *game, t_ray *ray);
void set_ray_direction(t_ray *ray);
void cast_rays(t_game *game);
void render_rays(t_game *game);
void render_3d_walls(t_game *game);
t_bool has_wall_at(t_game *game, double x, double y);
int main_loop(t_game *game);
void set_pos(t_pos *pos, float x, float y);
float pos_distance(t_pos *p1, t_pos *p2);
unsigned int get_texture_color(t_data *texture, t_pos *offset);
void compute_wall_boundaries(t_game *game, t_ray *ray, t_wall *wall);
void render_texture_strip(t_data *img, t_data *texture, t_wall *wall, t_pos *offset, int x);
#endif

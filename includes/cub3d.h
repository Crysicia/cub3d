/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:06:26 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/26 12:34:36 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "types.h"
# include <limits.h>
# include "../mlx/mlx.h"
float normalize_angle(float angle);
int draw_map(t_game *game);
int draw_player(t_game *game);
void cast_ray(t_game *game, t_ray *ray);
void set_ray_direction(t_ray *ray);
void cast_rays(t_game *game);
void render_rays(t_game *game);
void render_3d_walls(t_game *game);
t_bool has_wall_at(t_game *game, float x, float y);
int main_loop(t_game *game);
void set_pos(t_pos *pos, float x, float y);
float pos_distance(t_pos *p1, t_pos *p2);
unsigned int get_texture_color(t_data *texture, t_pos *offset);
void compute_wall_boundaries(t_game *game, t_ray *ray, t_wall *wall);
void render_texture_strip(t_data *img, t_data *texture, t_wall *wall, t_pos *offset, int x);

t_bool is_in_fov(double player_angle, double angle);
void update_sprite_visibility(t_player *player, t_sprite *sprite);
void render_sprite(t_game *game, t_sprite *sprite);
void sort_sprites(t_game *game);

int arr_len(char **arr);
t_bool set_colors(int *color, int red, int green, int blue);
t_bool get_colors(int *color, char **colors);
t_bool color_is_valid(char *line);
int parse_colors(int *color, char *line);

t_bool set_resolution(t_resolution *resolution, int width, int height);
t_bool get_resolution(t_resolution *resolution, char **reso_arr);
t_bool resolution_is_valid(char *line);
int parse_resolution(t_resolution *resolution, char *line);

int set_texture(void *mlx, t_data *texture, char *path);
int parse_texture(void *mlx, t_data *texture, char *line);
#endif
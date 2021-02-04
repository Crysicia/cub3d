/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:06:26 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/04 14:30:16 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "types.h"
# include <limits.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# define BUFFER_SIZE 64

char	*gnl_strdup(const char *s1);
char	*gnl_strjoin(char const *s1, char const *s2);
int		gnl_strchr(const char *s, int c);
void	gnl_nl_to_null(char *str);
int		gnl_free(void *line, char **remaining, int status);
char	*gnl_dup_free(char *to_free, char *to_dup);
char	*gnl_alloc_remaining(char *remaining);
int		get_next_line(int fd, char **line, char **remaining);

void clean_exit(t_game *game, int error);
void print_error(int code);
t_bool init_rays(t_game *game);
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
void render_texture_strip(t_game *game, t_data *texture, t_wall *wall, t_pos *offset, int x);

t_bool is_in_fov(double player_angle, double angle);
void update_sprite_visibility(t_player *player, t_sprite *sprite);
void render_all_sprites(t_game *game);
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

t_bool has_extension(char *path, char *ext);
t_bool open_file(char *path, int *fd);
int set_error(int *error, int code);
t_bool settings_set(t_game *game);

int parse_setting(t_game *game, char *line);
int parse_settings_loop(t_game *game, int fd, int *error);
int parse_map_loop(t_game *game, int fd, int *error);
int parse_file(t_game *game, char *path, int *error);

t_bool add_row_to_map(t_map *map, char *row);
t_bool map_row_is_valid(char *line);
int parse_map(t_game *game, char *line);
int validate_map(t_map *map, int *error);
int map_get_positions(t_map *map);
void set_player_pos(t_player *player, t_pos *pos, char angle);
int set_sprites_pos(t_map *map);

t_pos *new_pos(float x, float y);
int free_queue(t_list *queue, int error);
t_bool enqueue(t_list **queue, int x, int y);
void dequeue(t_list **queue);
int floodfill(t_pos *pos, char *targets, char fill, t_map *map);


t_bool save_image(t_game *game);

#endif

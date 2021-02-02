/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:53:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/02 15:08:20 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

t_bool line_is_blank(char *line)
{
	while (*line)
	{
		if (*line != ' ' || *line != '\t')
			return (false);
		line++;
	}
	return (true);
}

int parse_setting(t_game *game, char *line)
{
	if (!ft_strncmp(line, "R ", 2))
		return (parse_resolution(&game->resolution, &line[2]));
	if (!ft_strncmp(line, "C ", 2))
		return (parse_colors(&game->ceiling_color, &line[2]));
	if (!ft_strncmp(line, "F ", 2))
		return (parse_colors(&game->floor_color, &line[2]));
	if (!ft_strncmp(line, "S ", 2))
		return (parse_texture(game->mlx, &game->sprite_texture, &line[2]));
	if (!ft_strncmp(line, "NO ", 3))
		return (parse_texture(game->mlx, &game->texture[0], &line[3]));
	if (!ft_strncmp(line, "EA ", 3))
		return (parse_texture(game->mlx, &game->texture[1], &line[3]));
	if (!ft_strncmp(line, "SO ", 3))
		return (parse_texture(game->mlx, &game->texture[2], &line[3]));
	if (!ft_strncmp(line, "WE ", 3))
		return (parse_texture(game->mlx, &game->texture[3], &line[3]));
	return (UNKNOWN_SETTING_ERROR);
}

int parse_settings_loop(t_game *game, int fd, int *error)
{
	char *line;
	int gnl_ret;

	gnl_ret = 1;
	while (*error == SUCCESS && gnl_ret == 1 && !settings_set(game))
	{
		gnl_ret = get_next_line(fd, &line);
		if (gnl_ret == -1)
			return (set_error(error, READ_ERROR));
		if (!line_is_blank(line))
			*error = parse_setting(game, line);
		printf("Current line: %s\n", line);
		free(line);
	}
	if (*error != SUCCESS)
		close(fd);
	return (*error);
}

int parse_map_loop(t_game *game, int fd, int *error)
{
	char *line;
	int gnl_ret;
	t_bool map_reached;

	gnl_ret = 1;
	map_reached = false;
	while (*error == SUCCESS && gnl_ret == 1)
	{
		gnl_ret = get_next_line(fd, &line);
		if (gnl_ret == -1)
			return (set_error(error, READ_ERROR));
		if (!line_is_blank(line))
			map_reached = true;
		if (map_reached)
			*error = parse_map(game, line);
		free(line);
	}
	if (*error != SUCCESS)
		close(fd);
	return (*error);
}

int parse_file(t_game *game, char *path, int *error)
{
	int fd;

	*error = SUCCESS;
	fd = 0;
	if (!has_extension(path, ".cub"))
		return (set_error(error, EXTENSION_ERROR));
	if (!open_file(path, &fd))
		return (set_error(error, OPEN_ERROR));
	if (parse_settings_loop(game, fd, error) != SUCCESS)
		return (*error);
	if (parse_map_loop(game, fd, error) != SUCCESS)
		return (*error);
	close(fd);
	if (validate_map(&game->map, error) != SUCCESS)
		return (*error);
	return (*error);
}

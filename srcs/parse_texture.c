/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:27:26 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/28 12:24:36 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

int set_texture(void *mlx, t_data *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(mlx, path,
							&texture->width, &texture->height);
	free(path);
	if (texture->img)
		texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (!texture->img || !texture->addr)
	{
		if (texture->img)
			mlx_destroy_image(mlx, texture->img);
		free(texture->addr);
		return (GENERIC_ERROR);
	}
	return (SUCCESS);
}

int parse_texture(void *mlx, t_data *texture, char *line)
{
	char *trimmed;

	if (texture->img != NULL)
		return (ALREADY_SET_ERROR);
	trimmed = ft_strtrim(line, " ");
	if (!trimmed)
		return (ALLOCATION_ERROR);
	if (!has_extension(trimmed, ".xpm"))
	{
		free(trimmed);
		return (EXTENSION_ERROR);
	}
	return (set_texture(mlx, texture, trimmed));
}

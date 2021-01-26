/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:27:26 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/26 15:10:12 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
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
		return (-1);
	}
	return (1);
}

int parse_texture(void *mlx, t_data *texture, char *line)
{
	char *trimmed;

	trimmed = ft_strtrim(line, " ");
	if (!trimmed)
		return (ALLOCATION_ERROR);
	return (set_texture(mlx, texture, trimmed));
}
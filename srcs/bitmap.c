/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:50:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/09 13:37:49 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_bmp_pixel rgb_to_pixel(int rgb)
{
	t_bmp_pixel pixel;

	pixel.red = (rgb & 0xFFFF00) >> 16;
	pixel.green = (rgb & 0xFF00) >> 8;
	pixel.blue = rgb & 0xFF;
	return (pixel);
}

int pitch_correction(int bits)
{
	int pitch;

	pitch = 4 - ((3 * bits) % 4);
	if (pitch == 4)
		return (0);
	return (pitch);
}

void render_one_frame(t_game *game)
{
	cast_rays(game);
	render_3d_walls(game);
	render_all_sprites(game);
}

int set_header(t_game *game, int fd, t_bmp_header *header)
{
	ft_bzero(header, sizeof(t_bmp_header));
	header->signature[0] = 'B';
	header->signature[1] = 'M';
	header->image_offset = 54;
	header->reserved = 0;
	header->dib_header.header_size = sizeof(t_dib_header);
	header->dib_header.width = game->resolution.width;
	header->dib_header.height = game->resolution.height;
	header->dib_header.planes = 1;
	header->dib_header.bits_per_pixel = 24;
	header->dib_header.image_size = (3 * game->resolution.height
		* game->resolution.width) + game->resolution.height
		* pitch_correction(game->resolution.width);
	header->size = header->image_offset + header->dib_header.image_size;
	if (write(fd, header, 2) != -1)
		return (write(fd, (char *)header + 4, sizeof(t_bmp_header) - 4));
	return (-1);
}

int set_image(t_game *game, int fd, t_bmp_header *header)
{
	t_pos coords;
	t_bmp_pixel pixel;

	set_pos(&coords, 0, game->resolution.height - 1);
	while ((int)coords.y >= 0)
	{
		coords.x = 0;
		while ((int)coords.x < game->resolution.width)
		{
			pixel = rgb_to_pixel(get_texture_color(&game->img, &coords));
			if (write(fd, &pixel, 3) == -1)
				return (-1);
			coords.x++;
		}
		if (write(fd, "\0\0\0", pitch_correction(header->dib_header.width)) == -1)
			return (-1);
		coords.y--;
	}
	return (1);
}

int save_image(t_game *game)
{
	t_bmp_header header;
	int fd;

	render_one_frame(game);
	fd = open(BMP_PATH, O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG);
	if (fd == -1 || set_header(game, fd, &header) == -1
		|| set_image(game, fd, &header) == -1 || close(fd) == -1)
		return (WRITE_ERROR);
	return (SUCCESS);
}

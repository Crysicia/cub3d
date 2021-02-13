/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 10:42:59 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/13 11:01:13 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		render_one_frame(t_game *game)
{
	cast_rays(game);
	render_3d_walls(game);
	render_all_sprites(game);
}

t_bmp_pixel	rgb_to_pixel(int rgb)
{
	t_bmp_pixel pixel;

	pixel.red = (rgb & 0xFFFF00) >> 16;
	pixel.green = (rgb & 0xFF00) >> 8;
	pixel.blue = rgb & 0xFF;
	return (pixel);
}

int			pitch_correction(int bits)
{
	int pitch;

	pitch = 4 - ((3 * bits) % 4);
	if (pitch == 4)
		return (0);
	return (pitch);
}

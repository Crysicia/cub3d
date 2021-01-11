/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:40:07 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/11 12:44:54 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H
# include "types.h"
# include "ft_math.h"
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_octants(t_data *img, int xc, int yc, int x, int y);
void draw_circle(t_data *img, int radius, int xc, int yc);
void draw_square(t_data *img, int color, int size, int x, int y);
void draw_line(t_data *img, int color, int x0, int y0, int x1, int y1);
#endif

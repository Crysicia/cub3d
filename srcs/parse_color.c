/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:25:24 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/28 13:30:16 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/cub3d.h"

t_bool set_colors(int *color, int red, int green, int blue)
{
	if (!ft_in_range(0, 255, red) || !ft_in_range(0, 255, green)
		|| !ft_in_range(0, 255, blue))
		return (false);
	(*color) = (red << 16) + (green << 8) + blue;
	return (true);
}

t_bool get_colors(int *color, char **colors)
{
	if (arr_len(colors) != 3 || !set_colors(color, ft_atoi(colors[0]),
								ft_atoi(colors[1]), ft_atoi(colors[2])))
	{
		ft_free_matrix(colors, arr_len(colors));
		return (false);
	}
	ft_free_matrix(colors, arr_len(colors));
	return (true);
}

t_bool color_is_valid(char *line)
{
	int commas;
	char *charset;
	size_t index;

	commas = 0;
	charset = "0123456789, ";
	index = 0;
	while (line[index])
	{
		if (line[index] == ',')
			commas++;
		if (!ft_strchr(charset, line[index]) || commas > 2)
			return (false);
		index++;
	}
	return (true);
}

int parse_colors(int *color, char *line)
{
	char **color_arr;

	if (*color != NOT_SET)
		return (ALREADY_SET_ERROR);
	if (!color_is_valid(line))
		return (INVALID_SETTING_ERROR);
	if (!(color_arr = ft_split_set(line, ", ")))
		return (ALLOCATION_ERROR);
	if (!get_colors(color, color_arr))
		return (INVALID_SETTING_ERROR);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:25:24 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/25 16:28:31 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/cub3d.h"

int arr_len(char **arr)
{
	int len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

t_bool set_colors(t_game *game, int red, int green, int blue);

t_bool parse_colors(t_game *game, char **colors)
{
	if (arr_len(colors) != 3 || set_colors(game, ft_atoi(colors[0]),
								ft_atoi(colors[1]), ft_atoi(colors[2])))
		return (false);
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

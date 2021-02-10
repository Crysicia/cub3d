/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:17:04 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/10 15:03:01 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_bool set_resolution(t_resolution *resolution, int width, int height)
{
	if (!ft_in_range(0, INT_MAX, width) || !ft_in_range(0, INT_MAX, height))
		return (false);
	resolution->width = width;
	resolution->height = height;
	return (true);
}

t_bool get_resolution(t_resolution *resolution, char **reso_arr)
{
	if (arr_len(reso_arr) != 2 || !set_resolution(resolution,
		ft_atoi(reso_arr[0]), ft_atoi(reso_arr[1])))
	{
		ft_free_matrix((void **)reso_arr, arr_len(reso_arr));
		return (false);
	}
	ft_free_matrix((void **)reso_arr, arr_len(reso_arr));
	return (true);
}

t_bool resolution_is_valid(char *line)
{
	char *charset;
	size_t index;

	charset = "0123456789 ";
	index = -1;
	while (line[++index])
		if (!ft_strchr(charset, line[index]))
			return (false);
	return (true);
}

int parse_resolution(t_resolution *resolution, char *line)
{
	char **reso_arr;

	if (resolution->width != NOT_SET)
		return (ALREADY_SET_ERROR);
	if (!resolution_is_valid(line))
		return (INVALID_SETTING_ERROR);
	if (!(reso_arr = ft_split_set(line, " ")))
		return (ALLOCATION_ERROR);
	if (!get_resolution(resolution, reso_arr))
		return (INVALID_SETTING_ERROR);
	return (SUCCESS);
}

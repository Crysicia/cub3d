/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:05:58 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/27 12:47:52 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int arr_len(char **arr)
{
	int len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

t_bool has_extension(char *path, char *ext)
{
	int ext_len;
	int path_len;

	ext_len = ft_strlen(ext);
	path_len = ft_strlen(path);
	if (ext_len > path_len)
		return (false);
	return (!ft_strncmp(&path[path_len - ext_len], ext, ext_len));
}

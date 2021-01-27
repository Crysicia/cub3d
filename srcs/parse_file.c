/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:53:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/27 13:01:42 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int parse_file(t_game *game, char *path)
{
	if (!has_extension(path, ".cub"))
		return (EXTENSION_ERROR);
	return (SUCCESS);
}

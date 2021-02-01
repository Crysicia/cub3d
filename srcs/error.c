/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:43:53 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/01 17:02:26 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void print_error(int code)
{
	char *message;
		
	if (code == EXTENSION_ERROR)
		message = "Unsupported file extension";
	else if (code == OPEN_ERROR)
		message = "Could not open file";
	else if (code == READ_ERROR)
		message = "Could not read file";
	else if (code == ALLOCATION_ERROR)
		message = "Not enough memory available";
	else if (code == UNKNOWN_SETTING_ERROR)
		message = "Unknown setting";
	else if (code == INVALID_SETTING_ERROR)
		message = "Invalid setting";
	else if (code == GENERIC_ERROR)
		message = "¯\\_(ツ)_/¯";
	else if (code == ALREADY_SET_ERROR)
		message = "Setting already set";
	else if (code == MAP_ERROR)
		message = "Open map";
	else if (code == STARTING_POINT_ERROR)
		message = "Multiples starting points";
	else if (code == MALFORMED_MAP_ERROR)
		message = "Invalid map";
	printf("Error\n%s\n", message);
}

void clean_exit(t_game *game)
{

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:43:53 by lpassera          #+#    #+#             */
/*   Updated: 2021/02/13 14:26:14 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_error(int code)
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
	else if (code == ALREADY_SET_ERROR)
		message = "Setting already set";
	else if (code == MALFORMED_MAP_ERROR)
		message = "Open map";
	else if (code == STARTING_POINT_ERROR)
		message = "Multiples starting points";
	else if (code == MAP_ERROR)
		message = "Invalid map";
	else if (code == WRITE_ERROR)
		message = "Could not write file to disk";
	printf("Error\n%s\n", message);
}

void	free_display(void *mlx, void *win)
{
	if (mlx && win)
		mlx_destroy_window(mlx, win);
	if (mlx)
		mlx_destroy_display(mlx);
	free(mlx);
}

void	free_img(void *mlx, t_data *img)
{
	if (mlx && img && img->img)
		mlx_destroy_image(mlx, img->img);
}

void	clean_exit(t_game *game, int error)
{
	if (error != SUCCESS)
		print_error(error);
	ft_free_matrix((void **)game->map.matrix, game->map.height);
	free(game->map.sprites);
	free(game->rays);
	free_img(game->mlx, &game->img);
	free_img(game->mlx, &game->texture[0]);
	free_img(game->mlx, &game->texture[1]);
	free_img(game->mlx, &game->texture[2]);
	free_img(game->mlx, &game->texture[3]);
	free_img(game->mlx, &game->sprite_texture);
	free_display(game->mlx, game->win);
	free(game->gnl_remaining);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:20:26 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/12 11:21:06 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
#include "types.h"
int key_released(int keycode, t_game *game);
int key_pressed(int keycode, t_game *game);
#endif

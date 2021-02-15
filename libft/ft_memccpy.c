/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:22:55 by lpassera          #+#    #+#             */
/*   Updated: 2020/08/04 17:22:57 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t index;

	index = 0;
	while (index < n)
	{
		*(char *)(dst + index) = *(char *)(src + index);
		if (*(unsigned char *)(src + index) == (unsigned char)c)
			return ((void *)(dst + index + 1));
		index++;
	}
	return (NULL);
}

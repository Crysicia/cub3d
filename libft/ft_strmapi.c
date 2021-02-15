/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 21:51:51 by lpassera          #+#    #+#             */
/*   Updated: 2020/08/11 21:51:55 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	index;

	index = 0;
	if (!s || !(str = ft_strdup(s)))
		return (NULL);
	while (str[index])
	{
		str[index] = f(index, str[index]);
		index++;
	}
	return (str);
}

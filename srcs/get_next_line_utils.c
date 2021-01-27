/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 18:27:06 by lpassera          #+#    #+#             */
/*   Updated: 2021/01/27 13:20:07 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*gnl_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	if ((dup = malloc(len * sizeof(char))))
		ft_memcpy(dup, s1, len);
	return (dup);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
	{
		gnl_free((void *)s1, (char **)&s2, 0);
		return (NULL);
	}
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if ((str = malloc((s1len + s2len + 1) * sizeof(char))))
	{
		ft_memcpy(str, s1, s1len);
		ft_memcpy(&str[s1len], s2, s2len + 1);
	}
	free((char *)s1);
	return (str);
}

int		gnl_strchr(const char *s, int c)
{
	size_t index;
	size_t s_len;

	index = -1;
	s_len = 0;
	if (!s)
		return (1);
	while (s[s_len])
		s_len++;
	while (++index <= s_len)
		if (s[index] == (char)c)
			return (index + 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:11:57 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/23 17:37:35 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	k;
	char	*dst;

	k = 0;
	if (!s || (size_t)start >= (size_t)ft_strlen((char*)s))
		return (0);
	if (!(dst = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (len)
	{
		dst[k] = (char)s[start];
		k++;
		start++;
		len--;
	}
	dst[k] = '\0';
	return (dst);
}

char	*ft_strdup(const char *s)
{
	char			*dst;
	const int		slen = ft_strlen((char*)s);
	int				i;

	i = 0;
	if (!(dst = malloc(sizeof(char) * (slen + 1))))
		return (NULL);
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			s1len;
	int			s2len;
	int			i;
	int			k;
	char		*src;

	i = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen((char*)s1);
	s2len = ft_strlen((char*)s2);
	if (!(src = malloc((sizeof(char) * (s1len + s2len + 1)))))
		return (NULL);
	while (k < s1len)
		src[i++] = s1[k++];
	k = 0;
	while (k < s2len)
	{
		src[i] = s2[k];
		i++;
		k++;
	}
	src[i] = '\0';
	return (src);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char*)(s + i));
		i++;
	}
	if (s[i] == c)
		return ((char*)(s + i));
	return (0);
}

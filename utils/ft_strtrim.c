/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:41:22 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/20 17:07:24 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isincharset(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	int		i;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = 0;
	while (ft_isincharset(s1[start], set) == 1)
		start++;
	i = ft_strlen((char*)s1) - 1;
	while (ft_isincharset(s1[i], set) == 1 && i >= 0)
		i--;
	end = i;
	if (end <= 0)
		start = end;
	if (!(dst = malloc(sizeof(char) * (end - start + 2))))
		return (NULL);
	i = 0;
	while (start <= end && end > 0)
		dst[i++] = (char)s1[start++];
	dst[i] = '\0';
	return (dst);
}

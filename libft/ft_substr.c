/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:01:42 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/20 17:07:51 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	k;
	char	*dst;

	k = 0;
	if (!s || (size_t)start >= (size_t)ft_strlen((char*)s))
		return (ft_calloc(1, 1));
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

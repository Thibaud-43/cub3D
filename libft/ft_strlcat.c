/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:51:10 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/16 11:27:00 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const unsigned int	dstlen = ft_strlen(dst);
	const int			srclen = ft_strlen((char*)src);
	size_t				i;
	int					k;
	int					res;

	i = dstlen;
	k = 0;
	if (size == 0)
		res = srclen;
	if (size <= dstlen)
		res = srclen + size;
	else
		res = dstlen + srclen;
	while (src[k] && ((i + 1) < size))
	{
		dst[i] = src[k];
		i++;
		k++;
	}
	dst[i] = '\0';
	return (res);
}

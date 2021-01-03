/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:49:19 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/16 11:25:44 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*str1;
	size_t				i;

	c = (unsigned char)c;
	str1 = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (str1[i] == c)
			return ((void*)(s + i));
		i++;
	}
	return (0);
}

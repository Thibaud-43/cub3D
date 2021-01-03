/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:50:29 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/17 15:09:56 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*str1;
	unsigned char		*str2;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	str1 = (unsigned char*)dest;
	str2 = (unsigned char*)src;
	i = 0;
	if (str2 < str1)
		while (++i <= n)
			str1[n - i] = str2[n - i];
	else
		while (i < n)
		{
			str1[i] = str2[i];
			i++;
		}
	return (dest);
}

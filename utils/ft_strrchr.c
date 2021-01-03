/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:52:17 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/16 11:01:11 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *lastpos;

	lastpos = (0);
	while (*s)
	{
		if (*s == c)
			lastpos = (char*)s;
		s++;
	}
	if (lastpos)
		return (lastpos);
	if (c == '\0')
		return ((char*)s);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:23:36 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/17 16:58:58 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int					s1len;
	int					s2len;
	int					i;
	int					k;
	char				*src;

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

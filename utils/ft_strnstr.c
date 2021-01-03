/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:52:03 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/16 11:40:00 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t			i;
	size_t			k;
	size_t			tmp;
	const size_t	littlelen = (size_t)ft_strlen((char*)little);

	i = 0;
	k = 0;
	if (littlelen == 0)
		return ((char*)big);
	while (big[i] && i < len)
	{
		tmp = i;
		while (big[i] == little[k] && i < len)
		{
			if (k == littlelen - 1)
				return ((char*)(big + tmp));
			k++;
			i++;
		}
		i = tmp;
		k = 0;
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:33:56 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/17 16:39:35 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*map;
	unsigned int		i;

	if (!s)
		return (ft_calloc(1, 1));
	if (!(map = ft_strdup(s)))
		return (NULL);
	i = 0;
	while (map[i])
	{
		map[i] = f(i, map[i]);
		i++;
	}
	return (map);
}

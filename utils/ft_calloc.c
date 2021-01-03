/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:03:27 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/17 15:43:19 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	size_t	j;
	char	*tab;

	i = 0;
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	j = count * size;
	if (!(tab = malloc(j)))
		return (0);
	while (i < j)
		tab[i++] = 0;
	return ((void *)tab);
}

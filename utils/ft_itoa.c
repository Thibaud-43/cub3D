/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 09:02:49 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/17 16:48:01 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_size(int n)
{
	int i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int num)
{
	char		*dst;
	int			count;
	int			i;
	long int	n;

	n = num;
	count = ft_count_size(n);
	i = 0;
	if (n < 0 || count == 0)
		count++;
	if (!(dst = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		dst[0] = '-';
		i++;
	}
	dst[count] = '\0';
	while (count > i)
	{
		dst[--count] = (n % 10) + '0';
		n /= 10;
	}
	return (dst);
}

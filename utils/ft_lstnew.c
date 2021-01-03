/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 09:04:47 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/18 09:51:14 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_elem;

	if (!(new_elem = malloc((sizeof(t_list) * (1)))))
		return (NULL);
	new_elem->content = content;
	new_elem->next = NULL;
	return (new_elem);
}

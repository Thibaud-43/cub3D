/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_direction_so.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:09:14 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 15:54:18 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_parse_direction_so(t_parsing *parsing)
{
	char	**direction;
	int		fd;

	parsing->param_line_valid = 1;
	if (parsing->so_encountered == 1)
		message_map_invalid(parsing,
		"Error \n La ligne de param SO est présente deux fois\n");
	parsing->so_encountered = 1;
	if (!(direction = ft_split(parsing->lign, ' ')))
		return (0);
	if (direction[0][2] != 0 | direction[2] != 0)
		message_map_invalid(parsing,
		"Error \n La ligne de param SO n'est pas correctement rédigée \n");
	if (!direction[0] | !direction[1])
		message_map_invalid(parsing,
		"Error \n La ligne de param SO n'est pas correctement rédigée \n");
	fd = open(direction[1], O_RDONLY);
	if (fd == -1)
		message_map_invalid(parsing,
		"Error \n Le texture SO n'est pas correcte \n");
	close(fd);
	free_split(direction);
	return (1);
}

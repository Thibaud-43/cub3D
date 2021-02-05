/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_direction_ea.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:09:14 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 17:11:55 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_parse_direction_ea(t_parsing *parsing, t_map *map)
{
	char	**direction;
	int		fd;
	char	buff[2];

	parsing->param_line_valid = 1;
	if (parsing->ea_encountered == 1)
		message_map_invalid(parsing,
		"Error \n La ligne de param EA est présente deux fois\n");
	parsing->ea_encountered = 1;
	if (!(direction = ft_split(parsing->lign, ' ')))
		return (0);
	if (direction[0][2] != 0 | direction[2] != 0)
		message_map_invalid(parsing,
		"Error \n La ligne de param EA n'est pas correctement rédigée \n");
	if (!direction[0] | !direction[1])
		message_map_invalid(parsing,
		"Error \n La ligne de param EA n'est pas correctement rédigée \n");
	fd = open(direction[1], O_RDONLY);
	if (fd == -1 | read(fd, buff, 1) < 0)
		message_map_invalid(parsing,
		"Error \n La texture EA n'est pas correcte \n");
	close(fd);
	map->ea = ft_strdup(direction[1]);
	free_split(direction);
	return (1);
}

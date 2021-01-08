/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_direction_no.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:09:14 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 17:10:42 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_parse_direction_no(t_parsing *parsing, t_map *map)
{
	char	**direction;
	int		fd;

	parsing->param_line_valid = 1;
	if (parsing->no_encountered == 1)
		message_map_invalid(parsing,
		"Error \n La ligne de param NO est présente deux fois\n");
	parsing->no_encountered = 1;
	if (!(direction = ft_split(parsing->lign, ' ')))
		return (0);
	if (direction[0][2] != 0 | direction[2] != 0)
		message_map_invalid(parsing,
		"Error \n La ligne de param NO n'est pas correctement rédigée \n");
	if (!direction[0] | !direction[1])
		message_map_invalid(parsing,
		"Error \n La ligne de param NO n'est pas correctement rédigée \n");
	fd = open(direction[1], O_RDONLY);
	if (fd == -1)
		message_map_invalid(parsing,
		"Error \n La texture NO n'est pas correcte \n");
	map->no = ft_strdup(direction[1]);
	close(fd);
	free_split(direction);
	return (1);
}

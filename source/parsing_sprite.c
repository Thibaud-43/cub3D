/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:07:19 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 17:08:55 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_parse_sprite(t_parsing *parsing, t_map *map)
{
	char	**sprite;
	int		fd;
	char	buff[2];

	parsing->param_line_valid = 1;
	if (parsing->s_encountered == 1)
		message_map_invalid(parsing,
		"Error \n La ligne de param SPRITE est présente deux fois\n");
	parsing->s_encountered = 1;
	if (!(sprite = ft_split(parsing->lign, ' ')))
		return (0);
	if (sprite[0][1] != 0 | sprite[2] != 0)
		message_map_invalid(parsing,
		"Error \n La ligne de param S n'est pas correctement rédigée \n");
	if (!sprite[0] | !sprite[1])
		message_map_invalid(parsing,
		"Error \n La ligne de param S n'est pas correctement rédigée \n");
	fd = open(sprite[1], O_RDONLY);
	if (fd == -1 | read(fd, buff, 1) < 0)
		message_map_invalid(parsing,
		"Error \nLE SPRITE ne s'ouvre pas correctement\n");
	close(fd);
	map->sprite = ft_strdup(sprite[1]);
	free_split(sprite);
	return (1);
}

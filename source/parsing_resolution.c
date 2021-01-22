/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_resolution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:03:07 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 17:05:09 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_parse_resolution_2(t_parsing *parsing,
char **resolution, int i, t_map *map)
{
	if (parsing->is_valid)
	{
		while (resolution[1][i])
		{
			if (ft_isdigit(resolution[1][i]) == 0)
				message_map_invalid(parsing,
				"Error \n La resolution X comprend un charactère invalide \n");
			i++;
		}
		i = 0;
		while (resolution[2][i])
		{
			if (ft_isdigit(resolution[2][i]) == 0)
				message_map_invalid(parsing,
				"Error \n La resolution Y comprend un charactère invalide \n");
			i++;
		}
		map->resolution[0] = ft_atoi(resolution[1]);
		map->resolution[1] = ft_atoi(resolution[2]);
		if (map->resolution[0] == 0 |
			map->resolution[1] == 0)
			message_map_invalid(parsing,
			"Error \n Une des résolutions est égale a zero \n");
	}
}

int		ft_parse_resolution(t_parsing *parsing, t_map *map)
{
	char	**resolution;
	int		i;

	parsing->param_line_valid = 1;
	if (parsing->resolution_encountered == 1)
		message_map_invalid(parsing,
		"Error\nLa ligne de param RESOLUTION est presente deux fois");
	parsing->resolution_encountered = 1;
	if (!(resolution = ft_split(parsing->lign, ' ')))
		return (0);
	i = 0;
	if (!resolution[2] | !resolution[1] | !resolution[0])
		message_map_invalid(parsing,
		"Error \nLa ligne de param R n'est pas correctement rédigée \n");
	if (resolution[3] != 0)
		message_map_invalid(parsing,
		"Error \nLa ligne de param R n'est pas correctement rédigée \n");
	if ((resolution[0][0] != 'R') | resolution[0][1])
		message_map_invalid(parsing,
		"Error \nLa ligne de param R n'est pas correctement rédigée \n");
	ft_parse_resolution_2(parsing, resolution, i, map);
	free_split(resolution);
	return (1);
}

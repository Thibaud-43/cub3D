/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:09:14 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 16:58:29 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		ft_check_coma_floor(t_parsing *parsing)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (parsing->lign[i])
		if (parsing->lign[i++] == ',')
			count++;
	if (count != 2)
		message_map_invalid(parsing,
		"Error\n il y a trop de virgules dans FLOOR");
}

void		ft_parse_floor_2(t_parsing *parsing,
char **floor, char **rgb, t_map *map)
{
	if ((!rgb[1]) | (rgb[2] != 0))
		message_map_invalid(parsing,
		"Error \n La ligne de param FLOOR n'est pas correctement rédigée \n");
	map->floor[0] = ft_atoi(rgb[1]);
	map->floor[1] = ft_atoi(floor[1]);
	map->floor[2] = ft_atoi(floor[2]);
	if ((map->floor[0] < 0 | map->floor[0] > 255)
		| (map->floor[1] < 0 | map->floor[1] > 255)
		| (map->floor[2] < 0 | map->floor[2] > 255))
		message_map_invalid(parsing,
		"Error \n Le code RGB de param FLOOR n'est pas correctement rédigé \n");
}

int			ft_parse_floor(t_parsing *parsing, t_map *map)
{
	char	**floor;
	char	**rgb;
	int		i;
	int		k;

	i = 0;
	k = 0;
	parsing->param_line_valid = 1;
	ft_check_coma_floor(parsing);
	if (parsing->f_encountered == 1)
		message_map_invalid(parsing,
		"Error \n La ligne de param FLOOR est présente deux fois\n");
	parsing->f_encountered = 1;
	if (!(floor = ft_split(parsing->lign, ',')))
		return (0);
	if (!floor[0] | !floor[1] | !floor[2])
		message_map_invalid(parsing,
		"Error \n La ligne de param FLOOR n'est pas correctement rédigée \n");
	if (!(rgb = ft_split(floor[0], ' ')))
		return (0);
	ft_parse_floor_2(parsing, floor, rgb, map);
	free_split(rgb);
	free_split(floor);
	return (1);
}

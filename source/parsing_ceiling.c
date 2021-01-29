/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ceiling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:09:14 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/29 11:20:51 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		ft_check_coma(t_parsing *parsing)
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
		"Error\n il y a trop de virgules dans CEILING");
}

void		ft_parse_ceiling_2(t_parsing *parsing,
char **ceiling, char **rgb, t_map *map)
{
	if ((!rgb[1]) | (rgb[2] != 0))
		message_map_invalid(parsing,
		"Error \n La ligne de param CEILING n'est pas bien rédigée \n");
	map->ceiling[0] = ft_atoi(rgb[1]);
	map->ceiling[1] = ft_atoi(ceiling[1]);
	map->ceiling[2] = ft_atoi(ceiling[2]);
	if ((map->ceiling[0] < 0 | map->ceiling[0] > 255)
		| (map->ceiling[1] < 0 | map->ceiling[1] > 255)
		| (map->ceiling[2] < 0 | map->ceiling[2] > 255))
		message_map_invalid(parsing,
		"Error\n Le code rgb n'est pas valide \n");
}

int			ft_parse_ceiling(t_parsing *parsing, t_map *map)
{
	char	**ceiling;
	char	**rgb;
	int		i;
	int		k;

	i = 0;
	k = 0;
	parsing->param_line_valid = 1;
	ft_check_coma(parsing);
	if (parsing->c_encountered == 1)
		message_map_invalid(parsing,
		"Error \n La ligne de param CEILING est présente deux fois\n");
	parsing->c_encountered = 1;
	if (!(ft_check_ch(parsing->lign, "C ,0123456789")))
		message_map_invalid(parsing,
		"Error \n charactere invalide dans CEILING\n");
	if (!(ceiling = ft_split(parsing->lign, ',')))
		return (0);
	if (!ceiling[0] | !ceiling[1] | !ceiling[2])
		message_map_invalid(parsing,
		"Error \n La ligne de param CEILING n'est pas correctement rédigée \n");
	if (!(rgb = ft_split(ceiling[0], ' ')))
		return (0);
	ft_parse_ceiling_2(parsing, ceiling, rgb, map);
	free_split(rgb);
	free_split(ceiling);
	return (1);
}

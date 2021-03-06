/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:22:09 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/29 09:00:07 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_initialize_map_struc(t_p_map *p_map)
{
	p_map->k = 1;
	p_map->z = 1;
}

int		ft_mallloc_matrice(t_parsing *parsing, t_map *map)
{
	int i;

	i = 0;
	if (!(map->matrice = malloc(sizeof(char *)
		* (parsing->nb_lines_map + 3))))
		return (0);
	while (i < parsing->nb_lines_map + 2)
	{
		if (!(map->matrice[i] = malloc(sizeof(char *)
			* (parsing->line_map_len_max + 3))))
			return (0);
		i++;
	}
	return (1);
}

int		ft_init_matrice(t_parsing *parsing, t_map *map)
{
	int i;

	i = 0;
	if (!(ft_mallloc_matrice(parsing, map)))
		return (0);
	while (i < (parsing->line_map_len_max + 2))
	{
		map->matrice[0][i] = ' ';
		i++;
	}
	map->matrice[0][i] = 0;
	i = 0;
	while (i < (parsing->line_map_len_max + 2))
	{
		map->matrice[parsing->nb_lines_map + 1][i] = ' ';
		i++;
	}
	map->matrice[parsing->nb_lines_map + 1][i] = 0;
	return (1);
}

void	ft_parse_map_advanced_3(t_parsing *parsing, t_p_map *p_map, t_map *map)
{
	while ((p_map->ret = get_next_line(p_map->fd, &parsing->lign)))
	{
		if (p_map->k >= parsing->line_num_begin_map)
		{
			p_map->i = 0;
			map->matrice[p_map->z][p_map->i] = ' ';
			(p_map->i)++;
			while (parsing->lign[p_map->i - 1])
			{
				map->matrice[p_map->z][p_map->i] =
				parsing->lign[p_map->i - 1];
				(p_map->i)++;
			}
			while ((p_map->i) <= (parsing->line_map_len_max + 1))
			{
				map->matrice[p_map->z][p_map->i] = ' ';
				(p_map->i)++;
			}
			map->matrice[p_map->z][p_map->i] = 0;
			(p_map->z)++;
		}
		free(parsing->lign);
		(p_map->k)++;
	}
}

int		ft_parse_map_advanced(t_parsing *parsing, char **argv, t_map *map)
{
	t_p_map	p_map;

	ft_initialize_map_struc(&p_map);
	p_map.fd = open(argv[1], O_RDONLY);
	if (p_map.fd < 0)
		return (0);
	if (ft_init_matrice(parsing, map) == 0)
		return (0);
	ft_parse_map_advanced_3(parsing, &p_map, map);
	free(parsing->lign);
	map->matrice[(p_map.z) + 1] = 0;
	ft_parse_map_advanced_2(parsing, map);
	close((p_map.fd));
	return (1);
}

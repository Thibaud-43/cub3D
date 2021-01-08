/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:22:09 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 12:10:03 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_initialize_map_struc(t_p_map *p_map)
{
	p_map->k = 1;
	p_map->z = 1;
}

int	ft_init_matrice(t_parsing *parsing)
{
	int i;

	i = 0;
	if (!(parsing->matrice = malloc(sizeof(char *)
		* (parsing->nb_lines_map + 3))))
		return (0);
	while (i < parsing->nb_lines_map + 2)
	{
		if (!(parsing->matrice[i] = malloc(sizeof(char *)
			* (parsing->line_map_len_max + 3))))
			return (0);
		i++;
	}
	i = 0;
	while (i < (parsing->line_map_len_max + 2))
	{
		parsing->matrice[0][i] = ' ';
		i++;
	}
	parsing->matrice[0][i] = 0;
	i = 0;
	while (i < (parsing->line_map_len_max + 2))
	{
		parsing->matrice[parsing->nb_lines_map + 1][i] = ' ';
		i++;
	}
	parsing->matrice[parsing->nb_lines_map + 1][i] = 0;
	return (1);
}

int	ft_parse_map_advanced(t_parsing *parsing, char **argv)
{
	t_p_map	p_map;	

	ft_initialize_map_struc(&p_map);
	p_map.fd = open(argv[1], O_RDONLY);
	if (p_map.fd < 0)
		return (0);
	if (ft_init_matrice(parsing) == 0)
		return (0);
	while ((p_map.ret = get_next_line(p_map.fd, &parsing->lign)))
	{
		if (p_map.k >= parsing->line_num_begin_map)
		{
			p_map.i = 0;
			parsing->matrice[p_map.z][p_map.i] = ' ';
			(p_map.i)++;
			while (parsing->lign[p_map.i - 1])
			{
				parsing->matrice[p_map.z][p_map.i] = parsing->lign[p_map.i - 1];
				(p_map.i)++;
			}
			while ((p_map.i) <= (parsing->line_map_len_max + 1))
			{
				parsing->matrice[p_map.z][p_map.i] = ' ';
				(p_map.i)++;
			}
			parsing->matrice[p_map.z][p_map.i] = 0;
			(p_map.z)++;
		}
		free(parsing->lign);
		(p_map.k)++;
	}
	free(parsing->lign);
	parsing->matrice[(p_map.z) + 1] = 0;
	ft_parse_map_advanced_2(parsing);
	ft_print_matrice(parsing);
	close((p_map.fd));
	return (1);
}

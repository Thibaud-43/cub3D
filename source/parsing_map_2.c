/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:22:09 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 10:24:27 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_init_matrice(t_parsing *parsing)
{
	int i;

	i = 0;
	if(!(parsing->matrice = malloc(sizeof(char *) * (parsing->nb_lines_map + 3))))
		return (0);
	while(i < parsing->nb_lines_map + 2)
	{
		if(!(parsing->matrice[i] = malloc(sizeof(char *) * (parsing->line_map_len_max + 3))))
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
	int	fd;
	int	ret;
	int	k;
	int	i;
	int	z;

	k = 1;
	z = 1;
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		return (0);
	if (ft_init_matrice(parsing) == 0)
		return (0);
	while((ret = get_next_line(fd, &parsing->lign)))
	{
		if (k >= parsing->line_num_begin_map)
		{
			i = 0;
			parsing->matrice[z][i] = ' ';
			i++;
			while (parsing->lign[i - 1])
			{
				parsing->matrice[z][i] = parsing->lign[i - 1];
				i++;
			}
			while ((i) <= (parsing->line_map_len_max + 1))
			{
				parsing->matrice[z][i] = ' ';
				i++;
			}
			parsing->matrice[z][i] = 0;
			z++;
		}
		free(parsing->lign);		
		k++;
	}
	free(parsing->lign);		
	parsing->matrice[z + 1] = 0;
	ft_parse_map_advanced_2(parsing);
	ft_print_matrice(parsing);
	close(fd);
	return (1);
}


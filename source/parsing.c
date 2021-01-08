/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:26:50 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 10:27:22 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_parser(int argc, char **argv)
{
	t_parsing	parsing;
	int		fd;
	int		ret;
	int		i;
	int		k;

	ret = 1;
	k = 0;
	ft_init_parsing(&parsing);
	ft_check_args(&parsing, argc, argv);	
	if((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);	
	while ((ret = get_next_line(fd, &parsing.lign)))
	{
		i = 0;
		k++;
		parsing.param_line_valid = 0;
		while(parsing.lign[i] == ' ')
			i++;
		if(parsing.lign[i] == 'R' && parsing.map_encountered == 0)
		{
			if(!(ft_parse_resolution(&parsing)))
				return (0);
		}
		if(parsing.lign[i] == 'E' && parsing.lign[i + 1] == 'A' && parsing.map_encountered == 0) 
		{
			if(!(ft_parse_direction_ea(&parsing)))
				return (0);
		}
		if(parsing.lign[i] == 'W' && parsing.lign[i + 1] == 'E' && parsing.map_encountered == 0) 
		{
			if(!(ft_parse_direction_we(&parsing)))
				return (0);
		}
		if (parsing.lign[i] == 'S' && parsing.lign[i + 1] == 'O' && parsing.map_encountered == 0) 
		{
			if(!(ft_parse_direction_so(&parsing)))
				return (0);
		}
		if (parsing.lign[i] == 'N' && parsing.lign[i + 1] == 'O' && parsing.map_encountered == 0)
		{
			if(!(ft_parse_direction_no(&parsing)))
				return (0);
		}
		if (parsing.lign[i] == 'S' && parsing.lign[i + 1] == ' ' && parsing.map_encountered == 0)
		{
			if(!(ft_parse_sprite(&parsing)))
				return (0);
		}
		if (parsing.lign[i] == 'F' && parsing.map_encountered == 0)
		{
			if(!(ft_parse_floor(&parsing)))
				return (0);
		}
		if (parsing.lign[i] == 'C' && parsing.map_encountered == 0)
		{
			if(!(ft_parse_ceiling(&parsing)))
				return (0);
		}
		if(parsing.lign[i] == 0 && parsing.map_encountered == 1)
		{
			message_map_invalid(&parsing, "Error\n Présence d'une ligne vide au niveau de la map\n");
			parsing.param_line_valid = 1;
		}
		if(parsing.lign[i] == 0 && parsing.map_encountered == 0)
		{
			parsing.param_line_valid = 1;
		}

		if(parsing.lign[i] == '0' | parsing.lign[i] == '1')
		{
			if(!(ft_parse_map(&parsing, k)))
				return (0);
					
		}
		if(parsing.param_line_valid == 0)
		{

			message_map_invalid(&parsing, "Error\n Une ligne n'est pas correcte\n");
		}
		free(parsing.lign);
	}
	free(parsing.lign);
	ft_all_params(&parsing);
	ft_parse_map_advanced(&parsing, argv);
	close(fd);
//	printf("La map commence à la ligne numeros : %d\nLe nombre de ligne de la map est de : %d\nLa taille max de la ligne est de : %d\n", parsing.line_num_begin_map, parsing.nb_lines_map, parsing.line_map_len_max);
	return (parsing.is_valid);
}

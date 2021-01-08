/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:22:09 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 11:57:10 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_check_ch_map(t_parsing *parsing)
{
	int i;

	i = 0;
	while (parsing->lign[i])
	{
		if (parsing->lign[i] == 'N' | parsing->lign[i] == 'S'
			| parsing->lign[i] == 'E' | parsing->lign[i] == 'W')
		{
			if (parsing->player_found == 1)
				message_map_invalid(parsing,
				"Error\n Il y a plusieurs joueurs sur la map \n");
			else
				parsing->player_found = 1;
		}
		else if (!(parsing->lign[i] == ' ' | parsing->lign[i] == '0'
				| parsing->lign[i] == '1' | parsing->lign[i] == '2'))
			message_map_invalid(parsing,
			"Error\n La map est invalide\n");
		i++;
	}
}

int		ft_parse_map(t_parsing *parsing, int k)
{
	parsing->param_line_valid = 1;
	if (parsing->map_encountered == 0)
		parsing->line_num_begin_map = k;
	if (ft_strlen(parsing->lign) > parsing->line_map_len_max)
		parsing->line_map_len_max = ft_strlen(parsing->lign);
	parsing->nb_lines_map++;
	ft_check_ch_map(parsing);
	parsing->map_encountered = 1;
	return (1);
}

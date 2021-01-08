/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ceiling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:09:14 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 10:11:30 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_parse_ceiling(t_parsing *parsing)
{
	char	**ceiling;
	char	**rgb;
	int	rgb_tab[3];
	int	i;
	int	k;

	i = 0;
	k = 0;
	parsing->param_line_valid = 1;
	if (parsing->c_encountered == 1)
		message_map_invalid(parsing, "Error \n La ligne de param CEILING est présente deux fois\n");
	parsing->c_encountered = 1;
	if(!(ceiling = ft_split(parsing->lign, ',')))
		return (0);
	if(!ceiling[0] | !ceiling[1] | !ceiling[2])
		message_map_invalid(parsing, "Error \n La ligne de param CEILING n'est pas correctement rédigée \n");
	if(!(rgb = ft_split(ceiling[0], ' ')))
		return (0);
	if((!rgb[1]) | (rgb[2] != 0))
		message_map_invalid(parsing, "Error \n La ligne de param CEILING n'est pas correctement rédigée \n");
	rgb_tab[0] = ft_atoi(rgb[1]);
	rgb_tab[1] = ft_atoi(ceiling[1]);
	rgb_tab[2] = ft_atoi(ceiling[2]);
	if((rgb_tab[0] < 0 | rgb_tab[0] > 255) | (rgb_tab[1] < 0 | rgb_tab[1] > 255) | (rgb_tab[2] < 0 | rgb_tab[2] > 255))
		message_map_invalid(parsing, "Error \n Le code RGB de param CEILING n'est pas correctement rédigé \n");
	free_split(rgb);	
	free_split(ceiling);
	return(1);
}

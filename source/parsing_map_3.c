/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:22:09 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/27 13:32:28 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		ft_check_vertical(int i, int k, t_map *map, int *error)
{
	int tmp_i;

	tmp_i = i;
	while (map->matrice[i][k] != '1')
	{
		if (map->matrice[i][k] == ' ' | map->matrice[i][k] == 0)
		{
			*error = 1;
			break ;
		}
		i--;
	}
	i = tmp_i;
	while (map->matrice[i][k] != '1')
	{
		if (map->matrice[i][k] == ' ' | map->matrice[i][k] == 0)
		{
			*error = 1;
			break ;
		}
		i++;
	}
}

void		ft_check_horizontal(int k, int i, t_map *map, int *error)
{
	int tmp_k;

	tmp_k = k;
	while (map->matrice[i][k] != '1')
	{
		if (map->matrice[i][k] == ' ' | map->matrice[i][k] == 0)
		{
			*error = 1;
			break ;
		}
		k--;
	}
	k = tmp_k;
	while (map->matrice[i][k] != '1')
	{
		if (map->matrice[i][k] == ' ' | map->matrice[i][k] == 0)
		{
			*error = 1;
			break ;
		}
		k++;
	}
}

void		ft_check_comformity(int i, int k, t_map *map, int *error)
{
	ft_check_vertical(i, k, map, error);
	ft_check_horizontal(k, i, map, error);
}

void		ft_set_player_pos(t_map *map, int i, int k)
{
	map->player_x = (double)k + 0.5;
	map->player_y = (double)i + 0.5;
}

void		ft_parse_map_advanced_2(t_parsing *parsing, t_map *map)
{
	int i;
	int k;
	int error;

	i = 0;
	error = 0;
	while (map->matrice[i])
	{
		k = 0;
		while (map->matrice[i][k])
		{
			if (map->matrice[i][k] == '0' | map->matrice[i][k] == '2'
			| map->matrice[i][k] == 'N' | map->matrice[i][k] == 'S'
			| map->matrice[i][k] == 'W' | map->matrice[i][k] == 'E')
				ft_check_comformity(i, k, map, &error);
			if (map->matrice[i][k] == 'N' | map->matrice[i][k] == 'S'
			| map->matrice[i][k] == 'W' | map->matrice[i][k] == 'E')
				ft_set_player_pos(map, i, k);
			k++;
		}
		i++;
	}
	if (error == 1)
		message_map_invalid(parsing, "Error\n La map est invalide\n");
}

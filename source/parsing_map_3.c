/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:22:09 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 16:02:26 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		ft_check_vertical(int i, int tmp_i, t_parsing *parsing, int *error)
{
	while (parsing->matrice[i][k] != '1')
	{
		if (parsing->matrice[i][k] == ' ' | parsing->matrice[i][k] == 0)
		{
			*error = 1;
			break ;
		}
		i--;
	}
	i = tmp_i;
	while (parsing->matrice[i][k] != '1')
	{
		if (parsing->matrice[i][k] == ' ' | parsing->matrice[i][k] == 0)
		{
			*error = 1;
			break ;
		}
		i++;
	}
}

void		ft_check_horizontal(int k, int tmp_k, t_parsing *parsing, int error)
{
	while (parsing->matrice[i][k] != '1')
	{
		if (parsing->matrice[i][k] == ' ' | parsing->matrice[i][k] == 0)
		{
			*error = 1;
			break ;
		}
		k--;
	}
	k = tmp_k;
	while (parsing->matrice[i][k] != '1')
	{
		if (parsing->matrice[i][k] == ' ' | parsing->matrice[i][k] == 0)
		{
			*error = 1;
			break ;
		}
		k++;
	}
}

void		ft_check_comformity(int i, int k, t_parsing *parsing, int *error)
{
	int tmp_i;
	int tmp_k;

	tmp_i = i;
	tmp_k = k;
	ft_check_vertical(i, tmp_i, parsing, error);
	ft_check_horizontal(k, tmp_k, parsing, error);
}

void		ft_parse_map_advanced_2(t_parsing *parsing)
{
	int i;
	int k;
	int error;

	i = 0;
	error = 0;
	while (parsing->matrice[i])
	{
		k = 0;
		while (parsing->matrice[i][k])
		{
			if (parsing->matrice[i][k] == '0' | parsing->matrice[i][k] == '2'
			| parsing->matrice[i][k] == 'N' | parsing->matrice[i][k] == 'S'
			| parsing->matrice[i][k] == 'O' | parsing->matrice[i][k] == 'E')
				ft_check_comformity(i, k, parsing, &error);
			k++;
		}
		i++;
	}
	if (error == 1)
		message_map_invalid(parsing, "Error\n La map est invalide\n");
}

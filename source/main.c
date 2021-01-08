/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:47:07 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/08 17:53:31 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_initialize_map(t_map *map)
{
	map->matrice = NULL;
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->sprite = NULL;
	map->ceiling[0] = 0;
	map->ceiling[1] = 0;
	map->ceiling[2] = 0;
	map->floor[0] = 0;
	map->floor[1] = 0;
	map->floor[2] = 0;
	map->resolution[0] = 0;
	map->resolution[1] = 0;
}

void	ft_free_map(t_map *map)
{
	free(map->no);
	free(map->so);
	free(map->ea);
	free(map->we);
	free(map->sprite);
	ft_print_matrice(map);
}

int		main(int argc, char **argv)
{
	t_map	map;
	ft_initialize_map(&map);
	printf("Valeur de retour: %d \n", ft_parser(argc, argv, &map));
	printf("Valeur de no : %s \n", map->no);
	printf("Valeur de so : %s \n", map->so);
	printf("Valeur de ea : %s \n", map->ea);
	printf("Valeur de we : %s \n", map->we);
	printf("Valeur de SPRITE : %s \n", map->sprite);
	printf("Valeur de ceiling : %d / %d / %d \n", map->ceiling[0], map->ceiling[1], map->ceiling[2]);
	printf("Valeur de floor : %d / %d / %d \n", map->floor[0], map->floor[1], map->floor[2]);
	printf("Valeur de resolution : %d / %d \n", map->resolution[0], map->resolution[1]);
	ft_free_map(&map);
	return (1);
}

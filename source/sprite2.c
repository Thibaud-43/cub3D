/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:47:07 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/29 12:22:21 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_setpos_sprites(t_map *map)
{
	int i;
	int k;
	int s;

	i = 0;
	s = 0;
	while (map->matrice[i])
	{
		k = 0;
		while (map->matrice[i][k])
		{
			if (map->matrice[i][k] == '2')
			{
				map->spr.pos[s].x = (double)i + 0.5;
				map->spr.pos[s].y = (double)k + 0.5;
				s++;
			}
			k++;
		}
		i++;
	}
}

void	ft_dist_sprites(t_map *map)
{
	int i;

	i = 0;
	while (i < map->spr.nbr)
	{
		map->spr.dist[i] = ((map->ray.posx - map->spr.pos[i].x) *
		(map->ray.posx - map->spr.pos[i].x)) +
		((map->ray.posy - map->spr.pos[i].y) *
		(map->ray.posy - map->spr.pos[i].y));
		i++;
	}
}

void	ft_transverse(t_map *map, int i, int k)
{
	double		tmpdist;
	double		tmpx;
	double		tmpy;

	tmpdist = map->spr.dist[i];
	map->spr.dist[i] = map->spr.dist[k];
	map->spr.dist[k] = tmpdist;
	tmpx = map->spr.pos[i].x;
	map->spr.pos[i].x = map->spr.pos[k].x;
	map->spr.pos[k].x = tmpx;
	tmpy = map->spr.pos[i].y;
	map->spr.pos[i].y = map->spr.pos[k].y;
	map->spr.pos[k].y = tmpy;
}

void	ft_order_sprites(t_map *map)
{
	int i;
	int k;

	i = 0;
	while (i < map->spr.nbr)
	{
		k = i + 1;
		while (k < map->spr.nbr)
		{
			if (map->spr.dist[i] < map->spr.dist[k])
				ft_transverse(map, i, k);
			k++;
		}
		i++;
	}
}

void	ft_count_sprites(t_map *map)
{
	int		i;
	int		k;

	i = 0;
	map->spr.nbr = 0;
	while (map->matrice[i])
	{
		k = 0;
		while (map->matrice[i][k])
		{
			if (map->matrice[i][k] == '2')
				map->spr.nbr++;
			k++;
		}
		i++;
	}
}

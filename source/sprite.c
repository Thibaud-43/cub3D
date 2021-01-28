/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:47:07 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/28 17:23:59 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_dist_sprites(t_map *map)
{
	int i;

	i = 0;
	while (i < map->spr.nbr)
	{
		map->spr.dist[i] = ((map->ray.posX - map->spr.pos[i].x) * (map->ray.posX - map->spr.pos[i].x)) + ((map->ray.posY - map->spr.pos[i].y) * (map->ray.posY - map->spr.pos[i].y));
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
				//map->matrice[i][k] = '0';
				s++;
			}
			k++;
		}
		i++;
	}
}

int		ft_init_sprites(t_map *map)
{
	ft_count_sprites(map);
	if (!(map->spr.dist = malloc(sizeof(double) * map->spr.nbr)))
		return 0;
	if (!(map->spr.pos = malloc(sizeof(t_pos) * map->spr.nbr)))
		return 0;
	ft_setpos_sprites(map);
	return (1);
}

void	ft_init_sprite_engine(t_map *map, int i)
{
	map->spr.spriteX = map->spr.pos[i].x - map->ray.posX;
	map->spr.spriteY = map->spr.pos[i].y - map->ray.posY;
	map->spr.invDet = 1.0 / (map->ray.planeX * map->ray.dirY - map->ray.dirX * map->ray.planeY);
	map->spr.transformX = map->spr.invDet * (map->ray.dirY * map->spr.spriteX - map->ray.dirX * map->spr.spriteY);
	map->spr.transformY = map->spr.invDet * (-map->ray.planeY * map->spr.spriteX + map->ray.planeX * map->spr.spriteY);
	map->spr.spriteScreenX = (int)((map->resolution[0] / 2) * (1 + map->spr.transformX / map->spr.transformY));	
	map->spr.spriteHeight = abs((int)(map->resolution[1] / map->spr.transformY));
	map->spr.drawStartY = -map->spr.spriteHeight / 2 + map->resolution[1] / 2;
	if (map->spr.drawStartY < 0)
		map->spr.drawStartY = 0;
	map->spr.drawEndY = map->spr.spriteHeight / 2 + map->resolution[1] / 2;
	if (map->spr.drawEndY >= map->resolution[1])
		map->spr.drawEndY = map->resolution[1] - 1;
	map->spr.spriteWidth = abs((int)(map->resolution[1] / map->spr.transformY));
	map->spr.drawStartX = -map->spr.spriteWidth / 2 + map->spr.spriteScreenX;
	if (map->spr.drawEndX < 0)
		map->spr.drawEndX = 0;
	map->spr.drawEndX = map->spr.spriteWidth / 2 + map->spr.spriteScreenX;
	if (map->spr.drawStartX >= map->resolution[0])
		map->spr.drawStartX = map->resolution[0] - 1;
}

void	ft_sprites(t_map *map)
{
	int		i;
	int		k;
	int		z;

	i = 0;
	ft_dist_sprites(map);
	ft_order_sprites(map);
	while (i < map->spr.nbr)
	{
		ft_init_sprite_engine(map, i);
		k = map->spr.drawStartX;
		while (k < map->spr.drawEndX)
		{
			map->spr.texX = (int)((256 * (k - (-map->spr.spriteWidth / 2 + map->spr.spriteScreenX)) * map->texture[4].width / map->spr.spriteWidth) / 256);
			if (map->spr.transformY > 0 && k > 0 && k < map->resolution[0])
			{
				z = map->spr.drawStartY;
				while (z < map->spr.drawEndY)
				{
					map->spr.d =  (z) * 256 - map->resolution[1] * 128 + map->spr.spriteHeight * 128;
					map->spr.texY = ((map->spr.d * map->texture[4].height) / map->spr.spriteHeight) / 256;
					if (map->texture[4].img->addr[map->spr.texY  * map->texture[4].img->line_length / 4 + map->spr.texX] != 0)
					{
						map->img.addr[z * map->img.line_length / 4 + k] = map->texture[4].img->addr[map->spr.texY * map->texture[4].img->line_length / 4 + map->spr.texX];
					}
					z++;
				}
			}
			k++;
		}
		i++;
	}
}

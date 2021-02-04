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

int		ft_init_sprites(t_map *map)
{
	ft_count_sprites(map);
	if (!(map->spr.dist = malloc(sizeof(double) * (map->spr.nbr + 1))))
		return (0);
	if (!(map->spr.pos = malloc(sizeof(t_pos) * (map->spr.nbr + 1))))
		return (0);
	map->spr.dist[map->spr.nbr] = 0;
	map->spr.pos[map->spr.nbr].x = 0;
	map->spr.pos[map->spr.nbr].y = 0;
	ft_setpos_sprites(map);
	return (1);
}

void	ft_init_sprite_engine2(t_map *map, int i)
{
	if (map->spr.drawstarty < 0)
		map->spr.drawstarty = 0;
	map->spr.drawendy = map->spr.spriteheight
	/ 2 + map->resolution[1] / 2;
	if (map->spr.drawendy >= map->resolution[1])
		map->spr.drawendy = map->resolution[1] - 1;
	map->spr.spritewidth = abs((int)(map->resolution[1]
	/ map->spr.transformy));
	map->spr.drawstartx = -map->spr.spritewidth / 2 + map->spr.spritescreenx;
	if (map->spr.drawendx < 0)
		map->spr.drawendx = 0;
	map->spr.drawendx = map->spr.spritewidth
	/ 2 + map->spr.spritescreenx;
	if (map->spr.drawstartx >= map->resolution[0])
		map->spr.drawstartx = map->resolution[0] - 1;
}

void	ft_init_sprite_engine(t_map *map, int i)
{
	map->spr.spritex = map->spr.pos[i].x - map->ray.posx;
	map->spr.spritey = map->spr.pos[i].y - map->ray.posy;
	map->spr.invdet = 1.0 / (map->ray.planex *
	map->ray.diry - map->ray.dirx * map->ray.planey);
	map->spr.transformx = map->spr.invdet * (map->ray.diry
	* map->spr.spritex - map->ray.dirx * map->spr.spritey);
	map->spr.transformy = map->spr.invdet * (-map->ray.planey
	* map->spr.spritex + map->ray.planex * map->spr.spritey);
	map->spr.spritescreenx = (int)((map->resolution[0] / 2)
	* (1 + map->spr.transformx / map->spr.transformy));
	map->spr.spriteheight = abs((int)(map->resolution[1]
	/ map->spr.transformy));
	map->spr.drawstarty = -map->spr.spriteheight
	/ 2 + map->resolution[1] / 2;
	ft_init_sprite_engine2(map, i);
}

void	ft_sprites2(t_map *map, int *i, int *k, int *z)
{
	while ((*k) < (map->spr.drawendx))
	{
		map->spr.texx = (int)((256 * ((*k) - (-map->spr.spritewidth
		/ 2 + map->spr.spritescreenx)) * map->texture[4].width
		/ map->spr.spritewidth) / 256);
		if (map->spr.transformy > 0 && (*k) > 0 && (*k) < map->resolution[0])
		{
			(*z) = map->spr.drawstarty;
			while ((*z) < (map->spr.drawendy))
			{
				map->spr.d = (*z) * 256 - map->resolution[1] *
				128 + map->spr.spriteheight * 128;
				map->spr.texy = ((map->spr.d * map->texture[4].height)
				/ map->spr.spriteheight) / 256;
				if (map->texture[4].addr[map->spr.texy *
				map->texture[4].img->line_length / 4 + map->spr.texx] != 0)
					map->img.addr[*z * map->img.line_length / 4 + (*k)] =
					map->texture[4].addr[map->spr.texy *
					map->texture[4].img->line_length / 4 + map->spr.texx];
				(*z)++;
			}
		}
		(*k)++;
	}
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
		k = map->spr.spritewidth + 1;
		ft_sprites2(map, &i, &k, &z);
		i++;
	}
}

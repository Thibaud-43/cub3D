/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:02:15 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/27 13:11:53 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_init_raycasting_2(t_map *map)
{
	map->ray.camerax = 0;
	map->ray.raydirx = 0;
	map->ray.raydiry = 0;
	map->ray.mapx = 0;
	map->ray.mapy = 0;
	map->ray.sidedistx = 0;
	map->ray.sidedisty = 0;
	map->ray.deltadistx = 0;
	map->ray.deltadisty = 0;
	map->ray.stepx = 0;
	map->ray.stepy = 0;
	map->ray.hit = 0;
	map->ray.side = 0;
	map->ray.perpwalldist = 0;
	map->ray.lineheight = 0;
	map->ray.drawstart = 0;
	map->ray.drawend = 0;
}

void		ft_init_raycasting_3(t_map *map)
{
	map->ray.camerax = 2 * map->ray.x / ((double)map->ray.width) - 1;
	map->ray.raydirx = map->ray.dirx + map->ray.planex * map->ray.camerax;
	map->ray.raydiry = map->ray.diry + map->ray.planey * map->ray.camerax;
	map->ray.mapx = (int)map->ray.posx;
	map->ray.mapy = (int)map->ray.posy;
	map->ray.hit = 0;
	map->ray.perpwalldist = 0;
}

void		ft_init_deltadist(t_map *map)
{
	if (map->ray.raydiry == 0)
		map->ray.deltadistx = 0;
	else if (map->ray.raydirx == 0)
		map->ray.deltadistx = 1;
	else
		map->ray.deltadistx = fabs(1 / map->ray.raydirx);
	if (map->ray.raydirx == 0)
		map->ray.deltadisty = 0;
	else if (map->ray.raydiry == 0)
		map->ray.deltadisty = 1;
	else
		map->ray.deltadisty = fabs(1 / map->ray.raydiry);
}

void		ft_init_dist(t_map *map)
{
	if (map->ray.raydirx < 0)
	{
		map->ray.stepx = -1;
		map->ray.sidedistx = (map->ray.posx - map->ray.mapx)
		* map->ray.deltadistx;
	}
	else
	{
		map->ray.stepx = 1;
		map->ray.sidedistx = (map->ray.mapx + 1.0 - map->ray.posx)
		* map->ray.deltadistx;
	}
	if (map->ray.raydiry < 0)
	{
		map->ray.stepy = -1;
		map->ray.sidedisty = (map->ray.posy - map->ray.mapy)
		* map->ray.deltadisty;
	}
	else
	{
		map->ray.stepy = 1;
		map->ray.sidedisty = (map->ray.mapy + 1.0 - map->ray.posy)
		* map->ray.deltadisty;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:02:15 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/12 11:56:11 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		ft_init_raycasting_1(t_map *map)
{
	map->ray.dirX = -1;
	map->ray.posY = map->player_x;
	map->ray.posX = map->player_y;
	map->ray.dirY = 0;
	map->ray.planeX = 0;
	map->ray.planeY = 0.66;
	map->ray.width = map->resolution[0];
	map->ray.height = map->resolution[1];
}

void		ft_init_raycasting_2(t_map *map)
{
	map->ray.cameraX = 0;
	map->ray.rayDirX = 0;
	map->ray.rayDirY = 0;
	map->ray.mapX = 0;
	map->ray.mapY = 0;
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
	map->ray.width = map->resolution[0];
	map->ray.height = map->resolution[1];
}

void		ft_init_raycasting_3(t_map *map)
{
	map->ray.cameraX = 2 * map->ray.x / ((double)map->ray.width) - 1;
	map->ray.rayDirX = map->ray.dirX + map->ray.planeX * map->ray.cameraX;
	map->ray.rayDirY = map->ray.dirY + map->ray.planeY * map->ray.cameraX;
	map->ray.mapX = (int)map->ray.posX;
	map->ray.mapY = (int)map->ray.posY;
	map->ray.hit = 0;
	map->ray.perpwalldist = 0;
}

void		ft_init_deltadist(t_map *map)
{
	if (map->ray.rayDirY == 0)
		map->ray.deltadistx = 0;
	else if (map->ray.rayDirX == 0)
		map->ray.deltadistx = 1;
	else
		map->ray.deltadistx = fabs(1 / map->ray.rayDirX);
	if (map->ray.rayDirX == 0)
		map->ray.deltadisty = 0;
	else if (map->ray.rayDirY == 0)
		map->ray.deltadisty = 1;
	else
		map->ray.deltadisty = fabs(1 / map->ray.rayDirY);
}

void		ft_init_dist(t_map *map)
{
	if (map->ray.rayDirX < 0)
	{
		map->ray.stepx = -1;
		map->ray.sidedistx = (map->ray.posX - map->ray.mapX)
		* map->ray.deltadistx;
	}
	else
	{
		map->ray.stepx = 1;
		map->ray.sidedistx = (map->ray.mapX + 1.0 - map->ray.posX)
		* map->ray.deltadistx;
	}
	if (map->ray.rayDirY < 0)
	{
		map->ray.stepy = -1;
		map->ray.sidedisty = (map->ray.posY - map->ray.mapY)
		* map->ray.deltadisty;
	}
	else
	{
		map->ray.stepy = 1;
		map->ray.sidedisty = (map->ray.mapY + 1.0 - map->ray.posY)
		* map->ray.deltadisty;
	}
}

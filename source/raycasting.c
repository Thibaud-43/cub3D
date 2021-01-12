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


void	ft_init_raycasting_1(t_map *map)
{
	map->ray.dirX = -1;
	map->ray.dirY = 0;
	map->ray.planeX = 0;
	map->ray.planeY = 0.66;
	map->ray.width = map->resolution[0];
	map->ray.height = map->resolution[1];
}

void	ft_init_raycasting_2(t_map *map)
{
	map->ray.posY = map->player_x;
	map->ray.posX = map->player_y;
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
void 	ft_draw_vertical_line(int x, t_ray *ray, t_map *map)
{
	int i;

	i = 0;
	while (i < ray->drawstart)
	{
		map->img.addr[i * map->img.line_length / 4 + x] = 0x000000;
		i++;
	}
	while (ray->drawstart <= ray->drawend)
	{
		map->img.addr[ray->drawstart * map->img.line_length / 4 + x] = 0xFCBA03;
		ray->drawstart++;
		i++;
	}	
	while (i < ray->height)
	{
		map->img.addr[i * map->img.line_length / 4 + x] = 0x03FCCA;
		i++;
	}
}

int		ft_raycasting(t_map	*map)
{
	map->ray.x = 0;
	while (map->ray.x < 800)
	{
		ft_init_raycasting_2(map);
		map->ray.cameraX = 2 * map->ray.x / ((double)map->ray.width) - 1;
		map->ray.rayDirX = map->ray.dirX + map->ray.planeX * map->ray.cameraX;
		map->ray.rayDirY = map->ray.dirY + map->ray.planeY * map->ray.cameraX;
		map->ray.mapX = (int)map->ray.posX;
		map->ray.mapY = (int)map->ray.posY;
		map->ray.hit = 0;
		map->ray.perpwalldist = 0;
		if (map->ray.rayDirY == 0)
			map->ray.deltadistx = 0;
		else if (map->ray.rayDirX == 0)
			map->ray.deltadistx = 1;
		else
			map->ray.deltadistx = fabs(1 / map->ray.rayDirX);
		if (map->ray.rayDirX == 0)
			map->ray.deltadisty = 0;
		else if(map->ray.rayDirY == 0)
			map->ray.deltadisty = 1;
		else
			map->ray.deltadisty = fabs(1 / map->ray.rayDirY);
		if (map->ray.rayDirX < 0)
		{
			map->ray.stepx = -1;
			map->ray.sidedistx = (map->ray.posX - map->ray.mapX) * map->ray.deltadistx;
		}
		else
		{
			map->ray.stepx = 1;
			map->ray.sidedistx = (map->ray.mapX + 1.0 - map->ray.posX) * map->ray.deltadistx;
		}
		if (map->ray.rayDirY < 0)
		{
			map->ray.stepy = -1;
			map->ray.sidedisty = (map->ray.posY - map->ray.mapY) * map->ray.deltadisty;
		}
		else
		{
			map->ray.stepy = 1;
			map->ray.sidedisty = (map->ray.mapY + 1.0 - map->ray.posY) * map->ray.deltadisty;
		}
		while (map->ray.hit == 0)
		{
			if (map->ray.sidedistx < map->ray.sidedisty)
			{
				map->ray.sidedistx += map->ray.deltadistx;
				map->ray.mapX += map->ray.stepx;
				map->ray.side = 0;
			}
			else
			{
				map->ray.sidedisty += map->ray.deltadisty;
				map->ray.mapY += map->ray.stepy;
				map->ray.side = 1;
			}
			if (map->matrice[map->ray.mapX][map->ray.mapY] != '0')
				map->ray.hit = 1;
		}
		if (map->ray.side == 0)
			map->ray.perpwalldist = (map->ray.mapX - map->ray.posX + (1 - map->ray.stepx) / 2) / map->ray.rayDirX;
		else	
			map->ray.perpwalldist = (map->ray.mapY - map->ray.posY + (1 - map->ray.stepy) / 2) / map->ray.rayDirY;
		map->ray.lineheight = (int)(map->ray.height / map->ray.perpwalldist);
		map->ray.drawstart = -map->ray.lineheight / 2 + map->ray.height / 2;
		if (map->ray.drawstart < 0)
			map->ray.drawstart = 0;
		map->ray.drawend = map->ray.lineheight / 2 + map->ray.height / 2;
		if (map->ray.drawend >= map->ray.height | map->ray.drawend == 0)
			map->ray.drawend = map->ray.height - 1;

		ft_draw_vertical_line(map->ray.x, &map->ray, map);
		map->ray.x++;
	}
	mlx_put_image_to_window(map->vars.mlx, map->vars.win, map->img.img, 0, 0);
	return (1);
}

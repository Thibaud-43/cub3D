/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:02:15 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/12 11:44:38 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


typedef struct s_raycasting
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int		mapx;
	int		mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	double		perpwalldist;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		width;
	int		height;
	int		x;
}				t_ray;

void	ft_init_raycasting_struct(t_ray *ray, t_map *map)
{
	ray->posX = map->player_x;
	ray->posY = map->player_y;
	ray->dirX = 0;
	ray->dirY = 0;
	ray->planeX = 0;
	ray->planeY = 0;
	ray->cameraX = 0;
	ray->rayDirX = 0;
	ray->rayDirY = 0;
	ray->mapx = 0;
	ray->mapy = 0;
	ray->sidedistx = 0;
	ray->sidedisty = 0;
	ray->deltadistx = 0;
	ray->deltadisty = 0;
	ray->stepx = 0;
	ray->stepy = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->perpwalldist = 0;
	ray->lineheight = 0;
	ray->drawstart = 0;
	ray->drawend = 0;
	ray->x = 0;
	ray->width = map->resolution[0];
	ray->height = map->resolution[1];

}

int 	ft_draw_vertical_line(int x, t_ray *ray, t_map *map)
{
	int i;

	i = 0;
	while (i < ray->drawstart)
	{
		map->img.addr[x * map->img.line_length / 4 + i] = 0x000000;
		i++;
	}
	while (ray->drawstart <= ray->drawend)
	{
		map->img.addr[x * map->img.line_length / 4 + ray->drawstart] = 0xFCBA03;
		ray->drawstart++;
		i++;
	}	
	while (i < ray->height)
	{
		map->img.addr[x * map->img.line_length / 4 + i] = 0x03FCCA;
		i++;
	}
}

int		ft_raycasting(t_map	*map)
{
	t_ray	ray;

	ft_init_raycasting_struct(&ray, map);
	while (ray.x < ray.width)
	{
		ray.cameraX = 2 * x / double(ray.width) - 1;
		ray.rayDirX = ray.dirX + ray.planeX * ray.cameraX;
		ray.rayDirY = ray.dirY + ray.planeY * ray.cameraX;
		ray.mapX = map->player_x;
		ray.mapY = map->player_y;
		if (ray.rayDirX = 0)
			ray.deltadistX = 0;
		else
			ray.deltadistX = abs(1 / ray.rayDirX);
		if (ray.rayDirY = 0)
			ray.deltadistY = 0;
		else
			ray.deltadistY = abs(1 / ray.rayDirY);
		if (ray.rayDirX < 0)
		{
			ray.stepx = -1;
			ray.sidedistx = (ray.posX - ray.mapX) * ray.deltadistX;
		}
		else
		{
			ray.stepx = 1;
			ray.sidedistx = (ray.posX + 1.0 - ray.mapX) * ray.deltadistX;
		}
		if (ray.rayDirY < 0)
		{
			ray.stepy = -1;
			ray.sidedisty = (ray.posY - ray.mapY) * ray.deltadistY;
		}
		else
		{
			ray.stepy = 1;
			ray.sidedisty = (ray.posY + 1.0 - ray.mapY) * ray.deltadistY;
		}
		while (ray.hit == 0)
		{
			if (ray.sidedistX < ray.sidedistY)
			{
				ray.sidedistx += ray.deltadistX;
				ray.mapX += ray.stepX;
				side = 0;
			}
			else
			{
				ray.sidedistY += ray.deltadisty;
				ray.mapY += ray.stepY;
				ray.side = 1;
			}
			if (map->matrice[mapX][map] > 0)
				ray.hit = 1;
		}
		if (ray.side == 0)
			ray.perpWallDist = (ray.mapX - ray.posX + (1 - ray.stepX) / 2) / ray.rayDirX;
		else	
			ray.perpWallDist = (ray.mapY - ray.posY + (1 - ray.stepY) / 2) / ray.rayDirY;
		ft_draw_vertical_line(x, ray, map);
		ray.x++;
	}
	mlx_put_image_to_window(map->vars->mlx, map->vars->win, map->img->img, 0, 0);
}

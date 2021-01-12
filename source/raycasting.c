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
	int		mapX;
	int		mapY;
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
	ray->mapX = 0;
	ray->mapY = 0;
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

void 	ft_draw_vertical_line(int x, t_ray *ray, t_map *map)
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
		ray.cameraX = 2 * ray.x / ((double)ray.width) - 1;
		ray.rayDirX = ray.dirX + ray.planeX * ray.cameraX;
		ray.rayDirY = ray.dirY + ray.planeY * ray.cameraX;
		ray.mapX = map->player_x;
		ray.mapY = map->player_y;
		if (ray.rayDirX == 0)
			ray.deltadistx = 0;
		else
			ray.deltadistx = fabs(1 / ray.rayDirX);
		if (ray.rayDirY == 0)
			ray.deltadisty = 0;
		else
			ray.deltadisty = fabs(1 / ray.rayDirY);
		if (ray.rayDirX < 0)
		{
			ray.stepx = -1;
			ray.sidedistx = (ray.posX - ray.mapX) * ray.deltadistx;
		}
		else
		{
			ray.stepx = 1;
			ray.sidedistx = (ray.posX + 1.0 - ray.mapX) * ray.deltadistx;
		}
		if (ray.rayDirY < 0)
		{
			ray.stepy = -1;
			ray.sidedisty = (ray.posY - ray.mapY) * ray.deltadisty;
		}
		else
		{
			ray.stepy = 1;
			ray.sidedisty = (ray.posY + 1.0 - ray.mapY) * ray.deltadisty;
		}
		while (ray.hit == 0)
		{
			if (ray.sidedistx < ray.sidedisty)
			{
				ray.sidedistx += ray.deltadistx;
				ray.mapX += ray.stepx;
				ray.side = 0;
			}
			else
			{
				ray.sidedisty += ray.deltadisty;
				ray.mapY += ray.stepy;
				ray.side = 1;
			}
			if (map->matrice[ray.mapX][ray.mapY] > 0)
				ray.hit = 1;
		}
		if (ray.side == 0)
			ray.perpwalldist = (ray.mapX - ray.posX + (1 - ray.stepx) / 2) / ray.rayDirX;
		else	
			ray.perpwalldist = (ray.mapY - ray.posY + (1 - ray.stepy) / 2) / ray.rayDirY;
		ft_draw_vertical_line(ray.x, &ray, map);
		ray.x++;
	}
	mlx_put_image_to_window(map->vars.mlx, map->vars.win, map->img.img, 0, 0);
	return (1);
}

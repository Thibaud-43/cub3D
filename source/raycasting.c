/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:02:15 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/29 12:29:22 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_project_ray(t_map *map)
{
	while (map->ray.hit == 0)
	{
		if (map->ray.sidedistx < map->ray.sidedisty)
		{
			map->ray.sidedistx += map->ray.deltadistx;
			map->ray.mapx += map->ray.stepx;
			map->ray.side = 0;
		}
		else
		{
			map->ray.sidedisty += map->ray.deltadisty;
			map->ray.mapy += map->ray.stepy;
			map->ray.side = 1;
		}
		if (map->matrice[map->ray.mapx][map->ray.mapy] != '0'
		&& map->matrice[map->ray.mapx][map->ray.mapy] != '2')
			map->ray.hit = 1;
	}
	if (map->ray.side == 0)
		map->ray.perpwalldist = (map->ray.mapx - map->ray.posx +
		(1 - (double)map->ray.stepx) / 2) / map->ray.raydirx;
	else
		map->ray.perpwalldist = (map->ray.mapy - map->ray.posy +
		(1 - (double)map->ray.stepy) / 2) / map->ray.raydiry;
}

void		ft_init_draw(t_map *map)
{
	map->ray.lineheight = (int)(map->ray.height / map->ray.perpwalldist);
	map->ray.drawstart = -map->ray.lineheight / 2 + map->ray.height / 2;
	if (map->ray.drawstart < 0)
		map->ray.drawstart = 0;
	map->ray.drawend = map->ray.lineheight / 2 + map->ray.height / 2;
	if (map->ray.drawend >= map->ray.height || map->ray.drawend < 0)
		map->ray.drawend = map->ray.height - 1;
}

void		ft_draw_vertical_line(int x, t_ray *ray, t_map *map)
{
	int i;

	i = 0;
	if (map->ray.lineheight == -2147483648)
		return ;
	while (i < ray->drawstart)
	{
		map->img.addr[i * map->img.line_length / 4 + x] =
		create_trgb(0, map->ceiling[0], map->ceiling[1], map->ceiling[2]);
		i++;
	}
	ft_draw_texture(&i, x, map);
	while (i < ray->height)
	{
		map->img.addr[i * map->img.line_length / 4 + x] =
		create_trgb(0, map->floor[0], map->floor[1], map->floor[2]);
		i++;
	}
}

int			ft_raycasting(t_map *map)
{
	if (map->exit == 1)
		return (1);
	map->ray.x = 0;
	while (map->ray.x < map->resolution[0])
	{
		ft_init_raycasting_2(map);
		ft_init_raycasting_3(map);
		ft_init_deltadist(map);
		ft_init_dist(map);
		ft_project_ray(map);
		ft_init_draw(map);
		ft_draw_vertical_line(map->ray.x, &map->ray, map);
		map->spr.zbuffer[map->ray.x] = map->ray.perpwalldist;
		map->ray.x++;
	}
	ft_sprites(map);
	if (map->save == 1)
		save_bmp(map);
	else
	{
		mlx_put_image_to_window(map->vars.mlx,
		map->vars.win, map->img.img, 0, 0);
		ft_analyse_key(map);
	}
	return (1);
}

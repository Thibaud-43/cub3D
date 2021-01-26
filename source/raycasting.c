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

void		ft_project_ray(t_map *map)
{
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
		if (map->matrice[map->ray.mapX][map->ray.mapY] != '0' &&  map->matrice[map->ray.mapX][map->ray.mapY] != '2')
			map->ray.hit = 1;
	}
	if (map->ray.side == 0)
		map->ray.perpwalldist = (map->ray.mapX - map->ray.posX +
		(1 - map->ray.stepx) / 2) / map->ray.rayDirX;
	else
		map->ray.perpwalldist = (map->ray.mapY - map->ray.posY +
		(1 - map->ray.stepy) / 2) / map->ray.rayDirY;
}

void		ft_init_draw(t_map *map)
{
	map->ray.lineheight = (int)(map->ray.height / map->ray.perpwalldist);
	map->ray.drawstart = -map->ray.lineheight / 2 + map->ray.height / 2;
	if (map->ray.drawstart < 0)
		map->ray.drawstart = 0;
	map->ray.drawend = map->ray.lineheight / 2 + map->ray.height / 2;
	if (map->ray.drawend >= map->ray.height | map->ray.drawend == 0)
		map->ray.drawend = map->ray.height - 1;
}

int		ft_init_texture(t_map *map)
{
	if (map->ray.side == 0 && map->ray.rayDirX < 0)
		return 0;
	else if (map->ray.side == 0 && map->ray.rayDirX >= 0)
		return 1;
	else if (map->ray.side == 1 && map->ray.rayDirY < 0)
		return 2;
	else
		return 3;
}

void		ft_draw_texture(int *i, int x, t_map *map)
{
	int dir;

	dir = ft_init_texture(map);
	if (map->ray.side == 0)
		map->texture[dir].wallX = map->ray.posY + map->ray.perpwalldist * map->ray.rayDirY;
	else
		map->texture[dir].wallX = map->ray.posX + map->ray.perpwalldist * map->ray.rayDirX;
	map->texture[dir].wallX -= floor((map->texture[dir].wallX)); 
	map->texture[dir].step = 1.0 * map->texture[dir].height / map->ray.lineheight;
	map->texture[dir].texX = (int)(map->texture[dir].wallX * ((double)(map->texture[dir].width)));
	if (map->ray.side == 0 && map->ray.rayDirX > 0)
		map->texture[dir].texX = map->texture[dir].width - map->texture[dir].texX - 1;
	if (map->ray.side == 1 && map->ray.rayDirY < 0)
		map->texture[dir].texX = map->texture[dir].width - map->texture[dir].texX - 1;
	map->texture[dir].texPos = (map->ray.drawstart - map->resolution[1] / 2 + map->ray.lineheight / 2) * map->texture[dir].step;
	while (*i < map->ray.drawend)
	{
		map->texture[dir].texY = (int)map->texture[dir].texPos & (map->texture[dir].height - 1);
		map->texture[dir].texPos += map->texture[dir].step;
		if(*i < map->resolution[1] && x < map->resolution[0])
			map->img.addr[*i * map->img.line_length / 4 + x] = map->texture[dir].addr[map->texture[dir].texY * map->texture[dir].img->line_length / 4 +  map->texture[dir].texX];
		(*i)++;
	}
}

void		ft_draw_vertical_line(int x, t_ray *ray, t_map *map)
{
	int i;

	i = 0;
	ft_init_texture(map);
	if (map->ray.lineheight == -2147483648)
		return ;
	while (i < ray->drawstart)
	{
		map->img.addr[i * map->img.line_length / 4 + x] = 0x000000;
		i++;
	}
	ft_draw_texture(&i, x, map);
	while (i < ray->height)
	{
		map->img.addr[i * map->img.line_length / 4 + x] = 0x03FCCA;
		i++;
	}
}

void		ft_analyse_key(t_map *map)
{
	if (map->keys.forward == 1)
		ft_go_forward(map);
	if (map->keys.back == 1)
		ft_go_down(map);
	if (map->keys.camleft == 1)
		ft_rotate_left(map);
	if (map->keys.camright == 1)
		ft_rotate_right(map);
	if (map->keys.left == 1)
		ft_go_left(map);
	if (map->keys.right == 1)
		ft_go_right(map);
}

int			ft_raycasting(t_map *map)
{
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
	mlx_put_image_to_window(map->vars.mlx, map->vars.win, map->img.img, 0, 0);
	ft_analyse_key(map);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:47:07 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/29 16:24:12 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_go_forward(t_map *map)
{
	if (map->matrice[(int)(map->ray.posx + map->ray.dirx
	* map->movespeed)][(int)map->ray.posy] == '0')
		map->ray.posx += map->ray.dirx * map->movespeed;
	if (map->matrice[(int)map->ray.posx][(int)(map->ray.posy
	+ map->ray.diry * map->movespeed)] == '0')
		map->ray.posy += map->ray.diry * map->movespeed;
}

void	ft_go_down(t_map *map)
{
	if (map->matrice[(int)(map->ray.posx - map->ray.dirx
	* map->movespeed)][(int)map->ray.posy] == '0')
		map->ray.posx -= map->ray.dirx * map->movespeed;
	if (map->matrice[(int)map->ray.posx][(int)(map->ray.posy
	- map->ray.diry * map->movespeed)] == '0')
		map->ray.posy -= map->ray.diry * map->movespeed;
}

void	ft_go_left(t_map *map)
{
	if (map->matrice[(int)(map->ray.posx - map->ray.planex
	* map->movespeed)][(int)map->ray.posy] == '0')
		map->ray.posx -= map->ray.planex * map->movespeed;
	if (map->matrice[(int)map->ray.posx][(int)(map->ray.posy
	- map->ray.planey * map->movespeed)] == '0')
		map->ray.posy -= map->ray.planey * map->movespeed;
}

void	ft_go_right(t_map *map)
{
	if (map->matrice[(int)(map->ray.posx + map->ray.planex
	* map->movespeed)][(int)map->ray.posy] == '0')
		map->ray.posx += map->ray.planex * map->movespeed;
	if (map->matrice[(int)map->ray.posx][(int)(map->ray.posy
	+ map->ray.planey * map->movespeed)] == '0')
		map->ray.posy += map->ray.planey * map->movespeed;
}

void	ft_rotate_right(t_map *map)
{
	double	oldirx;
	double	oldplanex;

	oldirx = map->ray.dirx;
	oldplanex = map->ray.planex;
	map->ray.dirx = map->ray.dirx * cos(-map->rotspeed)
	- map->ray.diry * sin(-map->rotspeed);
	map->ray.diry = oldirx * sin(-map->rotspeed)
	+ map->ray.diry * cos(-map->rotspeed);
	map->ray.planex = map->ray.planex * cos(-map->rotspeed)
	- map->ray.planey * sin(-map->rotspeed);
	map->ray.planey = oldplanex * sin(-map->rotspeed)
	+ map->ray.planey * cos(-map->rotspeed);
}

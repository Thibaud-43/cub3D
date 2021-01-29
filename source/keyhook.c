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

#include "cub3D.h"

void	ft_go_forward(t_map *map)
{
	if (map->matrice[(int)(map->ray.posX + map->ray.dirX
	* map->moveSpeed)][(int)map->ray.posY] == '0')
		map->ray.posX += map->ray.dirX * map->moveSpeed;
	if (map->matrice[(int)map->ray.posX][(int)(map->ray.posY
	+ map->ray.dirY * map->moveSpeed)] == '0')
		map->ray.posY += map->ray.dirY * map->moveSpeed;
}

void	ft_go_down(t_map *map)
{
	if (map->matrice[(int)(map->ray.posX - map->ray.dirX
	* map->moveSpeed)][(int)map->ray.posY] == '0')
		map->ray.posX -= map->ray.dirX * map->moveSpeed;
	if (map->matrice[(int)map->ray.posX][(int)(map->ray.posY
	- map->ray.dirY * map->moveSpeed)] == '0')
		map->ray.posY -= map->ray.dirY * map->moveSpeed;
}

void	ft_go_left(t_map *map)
{
	if (map->matrice[(int)(map->ray.posX - map->ray.planeX
	* map->moveSpeed)][(int)map->ray.posY] == '0')
		map->ray.posX -= map->ray.planeX * map->moveSpeed;
	if (map->matrice[(int)map->ray.posX][(int)(map->ray.posY
	- map->ray.planeY * map->moveSpeed)] == '0')
		map->ray.posY -= map->ray.planeY * map->moveSpeed;
}

void	ft_go_right(t_map *map)
{
	if (map->matrice[(int)(map->ray.posX + map->ray.planeX
	* map->moveSpeed)][(int)map->ray.posY] == '0')
		map->ray.posX += map->ray.planeX * map->moveSpeed;
	if (map->matrice[(int)map->ray.posX][(int)(map->ray.posY
	+ map->ray.planeY * map->moveSpeed)] == '0')
		map->ray.posY += map->ray.planeY * map->moveSpeed;
}

void	ft_rotate_right(t_map *map)
{
	double	oldirx;
	double	oldplanex;

	oldirx = map->ray.dirX;
	oldplanex = map->ray.planeX;
	map->ray.dirX = map->ray.dirX * cos(-map->rotSpeed)
	- map->ray.dirY * sin(-map->rotSpeed);
	map->ray.dirY = oldirx * sin(-map->rotSpeed)
	+ map->ray.dirY * cos(-map->rotSpeed);
	map->ray.planeX = map->ray.planeX * cos(-map->rotSpeed)
	- map->ray.planeY * sin(-map->rotSpeed);
	map->ray.planeY = oldplanex * sin(-map->rotSpeed)
	+ map->ray.planeY * cos(-map->rotSpeed);
}

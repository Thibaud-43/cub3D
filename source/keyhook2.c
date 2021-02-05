/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:47:07 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/29 16:19:28 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rotate_left(t_map *map)
{
	double	oldirx;
	double	oldplanex;

	oldirx = map->ray.dirx;
	oldplanex = map->ray.planex;
	map->ray.dirx = map->ray.dirx * cos(map->rotspeed)
	- map->ray.diry * sin(map->rotspeed);
	map->ray.diry = oldirx * sin(map->rotspeed)
	+ map->ray.diry * cos(map->rotspeed);
	map->ray.planex = map->ray.planex * cos(map->rotspeed)
	- map->ray.planey * sin(map->rotspeed);
	map->ray.planey = oldplanex * sin(map->rotspeed)
	+ map->ray.planey * cos(map->rotspeed);
}

int		hook(int keycode, t_map *map)
{
	if (keycode == EXIT)
	{
		write(1, "Exiting ...", 12);
		ft_free_map(map);
		ft_print_matrice(map);
		map->exit = 1;
		exit(1);
	}
	if (keycode == FORWARD)
		map->keys.forward = 1;
	if (keycode == BACK)
		map->keys.back = 1;
	if (keycode == CAM_LEFT)
		map->keys.camleft = 1;
	if (keycode == CAM_RIGHT)
		map->keys.camright = 1;
	if (keycode == LEFT)
		map->keys.left = 1;
	if (keycode == RIGHT)
		map->keys.right = 1;
	return (1);
}

int		ft_release(int keycode, t_map *map)
{
	if (keycode == FORWARD)
		map->keys.forward = 0;
	if (keycode == BACK)
		map->keys.back = 0;
	if (keycode == CAM_LEFT)
		map->keys.camleft = 0;
	if (keycode == CAM_RIGHT)
		map->keys.camright = 0;
	if (keycode == LEFT)
		map->keys.left = 0;
	if (keycode == RIGHT)
		map->keys.right = 0;
	return (1);
}

int		ft_exit(t_map *map)
{
	ft_free_map(map);
	ft_print_matrice(map);
	map->exit = 1;
	exit(0);
}

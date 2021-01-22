/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:47:07 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/12 11:58:46 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_rotate_left(t_map *map)
{
	double	olDirX;
	double oldPlaneX;

	olDirX = map->ray.dirX;
	oldPlaneX = map->ray.planeX;
	map->ray.dirX = map->ray.dirX * cos(map->rotSpeed) - map->ray.dirY * sin(map->rotSpeed);
	map->ray.dirY = olDirX * sin(map->rotSpeed) + map->ray.dirY * cos(map->rotSpeed);
	map->ray.planeX = map->ray.planeX * cos(map->rotSpeed) - map->ray.planeY * sin(map->rotSpeed);
	map->ray.planeY = oldPlaneX * sin(map->rotSpeed) + map->ray.planeY * cos(map->rotSpeed);
	

}

int	hook(int keycode, t_map *map)
{
	if (keycode == EXIT)
	{
		write(1, "Exiting ...", 12);
 	 	exit(0);
	}
	printf("keycode : %d \n", keycode);
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

int	ft_release(int keycode, t_map *map)
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

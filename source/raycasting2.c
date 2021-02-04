/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:02:15 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/27 13:11:53 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_player_south(t_map *map)
{
	if (map->direction == 'S')
	{
		map->ray.diry = 0;
		map->ray.dirx = 1;
		map->ray.planex = 0;
		map->ray.planey = -0.66;
	}
}

void		ft_player_east(t_map *map)
{
	if (map->direction == 'E')
	{
		map->ray.diry = 1;
		map->ray.dirx = 0;
		map->ray.planex = 0.66;
		map->ray.planey = 0;
	}
}

void		ft_player_west(t_map *map)
{
	if (map->direction == 'W')
	{
		map->ray.diry = -1;
		map->ray.dirx = 0;
		map->ray.planex = -0.66;
		map->ray.planey = 0;
	}
}

void		ft_player_north(t_map *map)
{
	if (map->direction == 'N')
	{
		map->ray.diry = 0;
		map->ray.dirx = -1;
		map->ray.planex = 0;
		map->ray.planey = 0.66;
	}
}

void		ft_init_raycasting_1(t_map *map)
{
	map->ray.posy = map->player_x;
	map->ray.posx = map->player_y;
	ft_player_south(map);
	ft_player_west(map);
	ft_player_north(map);
	ft_player_east(map);
	map->ray.width = map->resolution[0];
	map->ray.height = map->resolution[1];
}

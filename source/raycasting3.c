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

int			ft_init_texture(t_map *map)
{
	if (map->ray.side == 0 && map->ray.raydirx < 0)
		return (0);
	else if (map->ray.side == 0 && map->ray.raydirx >= 0)
		return (1);
	else if (map->ray.side == 1 && map->ray.raydiry < 0)
		return (2);
	else
		return (3);
}

int			create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

void		ft_draw_texture2(int *i, int x, t_map *map, int dir)
{
	while (*i < map->ray.drawend)
	{
		map->texture[dir].texy = (int)map->texture[dir].texpos &
		(map->texture[dir].height - 1);
		map->texture[dir].texpos += map->texture[dir].step;
		if (*i < map->resolution[1] && x < map->resolution[0])
			map->img.addr[*i * map->img.line_length / 4 + x] =
			map->texture[dir].addr[map->texture[dir].texy *
			map->texture[dir].img->line_length / 4 + map->texture[dir].texx];
		(*i)++;
	}
}

void		ft_draw_texture(int *i, int x, t_map *map)
{
	int dir;

	dir = ft_init_texture(map);
	if (map->ray.side == 0)
		map->texture[dir].wallx = map->ray.posy +
		map->ray.perpwalldist * map->ray.raydiry;
	else
		map->texture[dir].wallx = map->ray.posx +
		map->ray.perpwalldist * map->ray.raydirx;
	map->texture[dir].wallx -= floor((map->texture[dir].wallx));
	map->texture[dir].step = 1.0 * map->texture[dir].height /
	map->ray.lineheight;
	map->texture[dir].texx = (int)(map->texture[dir].wallx *
	((double)(map->texture[dir].width)));
	if (map->ray.side == 0 && map->ray.raydirx > 0)
		map->texture[dir].texx = map->texture[dir].width
		- map->texture[dir].texx - 1;
	if (map->ray.side == 1 && map->ray.raydiry < 0)
		map->texture[dir].texx = map->texture[dir].width -
		map->texture[dir].texx - 1;
	map->texture[dir].texpos = (map->ray.drawstart - map->resolution[1] /
	2 + map->ray.lineheight / 2) * map->texture[dir].step;
	ft_draw_texture2(i, x, map, dir);
}

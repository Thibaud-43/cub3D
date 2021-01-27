/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:47:07 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/27 13:51:21 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		ft_initialize_map(t_map *map)
{
	map->matrice = NULL;
	map->direction = 0;
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->sprite = NULL;
	map->ceiling[0] = 0;
	map->ceiling[1] = 0;
	map->ceiling[2] = 0;
	map->floor[0] = 0;
	map->floor[1] = 0;
	map->floor[2] = 0;
	map->resolution[0] = 0;
	map->resolution[1] = 0;
	map->keys.forward = 0;
	map->keys.back = 0;
	map->keys.camright = 0;
	map->keys.camleft = 0;
	map->keys.left = 0;
	map->keys.right = 0;
}

void		ft_free_map(t_map *map)
{
	free(map->no);
	free(map->so);
	free(map->ea);
	free(map->we);
	free(map->sprite);
	free(map->spr.pos);
	free(map->spr.dist);
}

void		resolution_ms_rs(t_map *map)
{
	int		tmpW;
	int		tmpH;

	tmpW = 0;
	tmpH = 0;
	/*mlx_get_screen_size(map->vars.mlx, &tmpW, &tmpH);
	if (tmpW < map->resolution[0])
		map->resolution[0] = tmpW;
	if (tmpH < map->resolution[1])
		map->resolution[1] = tmpH;*/
	map->moveSpeed = MOVESPEED;
	map->rotSpeed = ROTSPEED;
}

void		window(t_map *map)
{
	map->matrice[(int)map->player_y][(int)map->player_x] = '0';
	map->vars.mlx = mlx_init();
	resolution_ms_rs(map);
	map->vars.win = mlx_new_window(map->vars.mlx,
	map->resolution[0], map->resolution[1], "Cub3D");
	map->img.img = mlx_new_image(map->vars.mlx,
	map->resolution[0], map->resolution[1]);
	map->img.addr = (int *)mlx_get_data_addr(map->img.img,
	&map->img.bits_per_pixel, &map->img.line_length, &map->img.endian);
	ft_init_raycasting_1(map);
	ft_texture(map);
	ft_raycasting(map);
	mlx_hook(map->vars.win, 2, 1L << 0, hook, map);
	mlx_loop_hook(map->vars.mlx, ft_raycasting, map);
	mlx_hook(map->vars.win, 3, 1L << 1, ft_release, map);
	mlx_loop(map->vars.mlx);
}

int			main(int argc, char **argv)
{
	t_map	map;

	ft_initialize_map(&map);
	if ((ft_parser(argc, argv, &map)))
	{
		window(&map);
		ft_print_matrice(&map);
	}
	ft_free_map(&map);
	return (1);
}

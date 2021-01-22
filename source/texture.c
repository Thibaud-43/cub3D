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

void		ft_set_texture(t_map *map)
{
	map->texture[0].img = mlx_xpm_file_to_image(map->vars.mlx, map->no, &map->texture[0].width, &map->texture[0].height);
	map->texture[0].addr = (int *)mlx_get_data_addr(map->texture[0].img, &map->texture[0].img.bits_per_pixel, &map->texture[0].img.line_length, &map->texture[0].img.endian);
	map->texture[1].img = mlx_xpm_file_to_image(map->vars.mlx, map->so, &map->texture[1].width, &map->texture[1].height);
	map->texture[2].img = mlx_xpm_file_to_image(map->vars.mlx, map->ea, &map->texture[2].width, &map->texture[2].height);
	map->texture[3].img = mlx_xpm_file_to_image(map->vars.mlx, map->we, &map->texture[3].width, &map->texture[3].height);
}

void		ft_texture(t_map *map)
{
	ft_set_texture(map);
	mlx_put_image_to_window(map->vars.mlx, map->vars.win, map->texture[2].img, 50, 50);
}
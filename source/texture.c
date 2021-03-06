/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:47:07 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/29 08:32:54 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_set_texture_img(t_map *map)
{
	map->texture[0].image.img = (void *)mlx_xpm_file_to_image(map->vars.mlx,
	map->so, &map->texture[0].width, &map->texture[0].height);
	map->texture[1].image.img = mlx_xpm_file_to_image(map->vars.mlx,
	map->no, &map->texture[1].width, &map->texture[1].height);
	map->texture[2].image.img = mlx_xpm_file_to_image(map->vars.mlx,
	map->ea, &map->texture[2].width, &map->texture[2].height);
	map->texture[3].image.img = mlx_xpm_file_to_image(map->vars.mlx,
	map->we, &map->texture[3].width, &map->texture[3].height);
	map->texture[4].image.img = mlx_xpm_file_to_image(map->vars.mlx,
	map->sprite, &map->texture[4].width, &map->texture[4].height);
}

void		ft_set_texture_addr(t_map *map)
{
	map->texture[0].addr = (int *)mlx_get_data_addr(map->texture[0].image.img,
	&map->texture[0].image.bits_per_pixel, &map->texture[0].image.line_length,
	&map->texture[0].image.endian);
	map->texture[1].addr = (int *)mlx_get_data_addr(map->texture[1].image.img,
	&map->texture[1].image.bits_per_pixel, &map->texture[1].image.line_length,
	&map->texture[1].image.endian);
	map->texture[2].addr = (int *)mlx_get_data_addr(map->texture[2].image.img,
	&map->texture[2].image.bits_per_pixel, &map->texture[2].image.line_length,
	&map->texture[2].image.endian);
	map->texture[3].addr = (int *)mlx_get_data_addr(map->texture[3].image.img,
	&map->texture[3].image.bits_per_pixel, &map->texture[3].image.line_length,
	&map->texture[3].image.endian);
	map->texture[4].addr = (int *)mlx_get_data_addr(map->texture[4].image.img,
	&map->texture[4].image.bits_per_pixel, &map->texture[4].image.line_length,
	&map->texture[4].image.endian);
}

void		ft_texture(t_map *map)
{
	ft_set_texture_img(map);
	if (map->texture[0].image.img == 0 | map->texture[1].image.img == 0 |
	map->texture[2].image.img == 0 | map->texture[3].image.img == 0 |
	map->texture[4].image.img == 0)
	{
		write(1, "Error\n une texture n'est pas au bon format", 42);
		ft_free_map(map);
		ft_print_matrice(map);
		exit(0);
	}
	ft_set_texture_addr(map);
}

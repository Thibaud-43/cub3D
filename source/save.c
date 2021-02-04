/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:35:19 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/28 17:10:42 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	insert_header(int fd, t_map *map)
{
	int		insert;
	int		i;

	write(fd, "BM", 2);
	insert = 54 + map->resolution[0] * map->resolution[1] * 4;
	write(fd, &insert, 4);
	insert = 0;
	write(fd, &insert, 2);
	write(fd, &insert, 2);
	insert = 54;
	write(fd, &insert, 4);
	insert = 40;
	write(fd, &insert, 4);
	insert = map->resolution[0];
	write(fd, &insert, 4);
	insert = map->resolution[1];
	write(fd, &insert, 4);
	insert = 1;
	write(fd, &insert, 2);
	insert = map->img.bits_per_pixel;
	write(fd, &insert, 2);
	insert = 0;
	i = 0;
	while (i++ < 7)
		write(fd, &insert, 4);
}

void	save_bmp(t_map *map)
{
	int fd;
	int i;
	int k;

	i = map->resolution[1] - 1;
	if ((fd = open("image.bmp", O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU)) == -1)
	{
		write(1, "Error \n image.bmp n'a pas ete cree", 35);
		ft_free_map(map);
		exit(1);
	}
	insert_header(fd, map);
	while (i >= 0)
	{
		k = 0;
		while (k < map->resolution[0])
		{
			write(fd, &map->img.addr[i * map->img.line_length / 4 + k], 4);
			k++;
		}
		i--;
	}
	close(fd);
}

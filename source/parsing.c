/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:26:50 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/29 11:42:24 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_parser_4(t_parsing *parsing, int *i, int *k, t_map *map)
{
	if (parsing->lign[*i] == 'F' && parsing->map_encountered == 0)
	{
		if (!(ft_parse_floor(parsing, map)))
			return (0);
	}
	if (parsing->lign[*i] == 0 && parsing->map_encountered == 0)
	{
		parsing->param_line_valid = 1;
	}
	if (parsing->lign[*i] == '0' | parsing->lign[*i] == '1')
	{
		if (!(ft_parse_map(map, parsing, *k)))
			return (0);
	}
	if (parsing->param_line_valid == 0)
	{
		message_map_invalid(parsing,
		"Error\n Une ligne n'est pas correcte\n");
	}
	free(parsing->lign);
	return (1);
}

static int		ft_parser_3(t_parsing *parsing, int *i, t_map *map)
{
	if (parsing->lign[*i] == 'N' && parsing->lign[*i + 1] == 'O'
		&& parsing->map_encountered == 0)
	{
		if (!(ft_parse_direction_no(parsing, map)))
			return (0);
	}
	if (parsing->lign[*i] == 'S' && parsing->lign[*i + 1] == ' '
		&& parsing->map_encountered == 0)
	{
		if (!(ft_parse_sprite(parsing, map)))
			return (0);
	}
	if (parsing->lign[*i] == 'C' && parsing->map_encountered == 0)
	{
		if (!(ft_parse_ceiling(parsing, map)))
			return (0);
	}
	if (parsing->lign[*i] == 0 && parsing->map_encountered == 1)
	{
		message_map_invalid(parsing,
		"Error\n Présence d'uneligne vide au niveau de la map\n");
		parsing->param_line_valid = 1;
	}
	return (1);
}

static int		ft_parser_2(t_parsing *parsing, int *i, int *k, t_map *map)
{
	*i = 0;
	(*k)++;
	parsing->param_line_valid = 0;
	while (parsing->lign[*i] == ' ')
		(*i)++;
	if (parsing->lign[*i] == 'R' && parsing->map_encountered == 0)
		if (!(ft_parse_resolution(parsing, map)))
			return (0);
	if (parsing->lign[*i] == 'E' && parsing->lign[*i + 1] == 'A'
		&& parsing->map_encountered == 0)
		if (!(ft_parse_direction_ea(parsing, map)))
			return (0);
	if (parsing->lign[*i] == 'W' && parsing->lign[*i + 1] == 'E'
		&& parsing->map_encountered == 0)
	{
		if (!(ft_parse_direction_we(parsing, map)))
			return (0);
	}
	if (parsing->lign[*i] == 'S' && parsing->lign[*i + 1] == 'O'
		&& parsing->map_encountered == 0)
	{
		if (!(ft_parse_direction_so(parsing, map)))
			return (0);
	}
	return (1);
}

int				ft_parser_5(t_parsing *parsing, int fd, int i, int k)
{
	free(parsing->lign);
	ft_all_params(parsing);
	if (parsing->is_valid == 1)
	{
		ft_parse_map_advanced(parsing, argv, map);
		if (ft_init_sprites(map) == 0)
			return (0);
	}
	close(fd);
}

int				ft_parser(int argc, char **argv, t_map *map)
{
	t_parsing	parsing;
	int			fd;
	int			ret;
	int			i;
	int			k;

	ret = 1;
	k = 0;
	ft_init_parsing(&parsing);
	ft_check_args(map, &parsing, argc, argv);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	while ((ret = get_next_line(fd, &parsing.lign)))
	{
		if (ft_parser_2(&parsing, &i, &k, map) == 0
			| ft_parser_3(&parsing, &i, map) == 0
			| ft_parser_4(&parsing, &i, &k, map) == 0)
			return (0);
	}
	if (!(ft_parser_5(&parsing, fd, i, k)))
		return (0);
	return (parsing.is_valid);
}

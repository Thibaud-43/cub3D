/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:15:51 by trouchon          #+#    #+#             */
/*   Updated: 2021/02/08 11:20:27 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_check_args(t_map *map, t_parsing *parsing, int argc, char **argv)
{
	if (argc < 2)
		message_map_invalid(parsing,
		"Error \n Le nombre d'argument est trop petit.\n");
	else if (argc > 3)
		message_map_invalid(parsing,
		"Error \n Le nombre d'argument est trop grand.\n");
	else if (argc == 3 && ft_check_save_flag(map, argv[2]) == 0)
		message_map_invalid(parsing,
		"Error \n Le troisième argument n'est pas reconnu.\n");
	else if (ft_checks_cub_format(argv[1]) == 0)
	{
		message_map_invalid(parsing,
		"Error \n Le format du '.cub' n'est pas correcte.\n");
		exit(0);
	}
}

int			ft_checks_cub_format(char *str)
{
	int		i;
	int		count_dot;
	int		fd;
	char	buff[2];

	count_dot = 0;
	i = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0 | read(fd, buff, 1) < 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '.')
			count_dot++;
		if (str[i] == '.' && str[i + 1] == 'c'
				&& str[i + 2] == 'u' && str[i + 3] == 'b'
				&& str[i + 4] == 0 && count_dot == 1)
			return (1);
		i++;
	}
	close(fd);
	return (0);
}

void		ft_all_params(t_parsing *parsing)
{
	if (parsing->no_encountered == 0 |
		parsing->so_encountered == 0 |
		parsing->we_encountered == 0 |
		parsing->ea_encountered == 0 |
		parsing->s_encountered == 0 |
		parsing->c_encountered == 0 |
		parsing->map_encountered == 0 |
		parsing->resolution_encountered == 0 |
		parsing->player_found == 0)
	{
		message_map_invalid(parsing,
		"Error\n Il manque des paramètres\n");
	}
}

int			ft_check_save_flag(t_map *map, char *str)
{
	if (str[0] == '-' && str[1] == '-' && str[2] == 's' &&
			str[3] == 'a' && str[4] == 'v' && str[5] == 'e' && str[6] == 0)
	{
		map->save = 1;
		return (1);
	}
	return (0);
}

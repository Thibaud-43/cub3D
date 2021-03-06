/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:25:39 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/29 16:24:02 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	message_map_invalid(t_parsing *parsing, char *str)
{
	write(1, str, ft_strlen(str));
	parsing->is_valid = 0;
}

void	ft_init_parsing(t_parsing *parsing)
{
	parsing->lign = NULL;
	parsing->is_valid = 1;
	parsing->resolution_encountered = 0;
	parsing->no_encountered = 0;
	parsing->so_encountered = 0;
	parsing->we_encountered = 0;
	parsing->ea_encountered = 0;
	parsing->s_encountered = 0;
	parsing->c_encountered = 0;
	parsing->f_encountered = 0;
	parsing->map_encountered = 0;
	parsing->line_num_begin_map = 0;
	parsing->line_map_len_max = 0;
	parsing->nb_lines_map = 0;
	parsing->player_found = 0;
	parsing->param_line_valid = 0;
}

void	free_split(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}

int		ft_check_ch(char *str, char *charset)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(charset, str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_matrice(t_map *map)
{
	int	k;

	k = 0;
	while (map->matrice[k])
		free(map->matrice[k++]);
	free(map->matrice);
	free(map->spr.zbuffer);
	if (map->img.img)
		mlx_destroy_image(map->vars.mlx, map->img.img);
	if (map->texture[0].image.img)
		mlx_destroy_image(map->vars.mlx, map->texture[0].image.img);
	if (map->texture[1].image.img)
		mlx_destroy_image(map->vars.mlx, map->texture[1].image.img);
	if (map->texture[2].image.img)
		mlx_destroy_image(map->vars.mlx, map->texture[2].image.img);
	if (map->texture[3].image.img)
		mlx_destroy_image(map->vars.mlx, map->texture[3].image.img);
	if (map->texture[4].image.img)
		mlx_destroy_image(map->vars.mlx, map->texture[4].image.img);
	if (map->save == 0)
		mlx_destroy_window(map->vars.mlx, map->vars.win);
	mlx_destroy_display(map->vars.mlx);
	free(map->vars.mlx);
}

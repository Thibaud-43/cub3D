/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:47:07 by trouchon          #+#    #+#             */
/*   Updated: 2021/01/09 13:25:13 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_initialize_map(t_map *map)
{
	map->matrice = NULL;
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
}

void	ft_free_map(t_map *map)
{
	free(map->no);
	free(map->so);
	free(map->ea);
	free(map->we);
	free(map->sprite);
	ft_print_matrice(map);
}

void		draw(t_data *img, int x, int y, int color)
{ 
	int tmp_x;
	int tmp_y;

	tmp_x = x * 30;
	while((tmp_x) < ((x + 1) * 30))
	{
		tmp_y = y * 30;
		while((tmp_y) < ((y + 1) * 30))
		{
			img->addr[tmp_x * img->line_length / 4 + tmp_y] = color;
			tmp_y++;
		}
		tmp_x++;
	}
}

void	print_window_matrice(t_map *map)
{
	int x;
	int y;

	x = 0;
       	while(map->matrice[x])
    	{
	    y = 0;
	    while(map->matrice[x][y])
	    {
		    if(map->matrice[x][y] == '1')
		    {
			draw(&map->img, x, y, 0xFCBA03);
		    }
		    else if(map->matrice[x][y] == '0')
		    {
			draw(&map->img, x, y, 0x03FCCA);
		    }
		    else
			    draw(&map->img, x, y, 0x000000);
		    y++;
	    }
	    x++;
    	}
	mlx_put_image_to_window(map->vars.mlx, map->vars.win, map->img.img, 0, 0);
}


void	ft_go_up(t_map *map)
{
	printf("Matrice : %c \n",map->matrice[6][15]);
	if (map->matrice[map->player_y - 1][map->player_x] == '0')
	{
		map->matrice[map->player_y - 1][map->player_x] = 'S';
		map->matrice[map->player_y][map->player_x] = '0';
		map->player_y--;
		print_window_matrice(map);
	}
}

void	ft_go_down(t_map *map)
{
	printf("Matrice : %c \n",map->matrice[6][15]);
	if (map->matrice[map->player_y + 1][map->player_x] == '0')
	{
		map->matrice[map->player_y + 1][map->player_x] = 'S';
		map->matrice[map->player_y][map->player_x] = '0';
		map->player_y++;
		print_window_matrice(map);
	}
}

void	ft_go_right(t_map *map)
{
	printf("Matrice : %c \n",map->matrice[6][15]);
	if (map->matrice[map->player_y][map->player_x + 1] == '0')
	{
		map->matrice[map->player_y][map->player_x + 1] = 'S';
		map->matrice[map->player_y][map->player_x] = '0';
		map->player_x++;
		print_window_matrice(map);
	}
}

void	ft_go_left(t_map *map)
{
	printf("Matrice : %c \n",map->matrice[6][15]);
	if (map->matrice[map->player_y][map->player_x - 1] == '0')
	{
		map->matrice[map->player_y][map->player_x - 1] = 'S';
		map->matrice[map->player_y][map->player_x] = '0';
		map->player_x--;
		print_window_matrice(map);
	}
}

int	hook(int keycode, t_map *map)
{
	(void)map;
	printf("keycode : %d \n", keycode);
	if (keycode == 32)
	{
		write(1, "Exiting ...", 12);
 	 	exit(0);
	}

	if (keycode == 65362)
	{
		ft_go_up(map);		
	}
	if (keycode == 65364)
	{
		ft_go_down(map);	
	}
	if (keycode == 65361)
	{
		
		ft_go_left(map);	
	}
	if (keycode == 65363)
	{
		ft_go_right(map);	
	}
	return (1);
}
void             window(t_map *map)
{
	map->vars.mlx = mlx_init(); 
    map->vars.win = mlx_new_window(map->vars.mlx, 1300, 700, "Hello world!");
    map->img.img = mlx_new_image(map->vars.mlx, 1300, 700);
    map->img.addr = (int *)mlx_get_data_addr(map->img.img, &map->img.bits_per_pixel, &map->img.line_length, &map->img.endian);
	print_window_matrice(map);
    mlx_hook(map->vars.win, 2, 1L<<0, hook, map);
    mlx_loop(map->vars.mlx);
}
int		main(int argc, char **argv)
{
	t_map	map;
	ft_initialize_map(&map);
	int ret;

	ret =  ft_parser(argc, argv, &map);
	printf("Valeur de retour: %d \n",ret);
	printf("Valeur de no : %s \n", map.no);
	printf("Valeur de so : %s \n", map.so);
	printf("Valeur de ea : %s \n", map.ea);
	printf("Valeur de we : %s \n", map.we);
	printf("Valeur de SPRITE : %s \n", map.sprite);
	printf("Valeur de ceiling : %d / %d / %d \n", map.ceiling[0], map.ceiling[1], map.ceiling[2]);
	printf("Valeur de floor : %d / %d / %d \n", map.floor[0], map.floor[1], map.floor[2]);
	printf("Valeur de resolution : %d / %d \n", map.resolution[0], map.resolution[1]);
	printf("Valeur de player_x : %d player_y : %d \n", map.player_x, map.player_y);
	if (ret)
		window(&map);
	ft_free_map(&map);
	return (1);
}


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

void	ft_go_forward(t_map *map)
{
	if (map->matrice[(int)(map->ray.posX + map->ray.dirX * map->moveSpeed)][(int)map->ray.posY] == '0')
		map->ray.posX += map->ray.dirX * map->moveSpeed;
	if (map->matrice[(int)map->ray.posX][(int)(map->ray.posY + map->ray.dirY * map->moveSpeed)] == '0')
		map->ray.posY += map->ray.dirY * map->moveSpeed;
	//ft_raycasting(map);
}

void	ft_go_down(t_map *map)
{
	if (map->matrice[(int)(map->ray.posX - map->ray.dirX * map->moveSpeed)][(int)map->ray.posY] == '0')
		map->ray.posX -= map->ray.dirX * map->moveSpeed;
	if (map->matrice[(int)map->ray.posX][(int)(map->ray.posY - map->ray.dirY * map->moveSpeed)] == '0')
		map->ray.posY -= map->ray.dirY * map->moveSpeed;
	//ft_raycasting(map);
}

void	ft_rotate_right(t_map *map)
{
	double	olDirX;
	double oldPlaneX;

	olDirX = map->ray.dirX;
	oldPlaneX = map->ray.planeX;
	map->ray.dirX = map->ray.dirX * cos(-map->rotSpeed) - map->ray.dirY * sin(-map->rotSpeed);
	map->ray.dirY = olDirX * sin(-map->rotSpeed) + map->ray.dirY * cos(-map->rotSpeed);
	map->ray.planeX = map->ray.planeX * cos(-map->rotSpeed) - map->ray.planeY * sin(-map->rotSpeed);
	map->ray.planeY = oldPlaneX * sin(-map->rotSpeed) + map->ray.planeY * cos(-map->rotSpeed);
	//ft_raycasting(map);
}

void	ft_rotate_left(t_map *map)
{
	double	olDirX;
	double oldPlaneX;

	olDirX = map->ray.dirX;
	oldPlaneX = map->ray.planeX;
	map->ray.dirX = map->ray.dirX * cos(map->rotSpeed) - map->ray.dirY * sin(map->rotSpeed);
	map->ray.dirY = olDirX * sin(map->rotSpeed) + map->ray.dirY * cos(map->rotSpeed);
	map->ray.planeX = map->ray.planeX * cos(map->rotSpeed) - map->ray.planeY * sin(map->rotSpeed);
	map->ray.planeY = oldPlaneX * sin(map->rotSpeed) + map->ray.planeY * cos(map->rotSpeed);
	//ft_raycasting(map);

}

int	hook(int keycode, t_map *map)
{
	if (keycode == 32)
	{
		write(1, "Exiting ...", 12);
 	 	exit(0);
	}

	if (keycode == 65362)
		map->keys.forward = 1;
	if (keycode == 65364)
		map->keys.back = 1;
	if (keycode == 65361)
		map->keys.left = 1;
	if (keycode == 65363)
		map->keys.right = 1;
	return (1);
}

int	ft_release(int keycode, t_map *map)
{
	if (keycode == 65362)
		map->keys.forward = 0;
	if (keycode == 65364)
		map->keys.back = 0;
	if (keycode == 65361)
		map->keys.left = 0;
	if (keycode == 65363)
		map->keys.right = 0;
	return (1);
}

void             window(t_map *map)
{
	map->vars.mlx = mlx_init(); 
	map->vars.win = mlx_new_window(map->vars.mlx, map->resolution[0], map->resolution[1], "Hello world!");
	map->img.img = mlx_new_image(map->vars.mlx, map->resolution[0], map->resolution[1]);
	map->img.addr = (int *)mlx_get_data_addr(map->img.img, &map->img.bits_per_pixel, &map->img.line_length, &map->img.endian);
	ft_init_raycasting_1(map);
	ft_raycasting(map);
	mlx_hook(map->vars.win, 2, 1L<<0, hook, map);
	mlx_loop_hook(map->vars.mlx, ft_raycasting, map);
	mlx_hook(map->vars.win, 3, 1L<<1, ft_release, map);
	mlx_loop(map->vars.mlx);
}
int		main(int argc, char **argv)
{
	t_map	map;
	ft_initialize_map(&map);
	int ret;

	ret =  ft_parser(argc, argv, &map);
/*	printf("Valeur de retour: %d \n",ret);
	printf("Valeur de no : %s \n", map.no);
	printf("Valeur de so : %s \n", map.so);
	printf("Valeur de ea : %s \n", map.ea);
	printf("Valeur de we : %s \n", map.we);
	printf("Valeur de SPRITE : %s \n", map.sprite);
	printf("Valeur de ceiling : %d / %d / %d \n", map.ceiling[0], map.ceiling[1], map.ceiling[2]);
	printf("Valeur de floor : %d / %d / %d \n", map.floor[0], map.floor[1], map.floor[2]);
	printf("Valeur de resolution : %d / %d \n", map.resolution[0], map.resolution[1]);
	printf("Valeur de player_x : %d player_y : %d \n", map.player_x, map.player_y);*/
	map.matrice[(int)map.player_y][(int)map.player_x] = '0';
	map.moveSpeed = 0.02;
	map.rotSpeed = 0.01;
	if (ret)
		window(&map);
	ft_free_map(&map);
	return (1);
}


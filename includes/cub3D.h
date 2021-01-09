#ifndef CUB3D_H
# define CUB3D_H

#include "libft.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

typedef struct  s_data {
    void        *img;
    int        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct s_vars {
	void *mlx;
	void *win;
}	t_vars;

typedef struct s_map
{
	char **matrice;
	char *no;
	char *so;
	char *ea;
	char *we;
	char *sprite;
	int	ceiling[3];
	int	floor[3];
	int	resolution[2];
	int	player_x;
	int	player_y;
	t_vars	vars;
	t_data	img;
}	t_map;

typedef struct s_parsing
{
	char	*lign;
	int	is_valid;
	int	resolution_encountered;
	int	no_encountered;
	int	so_encountered;
	int	we_encountered;
	int	ea_encountered;
	int	s_encountered;
	int	f_encountered;
	int	c_encountered;
	int	map_encountered;
	int	line_num_begin_map;
	int	line_map_len_max;
	int	nb_lines_map;
	int	param_line_valid;
	int	player_found;
}		t_parsing;

typedef struct s_parse_map
{
	int fd;
	int ret;
	int k;
	int i;
	int z;
}	t_p_map;

typedef struct s_normi
{
	int i;
	int k;
}	t_normi;

int ft_parser(int argc, char **argv, t_map *map);
void	ft_check_args(t_parsing *parsing, int argc, char **argv);
int	ft_checks_cub_format(char *str);
void	ft_all_params( t_parsing *parsing);
int	ft_check_save_flag(char *str);
int	ft_parse_ceiling(t_parsing *parsing, t_map *map);
int	ft_parse_floor(t_parsing *parsing, t_map *map);
int	ft_parse_direction_ea(t_parsing *parsing, t_map *map);
int	ft_parse_direction_no(t_parsing *parsing, t_map *map);
int	ft_parse_direction_so(t_parsing *parsing, t_map *map);
int	ft_parse_direction_we(t_parsing *parsing, t_map *map);
void	ft_check_ch_map(t_parsing *parsing);
int	ft_parse_map(t_parsing *parsing, int k);
int	ft_init_matrice(t_parsing *parsing, t_map *map);
int	ft_parse_map_advanced(t_parsing *parsing, char **argv, t_map *map);
void	ft_check_comformity(int i, int k, t_map *map, int *error);
void	ft_parse_map_advanced_2(t_parsing *parsing, t_map *map);
int	ft_parse_resolution(t_parsing *parsing, t_map *map);
int	ft_parse_sprite(t_parsing *parsing, t_map *map);
void	message_map_invalid(t_parsing *parsing, char *str);
void	ft_init_parsing(t_parsing *parsing);
void	free_split(char **str);
void	ft_print_matrice(t_map *map);

#endif


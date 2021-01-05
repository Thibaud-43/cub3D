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

typedef struct s_parsing
{
	char	*lign;
	int	is_valid;
	int	resolution_encountered;
	long	resolution_width;
	long	resolution_height;
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
	char	**matrice;
}		t_parsing;

int ft_parser(int argc, char **argv);

#endif


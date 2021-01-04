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
}		t_parsing;

int ft_parser(int argc, char **argv);

#endif



#include "cub3D.h"

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
	parsing->resolution_width = 0;
	parsing->resolution_height = 0;
	parsing->no_encountered = 0;
	parsing->so_encountered = 0;
	parsing->we_encountered = 0;
	parsing->ea_encountered = 0;
	parsing->s_encountered = 0;
	parsing->c_encountered = 0;
}

int	ft_parse_ceiling(t_parsing *parsing)
{
	char	**ceiling;
	char	**rgb;
	int	rgb_tab[3];
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (parsing->c_encountered == 1)
		message_map_invalid(parsing, "Error \n La ligne de param CEILING est présente deux fois\n");
	parsing->c_encountered = 1;
	if(!(ceiling = ft_split(parsing->lign, ' ')))
		return (0);
	if (ceiling[0][1] != 0 | ceiling[2] != 0)
		message_map_invalid(parsing, "Error \n La ligne de param CEILING n'est pas correctement rédigée \n");
	if(!ceiling[0] | !ceiling[1])
		message_map_invalid(parsing, "Error \n La ligne de param CEILING n'est pas correctement rédigée \n");
	if(!(rgb = ft_split(ceiling[1], ',')))
		return (0);
	if((!rgb[2]) | (rgb[3] != 0))
		message_map_invalid(parsing, "Error \n La ligne de param CEILING n'est pas correctement rédigée \n");
	while(rgb[i])
	{
		while(rgb[i][k])
		{
			if (ft_isdigit(rgb[i][k]) == 0)
				message_map_invalid(parsing, "Error \n Le code RGB de param CEILING n'est pas correctement rédigé \n");
			k++;
		}
		i++;
	}
	rgb_tab[0] = ft_atoi(rgb[0]);
	rgb_tab[1] = ft_atoi(rgb[1]);
	rgb_tab[2] = ft_atoi(rgb[2]);
	if((rgb_tab[0] < 0 | rgb_tab[0] > 255) | (rgb_tab[1] < 0 | rgb_tab[1] > 255) | (rgb_tab[2] < 0 | rgb_tab[2] > 255))
		message_map_invalid(parsing, "Error \n Le code RGB de param CEILING n'est pas correctement rédigé \n");
	free(rgb);	
	free(ceiling);
	return(1);
}
int	ft_parse_floor(t_parsing *parsing)
{
	char	**floor;
	char	**rgb;
	int	rgb_tab[3];
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (parsing->f_encountered == 1)
		message_map_invalid(parsing, "Error \n La ligne de param FLOOR est présente deux fois\n");
	parsing->f_encountered = 1;
	if(!(floor = ft_split(parsing->lign, ' ')))
		return (0);
	if (floor[0][1] != 0 | floor[2] != 0)
		message_map_invalid(parsing, "Error \n La ligne de param FLOOR n'est pas correctement rédigée \n");
	if(!floor[0] | !floor[1])
		message_map_invalid(parsing, "Error \n La ligne de param FLOOR n'est pas correctement rédigée \n");
	if(!(rgb = ft_split(floor[1], ',')))
		return (0);
	if((!rgb[2]) | (rgb[3] != 0))
		message_map_invalid(parsing, "Error \n La ligne de param FLOOR n'est pas correctement rédigée \n");
	while(rgb[i])
	{
		while(rgb[i][k])
		{
			if (ft_isdigit(rgb[i][k]) == 0)
				message_map_invalid(parsing, "Error \n Le code RGB de param FLOOR n'est pas correctement rédigé \n");
			k++;
		}
		i++;
	}
	rgb_tab[0] = ft_atoi(rgb[0]);
	rgb_tab[1] = ft_atoi(rgb[1]);
	rgb_tab[2] = ft_atoi(rgb[2]);
	if((rgb_tab[0] < 0 | rgb_tab[0] > 255) | (rgb_tab[1] < 0 | rgb_tab[1] > 255) | (rgb_tab[2] < 0 | rgb_tab[2] > 255))
		message_map_invalid(parsing, "Error \n Le code RGB de param FLOOR n'est pas correctement rédigé \n");
	free(rgb);	
	free(floor);
	return(1);
}

int	ft_parse_sprite(t_parsing *parsing)
{
	char	**sprite;
	int	fd;

	if (parsing->s_encountered == 1)
		message_map_invalid(parsing, "Error \n La ligne de param SPRITE est présente deux fois\n");
	parsing->so_encountered = 1;
	if(!(sprite = ft_split(parsing->lign, ' ')))
		return (0);
	if (sprite[0][1] != 0 | sprite[2] != 0)
		message_map_invalid(parsing, "Error \n La ligne de param S n'est pas correctement rédigée \n");
	if(!sprite[0] | !sprite[1])
		message_map_invalid(parsing, "Error \n La ligne de param EA n'est pas correctement rédigée \n");
	fd = open(sprite[1], O_RDONLY);
	if (fd == -1)
		message_map_invalid(parsing, "Error \nLE SPRITE ne s'ouvre pas correctement\n");
	close(fd);
	free(sprite);
	return(1);
}

int	ft_parse_direction_ea(t_parsing *parsing)
{
	char	**direction;
	int	fd;

	if (parsing->ea_encountered == 1)
		message_map_invalid(parsing, "Error \n La ligne de param EA est présente deux fois\n");
	parsing->ea_encountered = 1;
	if(!(direction = ft_split(parsing->lign, ' ')))
		return (0);
	if(direction[0][2] != 0 | direction[2] != 0)
		message_map_invalid(parsing, "Error \n La ligne de param EA n'est pas correctement rédigée \n");
	if(!direction[0] | !direction[1])
		message_map_invalid(parsing, "Error \n La ligne de param EA n'est pas correctement rédigée \n");
	fd = open(direction[1], O_RDONLY);
	if (fd == -1)
		message_map_invalid(parsing, "Error \n La texture EA n'est pas correcte \n");
	close(fd);
	free(direction);
	return (1);
}

int	ft_parse_direction_no(t_parsing *parsing)
{
	char	**direction;
	int	fd;

	if (parsing->no_encountered == 1)
		message_map_invalid(parsing, "Error \n La ligne de param NO est présente deux fois\n");
	parsing->no_encountered = 1;
	if(!(direction = ft_split(parsing->lign, ' ')))
		return (0);
	if(direction[0][2] != 0 | direction[2] != 0)
		message_map_invalid(parsing, "Error \n La ligne de param NO n'est pas correctement rédigée \n");
	if(!direction[0] | !direction[1])
		message_map_invalid(parsing, "Error \n La ligne de param NO n'est pas correctement rédigée \n");
	fd = open(direction[1], O_RDONLY);
	if (fd == -1)
		message_map_invalid(parsing, "Error \n La texture NO n'est pas correcte \n");
	close(fd);
	free(direction);
	return (1);
}

int	ft_parse_direction_we(t_parsing *parsing)
{
	char	**direction;
	int	fd;

	if (parsing->we_encountered == 1)
		message_map_invalid(parsing, "Error \n La ligne de param WE est présente deux fois\n");
	parsing->we_encountered = 1;
	if(!(direction = ft_split(parsing->lign, ' ')))
		return (0);
	if(direction[0][2] != 0 | direction[2] != 0)
		message_map_invalid(parsing, "Error \n La ligne de param WE n'est pas correctement rédigée \n");
	if(!direction[0] | !direction[1])
		message_map_invalid(parsing, "Error \n La ligne de param WE n'est pas correctement rédigée \n");
	fd = open(direction[1], O_RDONLY);
	if (fd == -1)
		message_map_invalid(parsing, "Error \n La texture WE n'est pas correcte \n");
	close(fd);
	free(direction);
	return (1);
}


int	ft_parse_direction_so(t_parsing *parsing)
{
	char	**direction;
	int	fd;

	if (parsing->so_encountered == 1)
		message_map_invalid(parsing, "Error \n La ligne de param SO est présente deux fois\n");
	parsing->so_encountered = 1;
	if(!(direction = ft_split(parsing->lign, ' ')))
		return (0);
	if(direction[0][2] != 0 | direction[2] != 0)
		message_map_invalid(parsing, "Error \n La ligne de param SO n'est pas correctement rédigée \n");
	if(!direction[0] | !direction[1])
		message_map_invalid(parsing, "Error \n La ligne de param SO n'est pas correctement rédigée \n");
	fd = open(direction[1], O_RDONLY);
	if (fd == -1)
		message_map_invalid(parsing, "Error \n Le texture SO n'est pas correcte \n");
	close(fd);
	free(direction);
	return (1);
}

int	ft_parse_resolution(t_parsing *parsing)
{
	char	**resolution;
	int	i;

	if (parsing->resolution_encountered == 1)
		parsing->is_valid = 0;
	parsing->resolution_encountered = 1;
	if(!(resolution = ft_split(parsing->lign, ' ')))
		return (0);
	i = 0;
	if (!resolution[2] | !resolution[1] | !resolution[0])
		parsing->is_valid = 0;
	if (resolution[3] != 0)
		parsing->is_valid = 0;
	if ((resolution[0][0] != 'R') | resolution [0][1])
		parsing->is_valid = 0;
	if (parsing->is_valid)
	{
		while (resolution [1][i])
		{
			if (ft_isdigit(resolution[1][i]) == 0)
				parsing->is_valid = 0;
			i++;
		}
		i = 0;
		while (resolution [2][i])
		{
			if (ft_isdigit(resolution[2][i]) == 0)
				parsing->is_valid = 0;
			i++;
		}
		parsing->resolution_width = ft_atoi(resolution[1]);
		parsing->resolution_height = ft_atoi(resolution[2]);
		if ( parsing->resolution_width == 0 | 
			parsing->resolution_height == 0)
			parsing->is_valid = 0;
	}
	free(resolution);
	return (1);
}

int	ft_parser(int argc, char **argv)
{
	t_parsing	parsing;
	int		fd;
	int		ret;

	ret = 1;
	(void) argc;
	ft_init_parsing(&parsing);
	
	fd = open(argv[1], O_RDONLY);
	
	while (ret)
	{
		ret = get_next_line(fd, &parsing.lign);
		if (parsing.lign[0] == 'R')
		{
			if(!(ft_parse_resolution(&parsing)))
				return (0);
		}
		else if(parsing.lign[0] == 'E' && parsing.lign[1] == 'A') 
		{
			if(!(ft_parse_direction_ea(&parsing)))
				return (0);
		}
		else if	(parsing.lign[0] == 'W' && parsing.lign[1] == 'E') 
		{
			if(!(ft_parse_direction_we(&parsing)))
				return (0);
		}
		else if (parsing.lign[0] == 'S' && parsing.lign[1] == 'O') 
		{
			if(!(ft_parse_direction_so(&parsing)))
				return (0);
		}
		else if (parsing.lign[0] == 'N' && parsing.lign[1] == 'O')
		{
			if(!(ft_parse_direction_no(&parsing)))
				return (0);
		}
		else if (parsing.lign[0] == 'S')
		{
			if(!(ft_parse_sprite(&parsing)))
				return (0);
		}
		else if (parsing.lign[0] == 'F')
		{
			if(!(ft_parse_floor(&parsing)))
				return (0);
		}
		else if (parsing.lign[0] == 'C')
		{
			if(!(ft_parse_ceiling(&parsing)))
				return (0);
		}

	//	printf("%s\n", parsing.lign);
		free(parsing.lign);
	}
	close(fd);
	return (parsing.is_valid);
}

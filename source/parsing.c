
#include "cub3D.h"

void	message_map_invalid(t_parsing *parsing, char *str)
{
	write(1, str, ft_strlen(str));
	parsing->is_valid = 0;
}

void	ft_init_parsing(t_parsing *parsing)
{
	parsing->lign = NULL;
	parsing->matrice = NULL;
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

void	ft_check_ch_map(t_parsing *parsing)
{
	int i;

	i = 0;
	while (parsing->lign[i])
	{
		if (parsing->lign[i] == 'N' | parsing->lign[i] == 'S' | parsing->lign[i] == 'E' | parsing->lign[i] == 'W')
		{
			if (parsing->player_found == 1)
				message_map_invalid(parsing, "Error\n Il y a plusieurs joueurs sur la map \n");
			else
				parsing->player_found = 1;
		}
		else if (!(parsing->lign[i] == ' ' | parsing->lign[i] == '0' | parsing->lign[i] == '1' | parsing->lign[i] == '2'))
			message_map_invalid(parsing, "Error\n La map est invalide\n");
		i++;
	}
}

int	ft_parse_map(t_parsing *parsing, int k)
{
	parsing->param_line_valid = 1;
	if(parsing->map_encountered == 0)
		parsing->line_num_begin_map = k;
	if(ft_strlen(parsing->lign) > parsing->line_map_len_max)
		parsing->line_map_len_max = ft_strlen(parsing->lign);
	parsing->nb_lines_map++;
	ft_check_ch_map(parsing);
	parsing->map_encountered = 1;
	return (1);
}

int	ft_malloc_matrice(t_parsing *parsing)
{
	int i;

	i = 0;
	if(!(parsing->matrice = malloc(sizeof(char *) * (parsing->nb_lines_map + 1))))
		return (0);
	while(i < parsing->nb_lines_map)
	{
		if(!(parsing->matrice[i] = malloc(sizeof(char *) * (parsing->line_map_len_max + 1))))
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_matrice(t_parsing *parsing)
{
	int	k;
	
	k = 0;
	while(parsing->matrice[k])
	{
		printf("%s\n", parsing->matrice[k]);
		free(parsing->matrice[k]);
		k++;
	}
	free(parsing->matrice);
}

int	ft_parse_map_advanced(t_parsing *parsing, char **argv)
{
	int	fd;
	int	ret;
	int	k;
	int	i;
	int	z;

	k = 1;
	z = 0;
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		return (0);
	if (ft_malloc_matrice(parsing) == 0)
		return (0);
	while((ret = get_next_line(fd, &parsing->lign)))
	{
		if (k >= parsing->line_num_begin_map)
		{
			i = 0;
			while (parsing->lign[i])
			{
				parsing->matrice[z][i] = parsing->lign[i];
				i++;
			}
			while (i <= parsing->line_map_len_max)
			{
				parsing->matrice[z][i] = ' ';
				i++;
			}
			parsing->matrice[z][i] = 0;
			z++;
		}
		free(parsing->lign);		
		k++;
	}
	free(parsing->lign);		
	parsing->matrice[z] = 0;
	ft_print_matrice(parsing);
	close(fd);
	return (1);
}

void	ft_all_params( t_parsing *parsing)
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
		message_map_invalid(parsing, "Error\n Il manque des paramètres\n");
	}
}

int	ft_check_save_flag(char *str)
{
	if (str[0] == '-' && str[1] == '-' && str[2] == 's' &&
			str[3] == 'a' && str[4] == 'v' && str[5] == 'e' && str[6] == 0)
		return (1);
	return (0);
}


int	ft_checks_cub_format(char *str)
{
	int	i;
	int	count_dot;

	count_dot = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			count_dot++;
		if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b' 
				&& str[i+4] == 0 && count_dot == 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_check_args(t_parsing *parsing, int argc, char **argv)
{
	if(argc < 2)
		message_map_invalid(parsing, "Error \n Le nombre d'argument est trop petit.\n");
	else if(argc > 3)
		message_map_invalid(parsing, "Error \n Le nombre d'argument est trop grand.\n");
	else if(argc == 3 && ft_check_save_flag(argv[2]) == 0)
		message_map_invalid(parsing, "Error \n Le troisième argument n'est pas reconnu.\n");
	else if(ft_checks_cub_format(argv[1]) == 0)
		message_map_invalid(parsing, "Error \n Le format du '.cub' n'est pas correcte.\n");
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
	parsing->param_line_valid = 1;
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
	free_split(rgb);	
	free_split(ceiling);
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
	parsing->param_line_valid = 1;
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
	free_split(rgb);	
	free_split(floor);
	return(1);
}

int	ft_parse_sprite(t_parsing *parsing)
{
	char	**sprite;
	int	fd;

	parsing->param_line_valid = 1;
	if (parsing->s_encountered == 1)
		message_map_invalid(parsing, "Error \n La ligne de param SPRITE est présente deux fois\n");
	parsing->s_encountered = 1;
	if(!(sprite = ft_split(parsing->lign, ' ')))
		return (0);
	if (sprite[0][1] != 0 | sprite[2] != 0)
		message_map_invalid(parsing, "Error \n La ligne de param S n'est pas correctement rédigée \n");
	if(!sprite[0] | !sprite[1])
		message_map_invalid(parsing, "Error \n La ligne de param S n'est pas correctement rédigée \n");
	fd = open(sprite[1], O_RDONLY);
	if (fd == -1)
		message_map_invalid(parsing, "Error \nLE SPRITE ne s'ouvre pas correctement\n");
	close(fd);
	free_split(sprite);
	return(1);
}

int	ft_parse_direction_ea(t_parsing *parsing)
{
	char	**direction;
	int	fd;

	parsing->param_line_valid = 1;
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
	free_split(direction);
	return (1);
}

int	ft_parse_direction_no(t_parsing *parsing)
{
	char	**direction;
	int	fd;

	parsing->param_line_valid = 1;
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
	free_split(direction);
	return (1);
}

int	ft_parse_direction_we(t_parsing *parsing)
{
	char	**direction;
	int	fd;

	parsing->param_line_valid = 1;
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
	free_split(direction);
	return (1);
}


int	ft_parse_direction_so(t_parsing *parsing)
{
	char	**direction;
	int	fd;

	parsing->param_line_valid = 1;
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
	free_split(direction);
	return (1);
}

int	ft_parse_resolution(t_parsing *parsing)
{
	char	**resolution;
	int	i;

	parsing->param_line_valid = 1;
	if (parsing->resolution_encountered == 1)
		message_map_invalid(parsing, "Error\n La ligne de param RESOLUTION est presente deux fois");
	parsing->resolution_encountered = 1;
	if(!(resolution = ft_split(parsing->lign, ' ')))
		return (0);
	i = 0;
	if (!resolution[2] | !resolution[1] | !resolution[0])
		message_map_invalid(parsing, "Error \n La ligne de param R n'est pas correctement rédigée \n");
	if (resolution[3] != 0)
		message_map_invalid(parsing, "Error \n La ligne de param R n'est pas correctement rédigée \n");
	if ((resolution[0][0] != 'R') | resolution [0][1])
		message_map_invalid(parsing, "Error \n La ligne de param R n'est pas correctement rédigée \n");
	if (parsing->is_valid)
	{
		while (resolution [1][i])
		{
			if (ft_isdigit(resolution[1][i]) == 0)
				message_map_invalid(parsing, "Error \n La resolution X comprend un charactère non justifié \n");
			i++;
		}
		i = 0;
		while (resolution [2][i])
		{
			if (ft_isdigit(resolution[2][i]) == 0)
				message_map_invalid(parsing, "Error \n La resolution Y comprend un charactère non justifié \n");
			i++;
		}
		parsing->resolution_width = ft_atoi(resolution[1]);
		parsing->resolution_height = ft_atoi(resolution[2]);
		if ( parsing->resolution_width == 0 | 
			parsing->resolution_height == 0)
			message_map_invalid(parsing, "Error \n Une des résolutions est égale a zero \n");
	}
	free_split(resolution);
	return (1);
}

int	ft_parser(int argc, char **argv)
{
	t_parsing	parsing;
	int		fd;
	int		ret;
	int		i;
	int		k;

	ret = 1;
	k = 0;
	ft_init_parsing(&parsing);
	ft_check_args(&parsing, argc, argv);	
	if((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);	
	while ((ret = get_next_line(fd, &parsing.lign)))
	{
		i = 0;
		k++;
		parsing.param_line_valid = 0;
		while(parsing.lign[i] == ' ')
			i++;
		if(parsing.lign[i] == 'R' && parsing.map_encountered == 0)
		{
			if(!(ft_parse_resolution(&parsing)))
				return (0);
		}
		if(parsing.lign[i] == 'E' && parsing.lign[i + 1] == 'A' && parsing.map_encountered == 0) 
		{
			if(!(ft_parse_direction_ea(&parsing)))
				return (0);
		}
		if(parsing.lign[i] == 'W' && parsing.lign[i + 1] == 'E' && parsing.map_encountered == 0) 
		{
			if(!(ft_parse_direction_we(&parsing)))
				return (0);
		}
		if (parsing.lign[i] == 'S' && parsing.lign[i + 1] == 'O' && parsing.map_encountered == 0) 
		{
			if(!(ft_parse_direction_so(&parsing)))
				return (0);
		}
		if (parsing.lign[i] == 'N' && parsing.lign[i + 1] == 'O' && parsing.map_encountered == 0)
		{
			if(!(ft_parse_direction_no(&parsing)))
				return (0);
		}
		if (parsing.lign[i] == 'S' && parsing.lign[i + 1] == ' ' && parsing.map_encountered == 0)
		{
			if(!(ft_parse_sprite(&parsing)))
				return (0);
		}
		if (parsing.lign[i] == 'F' && parsing.map_encountered == 0)
		{
			if(!(ft_parse_floor(&parsing)))
				return (0);
		}
		if (parsing.lign[i] == 'C' && parsing.map_encountered == 0)
		{
			if(!(ft_parse_ceiling(&parsing)))
				return (0);
		}
		if(parsing.lign[i] == 0 && parsing.map_encountered == 1)
		{
			message_map_invalid(&parsing, "Error\n Présence d'une ligne vide au niveau de la map\n");
			parsing.param_line_valid = 1;
		}
		if(parsing.lign[i] == 0 && parsing.map_encountered == 0)
		{
			parsing.param_line_valid = 1;
		}

		if(parsing.lign[i] == '0' | parsing.lign[i] == '1')
		{
			if(!(ft_parse_map(&parsing, k)))
				return (0);
					
		}
		if(parsing.param_line_valid == 0)
		{

			message_map_invalid(&parsing, "Error\n Une ligne n'est pas correcte\n");
		}
		free(parsing.lign);
	}
	free(parsing.lign);
	ft_all_params(&parsing);
	ft_parse_map_advanced(&parsing, argv);
	close(fd);
	printf("La map commence à la ligne numeros : %d\nLe nombre de ligne de la map est de : %d\nLa taille max de la ligne est de : %d\n", parsing.line_num_begin_map, parsing.nb_lines_map, parsing.line_map_len_max);
	return (parsing.is_valid);
}

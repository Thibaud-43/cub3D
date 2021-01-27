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

/*#define FORWARD 122
#define BACK 115
#define LEFT 113
#define RIGHT 100
#define CAM_LEFT 65361
#define CAM_RIGHT 65363
#define EXIT 65307*/

#define FORWARD 13
#define BACK 1
#define LEFT 0
#define RIGHT 2
#define CAM_LEFT 123
#define CAM_RIGHT 124
#define EXIT 53
#define MOVESPEED 0.05
#define ROTSPEED 0.02


typedef struct s_pos
{
	double	x;
	double	y;
}		t_pos;

typedef struct s_sprite
{
	int		nbr;
	double	*dist;
	t_pos	*pos;
	double	spriteX;
	double	spriteY;
	double	invDet;
	double	transformX;
	double	transformY;
	int		spriteScreenX;
	int		spriteHeight;
	int		spriteWidth;
	int		drawStartX;
	int		drawEndX;
	int		drawStartY;
	int		drawEndY;
	int		texX;
	int		texY;
	int		d;
}	t_sprite;

typedef struct  s_data {
    void        *img;
    int        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct s_texture
{
	t_data	*img;
	int		*addr;
	int		height;
	int		width;
	int		textNum;
	double		wallX;
	int		texX;
	int		texY;
	double		step;
	double		texPos;
}	t_texture;

typedef struct s_vars {
	void *mlx;
	void *win;
}	t_vars;

typedef struct s_keys 
{
	int	forward;
	int	back;
	int	camright;
	int	camleft;
	int	left;
	int	right;
}	t_keys;

typedef struct s_raycasting
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int		mapX;
	int		mapY;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	double		perpwalldist;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		width;
	int		height;
	int		x;
}	t_ray;

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
	double	player_x;
	double	player_y;
	double	moveSpeed;
	double	rotSpeed;
	char	direction;
	t_vars	vars;
	t_data	img;
	t_ray	ray;
	t_keys	keys;
	t_texture texture[5];
	t_sprite spr;
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
int		ft_parse_direction_we(t_parsing *parsing, t_map *map);
void	ft_check_ch_map(t_map *map, t_parsing *parsing);
int		ft_parse_map(t_map *map, t_parsing *parsing, int k);
int		ft_init_matrice(t_parsing *parsing, t_map *map);
int		ft_parse_map_advanced(t_parsing *parsing, char **argv, t_map *map);
void	ft_check_comformity(int i, int k, t_map *map, int *error);
void	ft_parse_map_advanced_2(t_parsing *parsing, t_map *map);
int		ft_parse_resolution(t_parsing *parsing, t_map *map);
int		ft_parse_sprite(t_parsing *parsing, t_map *map);
void	message_map_invalid(t_parsing *parsing, char *str);
void	ft_init_parsing(t_parsing *parsing);
void	free_split(char **str);
void	ft_print_matrice(t_map *map);
int		ft_raycasting(t_map *map);
void	ft_init_raycasting_1(t_map *map);
void	ft_go_forward(t_map *map);
void	ft_go_down(t_map *map);
void	ft_rotate_left(t_map *map);
void	ft_rotate_right(t_map *map);
void	ft_go_left(t_map *map);
void	ft_go_right(t_map *map);
int		hook(int keycode, t_map *map);
int		ft_release(int keycode, t_map *map);
void		ft_init_raycasting_1(t_map *map);
void		ft_init_raycasting_2(t_map *map);
void		ft_init_raycasting_3(t_map *map);
void		ft_init_deltadist(t_map *map);
void		ft_init_dist(t_map *map);
void		ft_texture(t_map *map);
int			ft_init_sprites(t_map *map);
void		ft_order_sprites(t_map *map);
void		ft_sprites(t_map *map);
#endif


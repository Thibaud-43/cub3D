# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/20 17:04:20 by trouchon          #+#    #+#              #
#    Updated: 2021/01/08 10:44:38 by trouchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= source/main.c source/parsing.c source/parsing_args.c source/parsing_ceiling.c source/parsing_direction_ea.c source/parsing_direction_no.c source/parsing_direction_so.c source/parsing_direction_we.c source/parsing_floor.c source/parsing_map_1.c source/parsing_map_2.c source/parsing_map_3.c  source/parsing_resolution.c source/parsing_sprite.c source/parsing_utils.c 
OBJS			= $(SRCS:.c=.o)
INC			=  -I includes/ -I libft/ -I $(MLX_DIR)
CC			= clang
RM			= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -fsanitize=address
MLX_DIR			= ./mlx
MLX			= $(MLX_DIR)/libmlx_Linux.a
LIBFT_DIR		= ./libft
LIBFT			= $(LIBFT_DIR)/libft.a
LIBS			= -L $(LIBFT_DIR) -lft -L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext
HEADERS_DIR		= includes
SRC_DIR			= source


NAME			= cub3D

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INC)

all:			$(NAME)

$(NAME):		$(LIBFT) $(MLX) $(OBJS)
				$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBS) -o $(NAME)
$(LIBFT):
				$(MAKE) -C $(LIBFT_DIR)
$(MLX):
				$(MAKE) -C $(MLX_DIR)
clean:
				$(MAKE) -C libft/ clean
				$(MAKE) -C mlx/ clean
				$(RM) $(OBJS)
fclean:			clean
				$(RM) $(NAME) 

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/20 17:04:20 by trouchon          #+#    #+#              #
#    Updated: 2020/11/20 17:04:28 by trouchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	
OBJS			= $(SRCS:.c=.o)
BONUS_OBJS		= $(BONUS:.c=.o)
CC				= clang
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.

NAME			= a.out

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS) libft.h.gch

fclean:			clean
					$(RM) $(NAME) 

re:				fclean $(NAME)

bonus:			$(OBJS) $(BONUS_OBJS)
					ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY:			all clean fclean re bonus

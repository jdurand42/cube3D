# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019\06/24 18:35:31 by jdurand           #+#    #+#              #
#    Updated: 2019/10/13 20:17:57 by jdurand          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cube3D

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

LIB		=	./libft/libft.a

SRCS 	=	./srcs/main.c ./srcs/ft_errors.c ./srcs/ft_ini.c ./srcs/ft_graph.c

all		:	$(NAME)

$(NAME) :
			cd ./libft ; make bonus ; cd .. ;

compil	:
			gcc -o $(NAME) -lmlx -framework OpenGL -framework Appkit \
			$(SRCS) $(LIB)

sani	:
			gcc -o $(NAME) -g3 -fsanitize=address -lmlx -framework OpenGL -framework Appkit $(SRCS) $(LIB)

clean	:
			cd ./libft ; make clean ; cd .. ;
			$(RM) $(OBJS) $(BONUS)

fclean	:	clean
			cd ./libft ; make fclean ; cd .. ;
			$(RM) $(NAME)

re	:	fclean	all

.PHONY	:	clean	fclean	all

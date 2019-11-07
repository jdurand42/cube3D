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

SRCS 	=	./srcs/main.c ./srcs/ft_errors.c

all		:	$(NAME)

$(NAME) :
			cd ./libft ; make bonus ; cd .. ;
			gcc -o $(NAME) $(SRCS) $(LIB)
compil	:
			gcc -o $(NAME) $(SRCS) $(LIB)

clean	:
			cd ./libft ; make clean ; cd .. ;
			$(RM) $(OBJS) $(BONUS)

fclean	:	clean
			cd ./libft ; make fclean ; cd .. ;
			$(RM) $(NAME)

re	:	fclean	all

.PHONY	:	clean	fclean	all

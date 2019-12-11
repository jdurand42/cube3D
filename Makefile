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

SRCS 	=	./srcs/main.c ./srcs/ft_errors.c ./srcs/ft_parsing.c \
			./srcs/ft_parsing2.c ./srcs/ft_utils.c ./srcs/ft_game.c \
			./srcs/ft_rays.c ./srcs/ft_dda.c ./srcs/ft_inputs.c \
			./srcs/ft_clean.c ./srcs/ft_texturing.c ./srcs/ft_sprites.c \
			./srcs/ft_utils2.c ./srcs/ft_draw_sprites.c ./srcs/ft_exit_stuff.c \
			./srcs/ft_dda2.c ./srcs/ft_inputs2.c ./srcs/ft_utils3.c \
			./srcs/ft_texturing2.c ./srcs/ft_sprites2.c ./srcs/ft_inputs3.c

all		:	$(NAME)

$(NAME) :
			cd ./libft ; make bonus ; cd .. ;
			gcc -o $(NAME) -lmlx -framework OpenGL -framework Appkit \
			$(SRCS) $(LIB)

compil	:
			make clean ;
			gcc -o $(NAME) -lmlx -framework OpenGL -framework Appkit \
			$(SRCS) $(LIB)

bmp     :
			gcc -o $(NAME) -lmlx -framework OpenGL -framework Appkit \
			$(SRCS) $(LIB) nmp/libbmp.a

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

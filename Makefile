# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 12:19:54 by tpaaso            #+#    #+#              #
#    Updated: 2023/01/02 15:10:04 by tpaaso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRCS =	src/main.c src/texture_read.c src/read.c src/menu_main.c \
		src/menu_char.c	src/key.c src/image.c src/draw.c src/2dimage.c \
		src/exit_program.c

OBJ = $(SRC:.c=.o)

INC = libft/libft.a

CCFL =	gcc -Wall -Wextra -Werror -L /usr/local/lib -lmlx -I /minilibx/ \
		-framework OpenGL -framework AppKit

LIBFT = libft/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@$(CCFL) -o $(NAME) $(OBJ) $(INC) $(SRCS)

clean:
	@/bin/rm -f $(OBJ)
	@make -C $(LIBFT) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

proper: all clean

.PHONY = all $(NAME) clean fclean re

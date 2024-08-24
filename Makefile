# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichaoub <ichaoub@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/18 14:50:48 by ichaoub           #+#    #+#              #
#    Updated: 2024/07/05 20:09:46 by ichaoub          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

FILES = \
	./main.c \
	./init.c \
	./utils.c \
	./events.c \
	./render.c

OBJ = $(FILES:.c=.o)

MLXLIB	= -L./minilibx-linux -lmlx -lXext -lX11 -lm
MLXINC  = -I./minilibx-linux

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLXLIB) -o ${NAME}

%.o: %.c
	$(CC) -c -Wall -Wextra -Werror $(MLXINC) $< -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean all

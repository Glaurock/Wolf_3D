# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wnoth <wnoth@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/21 10:59:48 by wnoth             #+#    #+#              #
#    Updated: 2018/01/02 11:24:10 by gmonnier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=wolf3d
SRC= srcs/inputs.c \
	srcs/map.c \
	srcs/ray.c \
	srcs/camera.c \
	srcs/wolf.c \
	srcs/parse.c \
	srcs/textures.c \
	srcs/floor_casting.c \
	srcs/collision.c \
	srcs/sprites.c \
	srcs/sprites_utils.c \
	srcs/update.c \
	srcs/error.c \
	srcs/line_format.c \
	srcs/draw.c \
	srcs/miscellaneous.c \
	srcs/verif_number.c \
	srcs/utils.c

CC=clang
CFLAGS=-I libft/includes -I minilibx_macos/ -I get_next_line/ -I includes/ -Wall -Wextra -Werror
OBJ=$(SRC:.c=.o)
LDFLAGS=-L libft/ -L minilibx_macos/
LIBS=-lft -lm -lmlx -framework OpenGL -framework AppKit

$(NAME): $(OBJ)
	make -C libft/
	make -C minilibx_macos/
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LIBS)

all: $(NAME)

clean:
	make -C libft/ clean
	make -C minilibx_macos/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

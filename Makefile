#Makefile by Mason

NAME = fract_ol

CC = gcc
CFLAGS = -Wall -Wextra -Werror

FILES = main.c toggle_keys.c

SRCS = $(addprefix srcs/, $(FILES))

FRAMEWORKS = -framework OpenGL -framework AppKit

INC_MINILIBX = -I minilibx
LINK_MINILIBX = -L minilibx -lmlx
MINILIBX = $(INC_MINILIBX) $(LINK_MINILIBX)

all: $(NAME)

minilibx/libmlx.a:
	make -C minilibx re

$(NAME): minilibx/libmlx.a
	$(CC) $(CFLAGS) $(MINILIBX) \
		-I . $(FRAMEWORKS) $(FILES) -o $(NAME)

build:
	mkdir build

clean:
	rm -rf build

tclean:
	make -C minilibx clean
	make fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

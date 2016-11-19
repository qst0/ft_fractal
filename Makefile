#Makefile by Mason

NAME = fract_ol

CC = gcc
CFLAGS = -Wall -Wextra -Werror

FILES = main.c \
		toggle_keys.c \
	   	mouse_hooks.c \
	   	image.c \
	   	hooks.c \
		color.c \
		draw_fractal.c \
		fractals.c \
		gfx.c

SRC = $(addprefix src/, $(FILES))

FRAMEWORKS = -framework OpenGL -framework AppKit
INC = -I ./include


INC_MINILIBX = -I minilibx
LINK_MINILIBX = -L minilibx -lmlx
MINILIBX = $(INC_MINILIBX) $(LINK_MINILIBX)

all: $(NAME)

minilibx/libmlx.a:
	@echo "Making minilibx"
	@make -C minilibx re

$(NAME): $(SRC) minilibx/libmlx.a
	@$(CC) $(CFLAGS) $(MINILIBX) \
		$(INC) $(FRAMEWORKS) $(SRC) -o $(NAME)
	@echo "Creating ./fract_ol"

build:
	mkdir build

clean:
	@rm -rf build
	@echo "clean successful"

tclean:
	make -C minilibx clean
	make fclean

fclean: clean
	@echo "Removing ./fract_ol"
	rm -f $(NAME)

re: fclean all

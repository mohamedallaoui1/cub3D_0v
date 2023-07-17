NAME=cub3D
CC= cc
libft= libft/libft.a
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
SRC= main.c parsing/texture_pars.c parsing/color_pars.c parsing/map_pars.c

OBJ= $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	make -C libft
	$(CC) $(OBJ) $(CFLAGS) $(libft) -o $(NAME) -lmlx -framework OpenGL -framework AppKit

clean:
	rm -rf $(OBJ)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

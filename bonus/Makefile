NAME=cub3D
CC= cc
libft= libft/libft.a
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
SRC= main.c parsing/texture_pars.c parsing/color_pars.c parsing/map_pars.c parsing/utils.c parsing/pars_main.c movements.c\
Controls.c RayCasting.c color_manip.c initialize.c system_rendering.c utils.c parsing/utils_2.c sprites.c initialze_v2.c parsing/texture_utils.c minimap.c movements_v2.c\

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

NAME=cub3D
NAME_BONUS=cub3D_BONUS
CC= cc
libft= libft/libft.a
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
SRC= ./mandatory/main.c ./mandatory/parsing/texture_pars.c ./mandatory/parsing/color_pars.c ./mandatory/parsing/map_pars.c\
 ./mandatory/parsing/utils.c ./mandatory/parsing/pars_main.c ./mandatory/movements.c\
./mandatory/Controls.c ./mandatory/RayCasting.c ./mandatory/color_manip.c ./mandatory/initialize.c \
./mandatory/system_rendering.c ./mandatory/utils.c ./mandatory/parsing/texture_pars_utils.c

SRC_BONUS= ./bonus/main.c ./bonus/parsing/texture_pars.c ./bonus/parsing/color_pars.c ./bonus/parsing/map_pars.c\
 ./bonus/parsing/utils.c ./bonus/parsing/pars_main.c ./bonus/movements.c\
./bonus/Controls.c ./bonus/RayCasting.c ./bonus/color_manip.c ./bonus/initialize.c ./bonus/system_rendering.c \
./bonus/utils.c ./bonus/parsing/utils_2.c ./bonus/sprites.c ./bonus/initialze_v2.c\
./bonus/parsing/texture_utils.c ./bonus/minimap.c ./bonus/movements_v2.c\

OBJ_BONUS= $(SRC_BONUS:.c=.o)

OBJ= $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	make -C libft
	$(CC) $(OBJ) $(CFLAGS) $(libft) -o $(NAME) -lmlx -framework OpenGL -framework AppKit
bonus:$(NAME_BONUS)
$(NAME_BONUS): $(OBJ_BONUS)
	make -C libft
	$(CC) $(OBJ_BONUS) $(CFLAGS) $(libft) -o $(NAME_BONUS) -lmlx -framework OpenGL -framework AppKit


clean:
	rm -rf $(OBJ) $(OBJ_BONUS)
	make clean -C libft

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)
	make fclean -C libft

re: fclean all

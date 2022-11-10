CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
RM = rm -rf
LIB = -L ./mlx -lmlx -L ./libft -lft
NAME = so_long
GRAPHICS = -L mlx/ -lmlx -framework OpenGL -framework Appkit
FOLDER = src/
FILES = main.c \
				events.c \
				fill_map.c \
				key_event.c \
				map_errors.c \
				window_init.c \
				utils.c \
				utils2.c

SRC = $(addprefix $(FOLDER), $(FILES))
OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME):	$(OBJ)
	@$(MAKE) -C ./libft
	@$(MAKE) -C ./mlx
	@$(CC) $(CFLAGS) $(GRAPHICS) -o $(NAME) $(OBJ) $(LIB)

clean:
	@$(MAKE) -C ./libft clean
	@$(MAKE) -C ./mlx clean
	@$(RM) $(OBJ)

fclean: clean
	@$(MAKE) -C ./libft fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean

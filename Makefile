NAME = cub3D

CFLAGS = -Wall -Wextra -Werror

LIBFT = Libft/libft.a

MLX = minilibx-linux/libmlx.a

MLXFLAGS = -lXext -lX11 -lm -lz

SRC = main.c utils.c \
	  validation.c get_next_line.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):$(OBJ) $(Libft) cub3D.h Makefile
	cc $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ) $(BNOBJ)

fclean:clean
	rm -f $(NAME)

re:fclean all

.PHONY: all clean fclean re
SRCS = src/main.c\
	src/empty.c\
	src/exit.c\
	src/game.c\
	src/graphics.c\
	src/miscellaneous.c\
	src/parser_utils.c\
	src/parser.c\
	src/path_finding.c

OBJS_DIR = obj

OBJS = $(SRCS:src/%.c=$(OBJS_DIR)/%.o)

NAME = so_long

INCLUDES = -I./libft -I/usr/include -Imlx

MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

MLX = mlx/libmlx.a

HEADER = includes/so_long.h

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

LIBFT = libft/libft.a

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(LIBFT) $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -L./libft -lft -o $(NAME)

$(OBJS_DIR)/%.o: src/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@ 

$(LIBFT):
	make -C libft

$(MLX):
	make -C mlx

clean:
	@make clean -C libft
	@make clean -C mlx
	rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean all

leakcheck: all
	valgrind --leak-check=full --trace-children=yes --track-fds=yes ./so_long
SRCS = src/main.c\
	src/

OBJS := $(SRCS:.c=.o)

NAME = so_long

INCLUDES = -I/usr/include -Imlx

MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

HEADER = includes/so_long.h

OBJS_BONUS := $(SRCS_BONUS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

$(NAME): libs $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME) $(MLX_FLAGS)

%.o: %.c $(HEADER)
	$(CC) -I./libft $(CFLAGS) -c $< -o $@ $(INCLUDES)

libs:
	make -C libft

clean:
	@make clean -C libft
	rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean all

leakcheck: all
	valgrind --leak-check=full --trace-children=yes --track-fds=yes ./so_long
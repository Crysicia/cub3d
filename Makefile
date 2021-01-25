CC			= gcc
CFLAGS 		= -g -Wall #-Werror -Wextra
RM 			= rm -f
NAME 		= test
HEADERS 	= -I./includes
LIBS = -Lmlx -lmlx -Imlx_linux -lXext -lX11 -lm -Llibft -lft
MLX = libmlx.a
LIBFT = libft.a

SRCS 		= srcs/main.c \
			  srcs/shapes.c \
			  srcs/ft_math.c \
			  srcs/init.c \
			  srcs/debug.c \
			  srcs/input.c \
			  srcs/raycasting.c \
			  srcs/utils.c \
			  srcs/texture.c \
			  srcs/sprite.c
OBJS 		= $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(MLX) $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(MLX):
	@$(MAKE) -C mlx

$(LIBFT):
	@$(MAKE) -C libft

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

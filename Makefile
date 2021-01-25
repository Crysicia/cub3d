CC			= gcc
CFLAGS 		= -g -Wall #-Werror -Wextra
RM 			= rm -f
NAME 		= test
HEADERS 	= -I./includes
LIBS = -Lmlx -lmlx -Imlx_linux -lXext -lX11 -lm
MLX = libmlx.a

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

$(NAME): $(MLX) $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(MLX):
	@$(MAKE) -C mlx

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

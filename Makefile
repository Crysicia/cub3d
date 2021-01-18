CC			= gcc
CFLAGS 		= -g -Wall #-Werror -Wextra
RM 			= rm -f
NAME 		= test
HEADERS 	= .
LIBS = -Lmlx -lmlx -Imlx_linux -lXext -lX11 -lm
MLX = libmlx.a

SRCS 		= main.c \
			  shapes.c \
			  ft_math.c \
			  init.c \
			  debug.c \
			  input.c \
			  raycasting.c \
			  utils.c \
			  texture.c \
			  sprite.c
OBJS 		= $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

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

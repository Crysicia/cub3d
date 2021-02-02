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
			  srcs/sprite.c \
			  srcs/parse_color.c \
			  srcs/parsing_utils.c \
			  srcs/parse_resolution.c \
			  srcs/parse_texture.c \
			  srcs/get_next_line.c \
			  srcs/get_next_line_utils.c \
			  srcs/parse_file.c \
			  srcs/parse_map.c \
			  srcs/parse_map_utils.c \
			  srcs/floodfill.c \
			  srcs/error.c \

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
	@$(MAKE) clean -C libft

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) fclean -C libft

re: fclean all

.PHONY: all clean fclean re

#-------------------------------#
# TODO :
# [✔] - Add clean exit (free everything)
# [] - Fix GNL leak
# [] - Add east and west textures
# [] - Implement queue for floodfill
# [] - Add close event on red cross
# [] - Implement bitmap save
# [] - Implement strafing
# [] - Fix sprites bug at angle 0
# [] - Clean code
# [] - Compile with errrors
# [] - Code "a la norme"™️

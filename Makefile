CC			= gcc
CFLAGS 		= -g -Wall -Wextra -Werror
RM 			= rm -f
NAME 		= test
HEADERS 	= -I./includes
LIBS = -Lmlx -lmlx -Imlx_linux -lXext -lX11 -lm -Llibft -lft
MLX = libmlx.a
LIBFT = libft.a

SRCS 		= srcs/main.c \
			  srcs/shapes.c \
			  srcs/init.c \
			  srcs/init_utils.c \
			  srcs/input.c \
			  srcs/raycasting.c \
			  srcs/utils.c \
			  srcs/texture.c \
			  srcs/sprite.c \
			  srcs/sprite_utils.c \
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
			  srcs/bitmap.c \
			  srcs/bitmap_utils.c \
			  srcs/movement.c \

OBJS 		= $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(MLX) $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(MLX):
	@$(MAKE) -C mlx

$(LIBFT):
	@$(MAKE) bonus -C libft

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
# [✔] - Fix GNL leak
# [✔] - Add east and west textures
# [✔] - Implement strafing
# [✔] - Add close event on red cross
# [✔] - Implement queue for floodfill
# [✔] - Implement bitmap save
# [✔] - Compile with errrors
# [] - Fix sprites bug at angle 0
# [] - Clean code
# [] - Code "a la norme"™️

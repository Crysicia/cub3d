CC			= gcc
CFLAGS 		= -g -Wall #-Werror -Wextra
RM 			= rm -f
NAME 		= test
HEADERS 	= includes

SRCS 		= main.c
OBJS 		= $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I $(HEADERS) -I/usr/include -Imlx_linux -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

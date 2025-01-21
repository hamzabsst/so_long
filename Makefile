CC = cc
CFLAGS = -Wall -Werror -Wextra

LDFLAGS = -L/usr/X11/lib -lX11 -lXext

MYLIB_DIR = mylib
MYLIB = $(MYLIB_DIR)/myLib.a

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

NAME = so_long

SRCS =	src/main.c \
		src/check_errors.c \
		src/check_errors2.c \
		src/map_parsing.c \
		src/init_txr.c \

OBJS = $(SRCS:.c=.o)

all: $(MYLIB) $(MLX) $(NAME)

$(MYLIB):
		@$(MAKE) -C $(MYLIB_DIR)
$(MLX):
		@$(MAKE) -C $(MLX_DIR)

%.o: %.c inc/so_long.h
		@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(MYLIB) $(MLX)
		@$(CC) $(CFLAGS) $(OBJS) $(MYLIB) $(MLX) $(LDFLAGS) -o $(NAME)

clean:
		@rm -f $(OBJS)
		@$(MAKE) clean -C $(MYLIB_DIR)
		@$(MAKE) clean -C $(MLX_DIR)

fclean: clean
		@rm -f $(NAME)
		@$(MAKE) fclean -C $(MYLIB_DIR)
		@$(MAKE) fclean -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re

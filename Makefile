NAME	:= so_long

C_GREEN = \033[0;32m
C_RED = \033[0;31m
C_BLUE = \033[0;34m
C_END=\033[0m

CFLAGS	:= -Wall -Wextra -Werror #-g3 -fsanitize=address
LIBMLX	:= ./lib/MLX42
HEADERS	:= -I . -I $(LIBMLX)/include 
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm libft/libft.a
SRCS	:=	main.c						\
			map/map_maker.c				\
			map/map_walls.c				\
			map/collectibles.c			\
			map/parsing.c				\
			map/parsing_utils.c			\
			init_player/init_player.c	\
			init_player/player_menu.c	\
			mechanic/movements.c		\
			mechanic/interaction.c		\
			mechanic/hook.c
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@gcc $(CFLAGS) $(HEADERS) -o $@ -c $<

$(NAME): $(OBJS) libmlx
	@gcc $(CFLAGS) $(OBJS) $(HEADERS) $(LIBS) -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)
	@echo "$(C_GREEN)all files compiled with $(CFLAGS)$(C_END)"
	@echo "$(C_GREEN)$(NAME) compiled$(C_END)"

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@echo "$(C_RED)$(NAME) cleanse$(C_END)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)/build/libmlx42.a
	@rm -rf libmlx42.a
	@echo "$(C_RED)Update: Herobrine has been removed.$(C_END)"

re: fclean all

.PHONY: all, clean, fclean, re, libmlx

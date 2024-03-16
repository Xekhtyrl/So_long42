NAME	:= so_long

C_GREEN = \033[0;32m
C_RED = \033[0;31m
C_BLUE = \033[0;34m
C_PURPLE = \033[1;35m
C_END = \033[0m

_END = $'\x1b[0m'
_BOLD = $'\x1b[1m'

CFLAGS	= -Wall -Wextra -Werror -g3 #-fsanitize=address
LIBMLX	= ./lib/MLX42
LIBFT	= ./lib/libft
HEADERS	= -I . -I $(LIBMLX)/include 
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
SRCS	=	main.c						\
			map/map_maker.c				\
			map/map_walls.c				\
			map/collectibles.c			\
			map/parsing.c				\
			map/parsing_utils.c			\
			init_player/init_player.c	\
			init_player/player_menu.c	\
			mechanic/movements.c		\
			mechanic/interaction.c		\
			mechanic/hook.c				\
			free_game/free_function.c	\
			free_game/free_functions_bis.c
SRCS_BONUS	=	Bonus/main.c						\
				Bonus/map/map_maker.c				\
				Bonus/map/map_walls.c				\
				Bonus/map/collectibles.c			\
				Bonus/map/parsing.c					\
				Bonus/map/parsing_utils.c			\
				Bonus/init_player/init_player.c		\
				Bonus/init_player/player_menu.c		\
				Bonus/mechanic/movements.c			\
				Bonus/mechanic/interaction.c		\
				Bonus/mechanic/mob_interaction.c	\
				Bonus/mechanic/hook.c				\
				Bonus/mob/mob.c						\
				Bonus/mob/mob_moveset.c				\
				Bonus/free_game/free_function.c		\
				Bonus/free_game/free_functions_bis.c
OBJS	= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@gcc $(CFLAGS) $(HEADERS) -o $@ -c $<

$(NAME): $(OBJS) makelibft libmlx
	@gcc $(CFLAGS) $(OBJS) $(HEADERS) $(LIBS) -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)
	@echo "$(C_GREEN)all files for $(_BOLD)$(NAME)$(_END)$(C_GREEN) compiled with $(C_PURPLE) $(CFLAGS) $(C_END)"
	@echo "$(C_GREEN)$(_BOLD)$(NAME)$(_END)$(C_GREEN) compiled$(C_END)"

makelibft:
	@make -C $(LIBFT)
	@echo "$(C_GREEN) libft compiled $(C_END)"

bonus: $(OBJS_BONUS) makelibft libmlx
	@gcc $(CFLAGS) $(OBJS_BONUS) $(HEADERS) $(LIBS) -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)_bonus
	@echo "$(C_GREEN)all files for $(_BOLD)$(NAME)_bonus$(_END)$(C_GREEN) compiled with $(C_PURPLE) $(CFLAGS) $(C_END)"
	@echo "$(C_GREEN)$(_BOLD)$(NAME)_bonus$(_END)$(C_GREEN) compiled$(C_END)"

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean
	@echo "$(C_RED)$(_BOLD)$(NAME)$(_END)$(C_RED) cleanse$(C_END)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME)_bonus
	@rm -rf $(LIBMLX)/build/libmlx42.a
	@make -C $(LIBFT) fclean
	@echo "$(C_RED)Update: Herobrine has been removed.$(C_END)"

re: fclean all

.PHONY: all, clean, fclean, re, makelibft, libmlx, bonus

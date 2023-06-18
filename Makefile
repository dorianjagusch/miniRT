# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 11:46:33 by djagusch          #+#    #+#              #
#    Updated: 2023/06/18 18:58:57 by djagusch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

### SET UP ###
CC = gcc
CFLAGS = -I$I
#OS := $(shell uname -a)
#ifeq ($(OS),Darwin)
#	CCFLAGS += -framework OpenGL -framework AppKit
MINILIBX = mlx_linux/libmlx.a
#else
#CFLAGS += -lXext -lX11
#MINILIBX = minilibx/libmlx_li
#ndif

RM = /bin/rm -f
RMDIR = /bin/rmdir -p

LIBFT = libft/libft.a

S = srcs
O = objs
I = incl

FILES = get_colour \
	set_scene \
	main \
	ft_vec3_calc \
	ft_vmult \
	ft_vadd \
	render \
	input \
	minirt \
	clean_up \
	ft_help \
	getters \
	handlers \
	error_handling \

HEADER = minirt \
	linux_keys \
	libft \
	macos_keys \
	errors \
	scene \
	vector \
	mlx

HEADER := $(addprefix $I/,$(addsuffix .h,$(HEADER)))

SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name "$(FILE).c"))
OBJ := $(notdir $(SRCS))
OBJS := $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS = $(dir $(OBJS))

NAME = miniRT

### RULES ###
all: $(NAME)

minilib: $(MINILIBX)

libft: $(CFLAGS)

print:
	@echo $(OBJS)

#	ifeq ($(OS),Darwin)
#		@$(CC) $(CFLAGS) $(OBJS) -L$(dir $(MINILIBX)) -lmlx -Llibft -lft -o $(NAME)
#	else
# -I/usr/lib -I/usr/include
#	$(CC) $(CFLAGS) $(OBJS) -L$(dir $(MINILIBX)) -lmlx -lm -Llibft -lft  -o $(NAME)
#	endif
$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(HEADER) $(OBJS) -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) -O3
	@echo "$(COLOUR_GREEN) $(NAME) successfully created$(COLOUR_END)"

$(MINILIBX):
	$(MAKE) -C $(dir $(MINILIBX))
	@echo "$(COLOUR_GREEN) $(MINILIBX) successfully created$(COLOUR_END)"

$(LIBFT):
	@$(MAKE) -C libft
	@echo "$(COLOUR_GREEN) $(LIBFT) successfully created$(COLOUR_END)"

$O:
	@mkdir -p $@ $(O_DIRS)

ifeq ($(OS),Darwin)
$O/%.o: $S/%.c $(HEADER) | $O
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@
else
$O/%.o: $S/%.c $(HEADER) | $O
		@$(CC) -I$I -I/usr/include -Imlx_linux -O3 -c $< -o $@
endif
	@echo "$(COLOUR_GREEN) $@ successfully created$(COLOUR_END)"

clean:
	@$(MAKE) -C $(dir $(MINILIBX)) clean
	@$(MAKE) -C libft clean
	@echo "$(COLOUR_RED) $(MINILIBX) removed$(COLOUR_END)"
	@echo "$(COLOUR_RED) $(LIBFT) removed$(COLOUR_END)"
	@$(RM) $(OBJS)
	@if [ -d $O ]; then $(RM) -rf $(O_DIRS) $O; fi

fclean : clean
	$(MAKE) -C libft fclean
	@$(RM) $(NAME)
	@echo "$(COLOUR_RED) $(NAME) removed$(COLOUR_END)"

re: fclean $(NAME)

.PHONY: all clean fclean re

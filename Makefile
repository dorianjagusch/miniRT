# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 11:46:33 by djagusch          #+#    #+#              #
#    Updated: 2023/06/25 12:32:46 by djagusch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

### SET UP ###
CC = cc
CFLAGS = -Wall -Werror -Wextra
OS := $(shell uname)

ifeq ($(OS),Darwin)
CFLAGS += -framework OpenGL -framework AppKit
MINILIBX = mlx/libmlx.a
LIBS = -L$(dir $(MINILIBX)) -lmlx -Llibft -lft
else
MINILIBX = mlx_linux/libmlx.a
LIBS = -Llibft -lft -L$(dir $(MINILIBX)) -lmlx_Linux \
	-L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
endif

RM = /bin/rm -f
RMDIR = /bin/rmdir -p

LIBFT = libft/libft.a

S = srcs
O = objs
I = incl

FILES = get_colour \
	colour_vec \
	render \
	cylinder_distance \
	plane_distance \
	light \
	sphere_distance \
	min_distance \
	get_normal \
	main \
	ft_vsub \
	ft_vec3_calc \
	ft_vmult \
	ft_vadd \
	ft_vclamp \
	ft_vscale \
	hit_shader \
	input \
	clean_up \
	set_scene \
	ft_help \
	set_image \
	getters \
	handlers \
	error_handling \
	camera \
	print_scene \
	print_objs

HEADER = vector_math \
	minirt \
	linux_keys \
	libft \
	shaders \
	macos_keys \
	errors \
	scene \
	mlx \
	print_helpers

HEADER := $(addprefix $I/,$(addsuffix .h,$(HEADER)))

SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name "$(FILE).c"))
OBJS := $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS := $(dir $(OBJS))

NAME = miniRT

### RULES ###
all: $(NAME)

minilib: $(MINILIBX)

libft: $(LIBFT)

print:
	@echo $(dir $(MINILIBX))
	@echo $(dir $(MINILIBX))

# Make produes the .h.gch files sees them as additional output thus does not allow the naming of the output
# need to figure out why it precompiles them

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	@$(CC) $(CFLAGS) $(OBJS) -I$I $(HEADER) $(LIBS) -O3 -g
	@echo "$(COLOUR_GREEN) $(NAME) successfully created$(COLOUR_END)"

$(MINILIBX):
	$(MAKE) -C $(dir $(MINILIBX))
	@echo "$(COLOUR_GREEN) $(MINILIBX) successfully created$(COLOUR_END)"

$(LIBFT):
	@$(MAKE) -C libft
	@echo "$(COLOUR_GREEN) $(LIBFT) successfully created$(COLOUR_END)"

$O:
	@mkdir -p $@ $(O_DIRS)

$O/%.o: $S/%.c $(HEADER) | $O
	@$(CC) -I$I -O3 -c $< -o $@
	@echo "$(COLOUR_GREEN) $@ successfully created$(COLOUR_END)"

clean:
	@$(MAKE) -C $(dir $(MINILIBX)) clean
	@$(MAKE) -C libft clean
	@echo "$(COLOUR_RED) $(MINILIBX) removed$(COLOUR_END)"
	@echo "$(COLOUR_RED) $(LIBFT) removed$(COLOUR_END)"
	@$(RM) $(OBJS)
	@if [ -d $O ]; then $(RM) -rf $(O_DIRS) $O; fi

fclean : clean
	@$(MAKE) -C libft fclean
	@$(RM) $(NAME)
	@echo "$(COLOUR_RED) $(NAME) removed$(COLOUR_END)"

re: fclean $(NAME)

.PHONY: all clean fclean re
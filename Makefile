# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 11:46:33 by djagusch          #+#    #+#              #
#    Updated: 2023/07/24 16:08:11 by djagusch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

### SET UP ###
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
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

FILES = camera \
	colour_vec \
	get_colour \
	box_distance \
	cylinder_distance \
	disk_distance \
	dist_cone \
	get_normal \
	light \
	min_distance \
	plane_distance \
	sphere_distance \
	triangle_distance \
	cone_distance \
	main \
	render \
	clean_up \
	create_bonus_objs \
	create_objs \
	error_handling \
	ft_help \
	ft_split3 \
	getters \
	handlers \
	input \
	is_obj \
	light_visibility \
	set_image \
	set_scene \
	texture_setup \
	brick_pattern \
	checker_pattern \
	hit_info \
	hit_shader \
	texture_colour \
	cylinder_map \
	planar_map \
	sphere_map \
	triangle_map \
	cone_map \
	vec_add \
	vec_clamp \
	vec_crossprod \
	vec_dist \
	vec_dotprod \
	vec_inv \
	vec_isnan \
	vec_mag \
	vec_mult \
	vec_neg \
	vec_normalize \
	vec_propadd \
	vec_reflect \
	vec_rotate \
	vec_scale \
	vec_sub \
	vec_add_array

HEADER = vector_math \
	minirt \
	objects \
	linux_keys \
	libft \
	shaders \
	macos_keys \
	errors \
	scene \
	mlx \
	patterns

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
	@echo 	$(CC) $(CFLAGS) $(OBJS) -I$I $(HEADER) $(LIBS) -O3

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS) -I$I $(LIBS) -o $(NAME)
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
	@$(CC) -I$I -c $< -o $@ -g
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
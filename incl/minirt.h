/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/18 02:10:20 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h> //

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# ifdef __APPLE__
#  include "macos_keys.h"
# else
#  include "linux_keys.h"
# endif
# include "libft.h"
# include "errors.h"
# include "vector_math.h"
# include "scene.h"
# include "shaders.h"
# include <float.h>
# include "materials.h"
# include "print_helpers.h"

// DEFAULTS
# define WIDTH 860
# define HEIGHT 520
# define BOUNCES 1
# define EXT_LEN 3
# define EXTENSION ".rt"
# define WHITE 0xFFFFFFFF
# define FOCALDEPTH
# define RATIO 0
# define REAL 1
# define BALANCE 2
# define INT 3
# define ANGLE 4

typedef struct s_window
{
	void	*mlx;
	void	*win;
}			t_window;

typedef struct s_img
{
	t_window	win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			move;
	t_scene		scene;
	int			is_help;
	int			error;
}				t_img;

// MINIRT
void	set_image(t_img *img);
void	set_scene(t_scene *scene, char *av);
void	render(t_img *img);
void	free_img(t_img *img);
void	ft_options(void);
void	ft_error(int error);

// VIEW HANDLERS
int		ft_toggle_help(t_img *img);
void	ft_toggle_move(t_img *img);
void	ft_change_bounces(t_img *img, int key);

// INPUT HANDLERS
int		user_input(t_img *img);
int		mouse_position(int x, int y, t_img *img);
int		mouse_handler(int mouse_action, int x, int y, t_img *img);
int		ft_close(t_img *img);
int		key_handler(int key, t_img *img);
void	ft_focal(int mouse_action, int x, int y, t_img *img);
void	ft_move(t_img *img, int key);

int		ft_close_win(t_img *img);
void	set_active(t_img *img, u_int8_t *active);

// COLOUR FUNCTIONS
int32_t	create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

void	camera_move(int key, t_img *img);

#endif

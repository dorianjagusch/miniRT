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

# include "mlx.h"
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
# include "scene.h"
# include "libft.h"
# include "errors.h"

# if 1
#  define WIDTH 500
#  define HEIGHT 500
#  define DEBUG_ONLY(...) ((void)0)
# else
#  define WIDTH 500
#  define HEIGHT 500
#  define DEBUG_ONLY(...) __VA_ARGS__
# endif

# define BOUNCES 3
# define EXT_LEN 3
# define EXTENSION ".rt"
# define WHITE 0xFFFFFFFF
# define FOCALDEPTH
# define RATIO 0
# define REAL 1
# define BALANCE 2
# define INT 3
# define ANGLE 4
# define EPSILON 10e-8

# define TRUE 1
# define FALSE 0

# define ORTHO 0
# define AXIS 1

int g_i;

typedef struct s_scene	t_scene;

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
	float		aspect_ratio;
	t_scene		*scene;
	int			is_help;
	int			error;
}				t_img;

// MINIRT
void	set_image(t_img *img);
void	set_scene(t_img *img, t_scene *scene, char *av);
void	render(t_img *img);
void	free_img(t_img *img);
void	ft_options(void);

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

void	calculate_rotation_angles(t_img *img, int delta_x, int delta_y);

#endif

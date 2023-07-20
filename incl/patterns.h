/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:03:47 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/19 16:25:08 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNS_H
# define PATTERNS_H

# include "vector_math.h"
# include "objects.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# ifndef M_1_DIV_PI
#  define M_1_DIV_PI 0.31830988618379067
# endif
# ifndef M_1_DIV_2PI
#  define M_1_DIV_2PI 0.15915494309189535
# endif
# ifndef U
#  define U 0
# endif
# ifndef V
#  define V 1
# endif

typedef union u_object	t_object;
typedef union u_texture	t_texture;

typedef t_vec2			(*t_map_func)(t_vec3 *, t_object *);
typedef t_vec4			(*t_col_func)(t_texture *, t_vec2);

typedef enum e_pattern
{
	checkers_pat,
	brick_pat
}	t_pattern;

typedef struct s_checkers
{
	char	*file;
	int		width;
	int		height;
	t_vec4	light;
	t_vec4	dark;
}			t_checkers;

typedef struct s_picture
{
	char	*file;
	int		width;
	int		height;
	int		*picture;
}			t_picture;

typedef union u_texture
{
	char		*file;
	t_pattern	pattern;
	t_checkers	checkers;
	t_picture	picture;
}				t_texture;

t_vec2		spherical_map(t_vec3 *point, t_object *obj);
t_vec2		cylinder_map(t_vec3 *point, t_object *obj);
t_vec2		plane_map(t_vec3 *point, t_object *obj);
t_vec2		disk_map(t_vec3 *point, t_object *obj);
t_vec2		triangle_map(t_vec3 *point, t_object *obj);

t_vec4		get_checkers(t_texture *checkers, t_vec2 uv);
t_checkers	set_board(int width, int height, t_vec4 light, t_vec4 dark);
t_vec4		get_brick(t_texture *texture, t_vec2 uv);

void		set_meta(t_object *object);
t_vec4		get_texture_colour(t_object *object, t_vec3 *point);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:03:47 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/15 16:07:01 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNS_H
# define PATTERNS_H

# include "vector_math.h"
# include "objects.h"
# include "minirt.h"

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


typedef t_vec2	(*t_map_func)(t_vec3 *, t_object *);

typedef struct s_checkers
{
	t_vec4	light;
	t_vec4	dark;
	int		width;
	int		height;
}			t_checkers;

typedef struct s_picture
{
	int		*picture;
	int		width;
	int		height;
}			t_picture;

typedef union u_texture
{
	t_checkers	checkers;
	t_picture	picture;
}				t_texture;

t_vec2	spherical_map(t_vec3 *point, t_object *obj);
t_vec2	capped_cylinder_map(t_vec3 point, t_object *obj);
t_vec2	plane_map(t_vec3 point, t_object *obj);

#endif
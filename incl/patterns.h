/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:03:47 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/14 14:20:26 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNS_H
# define PATTERNS_H

# include "vector_math.h"
# include "minirt.h"

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

#endif
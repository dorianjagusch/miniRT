/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:33:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/20 00:06:14 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERS_H
# define SHADERS_H

#include "scene.h"
#include "vector_math.h"
#include <float.h>

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	t_vec4	colour;
}			t_ray;

typedef struct s_payload
{
	int		id;
	double	distance;
	t_vec3	intersection;
	t_vec3	normal;
}			t_payload;

typedef struct s_dist_func
{
	int	type;
	int	(*dist_funct)(t_ray *, t_obj *);
}		t_dist_func;

void	get_closest(t_scene *scene, t_ray *ray, t_payload *payload);
double	dist_sphere(t_ray *ray, t_obj *obj);
double	dist_plane(t_ray *ray, t_obj *obj);
double	dist_cylinder(t_ray *ray, t_obj *obj);


#endif
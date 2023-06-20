/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:33:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/20 22:45:14 by djagusch         ###   ########.fr       */
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
}			t_ray;

typedef struct s_payload
{
	int		id;
	double	distance;
	t_vec3	hitpoint;
	t_vec3	hitnorm;
	double	light_dir;
	double	light_dist;

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
double 	light_dist(t_obj *objs, t_payload *payload);
t_vec3	get_normal(t_obj *obj, t_vec3 hitpoint);

#endif
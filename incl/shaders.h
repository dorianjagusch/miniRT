/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:33:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/22 13:14:52 by djagusch         ###   ########.fr       */
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
	int		obj_id;
	double	distance;
	t_vec3	hitpoint;
	t_vec3	hitnorm;
	t_vec3	light_dir;
	double	light_dist;
	int		material;
}			t_payload;

typedef struct s_dist_func
{
	int		type;
	double	(*dist_funct)(t_ray *, t_obj *);
}		t_dist_func;

void	get_closest(t_scene *scene, t_ray *ray, t_payload *payload);
double	get_dist(t_ray *ray, t_obj *obj);
double	dist_sphere(t_ray *ray, t_obj *obj);
double	dist_plane(t_ray *ray, t_obj *obj);
double	dist_cylinder(t_ray *ray, t_obj *obj);
void	light_distance(t_scene *scene, t_payload *payload);
t_vec3	get_normal(t_obj *obj, t_vec3 hitpoint);

t_vec4	hit_shader(t_scene *scene, t_payload *payload);

#endif
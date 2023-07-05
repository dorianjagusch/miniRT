/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:33:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/05 15:58:31 by smorphet         ###   ########.fr       */
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

typedef struct s_hitresult
{
	int		obj_id;
	double	distance;
	t_vec3	hitpoint;
	t_vec3	hitnorm;
}			t_hitresult;


typedef struct s_payload //TODO: split this into hit test results and light/camera stuff, make most things read only
{
	int		obj_id;
	double	distance;
	t_vec3	hitpoint;
	t_vec3	hitnorm;
	t_vec3	point2cam;
	t_vec3	light_dir;
	double	light_dist;
	int		material;
}			t_payload;

typedef struct s_print_func
{
	int		type;
	void	(*print_funct)(t_obj);
}		t_print_func;

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
double	dist_disk(t_ray *ray, t_obj *obj);
double	dist_triangle(t_ray *ray, t_obj *obj);
void	light_distance(t_scene *scene, t_payload *payload);
t_vec3	get_normal(t_obj *obj, t_vec3 hitpoint);
t_vec4	hit_shader(const t_scene *scene, const t_payload *payload);
t_ray	create_primary_ray(t_camera *cam, t_vec2 pxl);
void	set_hitpoint(t_scene *scene, t_ray *ray, t_payload *payload);

#endif
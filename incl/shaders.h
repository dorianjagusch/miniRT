/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:33:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/05 19:12:08 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERS_H
# define SHADERS_H

# include "scene.h"
# include "vector_math.h"
# include <float.h>

enum e_colour
{
	ambient,
	diffuse,
	specular,
	transparent,
	final
};

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	double	transparency;
}			t_ray;

typedef struct s_hitresult
{
	int		obj_id;
	double	distance;
	t_vec3	position;
	t_vec3	normal;
	t_vec3	point2cam;
	int		material;
}			t_hitresult;

typedef struct s_light_info
{
	t_vec3	direction;
	double	distance;
	double	intensity;
}			t_light_info;

typedef struct s_print_func
{
	int		type;
	void	(*print_funct)(t_obj);
}		t_print_func;

typedef struct s_dist_func
{
	int		type;
	double	(*dist_funct)(const t_ray *, const t_obj *);
}		t_dist_func;

void			get_closest(const t_scene *scene, const t_ray *ray, t_hitresult *hit);
double			get_dist(const t_ray *ray, const t_obj *obj);
double			dist_sphere(const t_ray *ray, const t_obj *obj);
double			dist_plane(const t_ray *ray, const t_obj *obj);
double			dist_cylinder(const t_ray *ray, const t_obj *obj);
double			dist_disk(const t_ray *ray, const t_obj *obj);
double			dist_triangle(const t_ray *ray, const t_obj *obj);
t_light_info	light_distance(t_scene *scene, t_hitresult *hit);
t_vec3			get_normal(t_obj *obj, t_vec3 hitpoint);
t_vec4			hit_shader(const t_ray *ray, const t_scene *scene,
					const t_hitresult *hit, const t_light_info *light_info);
t_ray			create_primary_ray(t_camera *cam, t_vec2 pxl);
void			set_hitpoint(t_scene *scene, t_ray *ray, t_hitresult *hit);
void			create_sphere(t_obj *obj, char *line);
void			create_cylinder(t_obj *obj, char *line);
void			create_plane(t_obj *obj, char *line);
void			create_disk(t_obj *obj, char *line);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:33:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/10 16:35:59 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERS_H
# define SHADERS_H

# include "scene.h"
# include "vector_math.h"
# include "materials.h"
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
	float	transparency;
}			t_ray;

typedef struct s_hitresult
{
	int				obj_id;
	float			distance;
	t_vec3			position;
	t_vec3			normal;
	t_vec3			point2cam;
	t_material_e	material;
	t_vec4			colour;
}					t_hitresult;

typedef struct s_light_info
{
	t_vec3	direction;
	float	distance;
	float	intensity;
}			t_light_info;

typedef float	(*t_dist_function)(const t_ray *, t_object *);

void			get_closest(const t_scene *scene, const t_ray *ray,
					t_hitresult *hit);
float			get_dist(const t_ray *ray, t_object *obj);
float			dist_sphere(const t_ray *ray, t_object *sphere);
float			dist_plane(const t_ray *ray, t_object *plane);
float			dist_cylinder(const t_ray *ray, t_object *cylinder);
float			dist_disk(const t_ray *ray, t_object *disk);
float			dist_triangle(const t_ray *ray, t_object *triangle);
float			dist_box(const t_ray *ray, t_object *box);
float			dist_arbbox(const t_ray *ray, t_object *obj);
t_light_info	light_distance(t_scene *scene, t_hitresult *hit);
t_vec3			get_normal(t_object *obj, t_vec3 hitpoint);
t_vec4			hit_shader(const t_scene *scene,
					const t_hitresult *hit, const t_light_info *light_info);
t_ray			create_primary_ray(t_camera *cam, t_vec2 pxl);
void			set_hitpoint(t_scene *scene, t_ray *ray, t_hitresult *hit);
void			create_sphere(t_sphere *sphere, char *line);
void			create_cylinder(t_cylinder *cylinder, char *line);
void			create_plane(t_plane *plane, char *line);
void			create_disk(t_disk *disk, char *line);
#endif
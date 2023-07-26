/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_info_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 07:32:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 14:01:00 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"
#include "objects_bonus.h"
#include "shaders_bonus.h"
#include "minirt_bonus.h"
#include <stdio.h>

t_vec4	get_hitcolour(const t_object *obj)
{
	if (obj->type == sphere_obj)
		return (obj->sphere.colour);
	else if (obj->type == plane_obj)
		return (obj->plane.colour);
	else if (obj->type == cylinder_obj)
		return (obj->cylinder.colour);
	else if (obj->type == disk_obj)
		return (obj->disk.colour);
	else if (obj->type == triangle_obj)
		return (obj->triangle.colour);
	else if (obj->type == cone_obj)
		return (obj->cone.colour);
	else
		return (obj->mesh.colour);
}

void	set_hitpoint(t_scene *scene, t_ray *ray, t_hitresult *hit)
{
	int		triangle_id;
	t_vec3	normal;
	t_vec4	colour;

	hit->position = vec3_add(ray->origin,
			vec3_multf(ray->direction, hit->distance));
	hit->point2cam = vec3_sub(hit->position, ray->origin);
	vec3_normalize(&hit->point2cam);
	get_texture_info(&(scene->objs[hit->obj_id]),
		&(hit->position), &colour, &normal);
	if (!scene->objs[hit->obj_id].meta.tex_col)
		hit->colour = get_hitcolour(&(scene->objs[hit->obj_id]));
	else
		hit->colour = colour;
	hit->normal = get_normal(&(scene->objs[hit->obj_id]), hit->position);
	hit->position = vec3_add(hit->position,
			vec3_multf(vec3_multf(hit->normal, 10e-2),
				-ft_sign(vec3_dot(hit->normal, scene->cam.dir))));
	if (scene->objs[hit->obj_id].meta.tex_norm)
		hit->normal = vec3_propadd(hit->normal, vec3_neg(normal), 0.55);
	if (scene->objs[hit->obj_id].type == mesh_obj)
	{
		triangle_id = scene->objs[hit->obj_id].mesh.obj_id;
		hit->normal = scene->objs[hit->obj_id].mesh.\
			triangle_data[triangle_id].triangle.normal;
		hit->colour = scene->objs[hit->obj_id].mesh.\
		triangle_data[triangle_id].triangle.colour;
		return ;
	}
}
